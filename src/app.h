#ifndef _VITAIDENT_APP_H_
#define _VITAIDENT_APP_H_

#include <psp2/apputil.h>
#include <psp2/appmgr.h>
#include <psp2/system_param.h>

#include <stdio.h>
#include <string.h>

SceVoid initAppUtil(SceVoid);
SceVoid termAppUtil(SceVoid);
SceChar8 * getUser(SceVoid);
const char * getLang(SceVoid);
char * getStorageInfo(SceInt type);
SceBool getEnterButton(SceVoid);

#endif