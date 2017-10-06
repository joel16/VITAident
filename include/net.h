#ifndef _VITAIDENT_NET_H_
#define _VITAIDENT_NET_H_

#include <vitasdk.h>

SceVoid initNet(SceVoid);
SceVoid termNet(SceVoid);
char * getMacAddress(SceVoid);
char * getIP(SceVoid);

#endif