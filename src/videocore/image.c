#include "image.h"

int viewImageFilename(ILCLIENT_T *client, char* filename, int duration) {
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		return -1;
	}

	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *imagedata = malloc(fsize + 1);
	fread(imagedata, fsize, 1, file);
	fclose(file);
	int ret = viewImageMemory(client, imagedata, fsize, duration);
	free(imagedata);
	return ret;
}

int viewImageMemory(ILCLIENT_T *client, char* imagedata, int imagelength, int duration) {
	OMX_BUFFERHEADERTYPE *pIbuf;
	int bytes_read;
	int status = 0;
	int ret;
	int port_settings_changed = 0;

	OMX_IMAGE_PARAM_PORTFORMATTYPE imagePortFormat;
	OMX_PARAM_PORTDEFINITIONTYPE portDef;

	COMPONENT_T *image_decode = NULL;
	COMPONENT_T *video_render = NULL;
	COMPONENT_T *list[3];
	TUNNEL_T tunnel[2];

	memset(list, 0, sizeof(list));
	memset(tunnel, 0, sizeof(tunnel));

	// create image_decode
	ret = ilclient_create_component(client, &image_decode, "image_decode", ILCLIENT_DISABLE_ALL_PORTS | ILCLIENT_ENABLE_INPUT_BUFFERS );
	if (ret != 0)
		status = -15;
	list[0] = image_decode;

	// create video_render
	ret = ilclient_create_component(client, &video_render, "video_render", ILCLIENT_DISABLE_ALL_PORTS);
	if (ret != 0)
		status = -14;
	list[1] = video_render;
	list[2] = NULL;

	portDef.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
	portDef.nVersion.nVersion = OMX_VERSION;
	portDef.nPortIndex = 320;
	ret = OMX_GetParameter(ILC_GET_HANDLE(image_decode), OMX_IndexParamPortDefinition, &portDef);
	portDef.nBufferSize = OMX_BUFFER_SIZE;
	ret = OMX_SetParameter(ILC_GET_HANDLE(image_decode), OMX_IndexParamPortDefinition, &portDef);

	imagePortFormat.nSize = sizeof(OMX_IMAGE_PARAM_PORTFORMATTYPE);
	imagePortFormat.nVersion.nVersion = OMX_VERSION;
	imagePortFormat.nPortIndex = 320;
	imagePortFormat.eCompressionFormat = OMX_IMAGE_CodingJPEG;
	OMX_SetParameter(ILC_GET_HANDLE(image_decode), OMX_IndexParamImagePortFormat, &imagePortFormat);

	ilclient_change_component_state(image_decode, OMX_StateIdle);
	set_tunnel(tunnel, image_decode, 321, video_render, 90);
	ilclient_enable_port_buffers(image_decode, 320, NULL, NULL, NULL);
	ilclient_change_component_state(image_decode, OMX_StateExecuting);

	int pos = 0;
	while((pIbuf = ilclient_get_input_buffer(image_decode, 320, 1)) != NULL) {
		int readlength = pIbuf->nAllocLen;
		if (pos + readlength > imagelength) {
			readlength = imagelength - pos;
		}
		memcpy(pIbuf->pBuffer, imagedata + pos, readlength);
		pos += readlength;
		bytes_read = readlength;

		if(port_settings_changed == 0 &&
		   (( bytes_read > 0 && ilclient_remove_event(image_decode, OMX_EventPortSettingsChanged, 321, 0, 0, 1) == 0) ||
		    ( bytes_read == 0 && ilclient_wait_for_event(image_decode, OMX_EventPortSettingsChanged, 321, 0, 0, 1,
		                                                 ILCLIENT_EVENT_ERROR | ILCLIENT_PARAMETER_CHANGED, 10000) == 0))) {
			port_settings_changed = 1;


			if(ilclient_setup_tunnel(tunnel, 0, 0) != 0) {
				status = -7;
				break;
			}

			ilclient_change_component_state(video_render, OMX_StateExecuting);

		}

		if(!bytes_read)
			break;

		pIbuf->nFilledLen = bytes_read;
		pIbuf->nOffset = 0;
		pIbuf->nFlags = OMX_BUFFERFLAG_TIME_UNKNOWN;

		if(OMX_EmptyThisBuffer(ILC_GET_HANDLE(image_decode), pIbuf) != OMX_ErrorNone)
		{
			status = -6;
			break;
		}
	}

	pIbuf->nFilledLen = 0;
	pIbuf->nFlags = OMX_BUFFERFLAG_TIME_UNKNOWN | OMX_BUFFERFLAG_EOS;

	if(OMX_EmptyThisBuffer(ILC_GET_HANDLE(image_decode), pIbuf) != OMX_ErrorNone)
		status = -20;


	// wait for EOS from render
	ilclient_wait_for_event(video_render, OMX_EventBufferFlag, 90, 0, OMX_BUFFERFLAG_EOS, 0,
	                        ILCLIENT_BUFFER_FLAG_EOS, 10000);


	sleep(duration);


	// need to flush the renderer to allow video_decode to disable its input port
	ilclient_flush_tunnels(tunnel, 0);

	ilclient_disable_port_buffers(image_decode, 320, NULL, NULL, NULL);

	ilclient_disable_tunnel(tunnel);
	ilclient_teardown_tunnels(tunnel);


	ret = ilclient_change_component_state(image_decode, OMX_StateIdle);
	ret = ilclient_change_component_state(image_decode, OMX_StateLoaded);

	ilclient_cleanup_components(list);
	return status;
}
