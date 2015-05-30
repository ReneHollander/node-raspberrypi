#include "helper.h"

ILCLIENT_T* init() {
	bcm_host_init();
	ILCLIENT_T* client = ilclient_init();
	if (client == NULL) {
		return NULL;
	}

	if(OMX_Init() != OMX_ErrorNone) {
		ilclient_destroy(client);
		return NULL;
	}

	return client;
}

void destroy(ILCLIENT_T *client) {
	OMX_Deinit();
	ilclient_destroy(client);
}
