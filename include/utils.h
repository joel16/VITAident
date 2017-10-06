#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <vitasdk.h>

/// Checks whether a result code indicates success.
#define R_SUCCEEDED(res)   ((res)>=0)
/// Checks whether a result code indicates failure.
#define R_FAILED(res)      ((res)<0)
/// Returns the level of a result code.

#include "graphics.h"

#define printf psvDebugScreenPrintf

#define SCE_CTRL_ANY_KEY (SCE_CTRL_SELECT | SCE_CTRL_L3 | SCE_CTRL_R3 | SCE_CTRL_START | SCE_CTRL_UP | SCE_CTRL_RIGHT | SCE_CTRL_DOWN | SCE_CTRL_LEFT | \
		SCE_CTRL_LTRIGGER | SCE_CTRL_RTRIGGER | SCE_CTRL_L1 | SCE_CTRL_R1 | SCE_CTRL_TRIANGLE | SCE_CTRL_CIRCLE | SCE_CTRL_CROSS | SCE_CTRL_SQUARE)
	
SceInt getVolume(SceVoid);
SceInt getBrightness(SceVoid);
SceInt regMgrGetInt(const char * category, const char * name);
char * regMgrGetStr(const char * category, const char * name);
SceVoid setColor(Color color); //Set font color
SceInt printStr(SceBool printStar, Color color, char message[250], char * info, ...);
SceVoid getSizeString(char *string, SceULong64 size);
const char * concat(char * s1, char * s2);

#endif