#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "graphics.h"

#define printf psvDebugScreenPrintf

#define SCE_CTRL_ANY_KEY (SCE_CTRL_SELECT | SCE_CTRL_L3 | SCE_CTRL_R3 | SCE_CTRL_START | SCE_CTRL_UP | SCE_CTRL_RIGHT | SCE_CTRL_DOWN | SCE_CTRL_LEFT | \
	SCE_CTRL_LTRIGGER | SCE_CTRL_RTRIGGER | SCE_CTRL_L1 | SCE_CTRL_R1 | SCE_CTRL_TRIANGLE | SCE_CTRL_CIRCLE | SCE_CTRL_CROSS | SCE_CTRL_SQUARE)

int sceRegMgrGetKeyInt(const char* category, const char* name, int* buf);
int sceRegMgrGetKeyStr(const char* category, const char* name, char* buf, const int size); 
int sceRegMgrGetKeyBin(const char *category, const char *name, void *buf, int size);

int getVolume();
int getBrightness();
int regMgrGetInt(const char * category, const char * name);
char * regMgrGetStr(const char* category, const char* name);
void setColor(Color color); //Set font color
int printStr(bool printStar, Color color, char message[250], char *info, ...);
void getSizeString(char *string, uint64_t size);
const char *concat(char* s1, char* s2);

#endif