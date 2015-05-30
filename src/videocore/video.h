#ifndef VIDEO_H
#define VIDEO_H

#include <stdio.h>

#include "ilclient/ilclient.h"

int playVideoFile(ILCLIENT_T *client, FILE *in);
int playVideoFilename(ILCLIENT_T *client, char* filename);

#endif
