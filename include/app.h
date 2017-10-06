#ifndef _VITAIDENT_APP_H_
#define _VITAIDENT_APP_H_

#include <vitasdk.h>

SceInt initAppUtil(SceVoid);
SceInt termAppUtil(SceVoid);
SceChar8 * getUser(SceVoid);
const char * getLang(SceVoid);
SceOff getMaxSize(const char * dev);
SceOff getFreeSize(const char * dev);
SceOff getUsedSize(const char * dev);
char * getStorageInfo(const char * dev, SceInt type);
SceBool getEnterButton(SceVoid);

#endif