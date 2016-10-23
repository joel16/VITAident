#ifndef _VITAIDENT_APP_H_
#define _VITAIDENT_APP_H_

#include <psp2/apputil.h>
#include <psp2/appmgr.h>
#include <psp2/system_param.h>

#include <stdio.h>
#include <string.h>

void initAppUtil();
void termAppUtil();
char * getUser();
const char * getLang();
char * getStorageInfo(int type);
const char * getEnterButton();

#endif