#ifndef _VITAIDENT_APP_H_
#define _VITAIDENT_APP_H_

#include <vitasdk.h>

SceInt App_InitAppUtil(SceVoid);
SceInt App_TermAppUtil(SceVoid);
SceChar8 *App_GetUser(SceVoid);
const char *App_GetLanguage(SceVoid);
SceOff App_GetTotalCapacity(const char *device);
SceOff App_GetUsedCapacity(const char *device);
char *App_GetStorageInfo(const char *device, SceInt type);
SceBool App_GetEnterButton(SceVoid);

#endif