#include "regmgr.h"
#include "utils.h"

SceInt RegMgr_GetBrightness(SceVoid)
{
	SceInt brightness = 0;
	SceInt regBrightness = RegMgr_GetInt("/CONFIG/DISPLAY/", "brightness");
	
	brightness = (regBrightness * 0.00152590219);
	
	return brightness;
}

SceInt RegMgr_GetInt(const char *category, const char *name)
{
	int value = 0;
	
	if (R_SUCCEEDED(sceRegMgrGetKeyInt(category, name, &value)))
		return value;
	
	return 0;
}

char *RegMgr_GetStr(const char *category, const char *name)
{
	static char str[256];
	
	if (R_SUCCEEDED(sceRegMgrGetKeyStr(category, name, str, sizeof(str))))
		return str;
	
	return NULL;
}