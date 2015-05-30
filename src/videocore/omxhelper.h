#ifndef OMXHELPER
#define OMXHELPER

#include <stdio.h>
#include <stdlib.h>

#include <OMX_Core.h>
#include <OMX_Component.h>

#define OMX_INIT_STRUCTURE(a) \
    memset(&(a), 0, sizeof(a)); \
    (a).nSize = sizeof(a); \
    (a).nVersion.nVersion = OMX_VERSION; \
    (a).nVersion.s.nVersionMajor = OMX_VERSION_MAJOR; \
    (a).nVersion.s.nVersionMinor = OMX_VERSION_MINOR; \
    (a).nVersion.s.nRevision = OMX_VERSION_REVISION; \
    (a).nVersion.s.nStep = OMX_VERSION_STEP

void printState(OMX_HANDLETYPE handle);
char *err2str(int err);

#endif
