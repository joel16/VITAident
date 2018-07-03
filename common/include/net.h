#ifndef _VITAIDENT_NET_H_
#define _VITAIDENT_NET_H_

#include <vitasdk.h>

SceVoid Net_Init(SceVoid);
SceVoid Net_Term(SceVoid);
char *Net_GetMacAddr(SceVoid);
char *Net_GetIPAddr(SceVoid);

#endif