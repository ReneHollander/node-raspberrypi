#ifndef HELPER_H
#define HELPER_H

#include <bcm_host.h>
#include "ilclient/ilclient.h"

ILCLIENT_T* init();
void destroy(ILCLIENT_T *client);

#endif
