#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>

#include "ilclient/ilclient.h"

#define OMX_BUFFER_SIZE 500 * 1024

int viewImageMemory(ILCLIENT_T *client, char* imagedata, int imagelength, int duration);
int viewImageFilename(ILCLIENT_T *client, char* filename, int duration);

#endif
