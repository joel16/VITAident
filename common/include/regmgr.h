#ifndef _VITAIDENT_REGMGR_H_
#define _VITAIDENT_REGMGR_H_

#include <vitasdk.h>

SceInt RegMgr_GetBrightness(SceVoid);
SceInt RegMgr_GetInt(const char *category, const char *name);
char *RegMgr_GetStr(const char *category, const char *name);

#endif