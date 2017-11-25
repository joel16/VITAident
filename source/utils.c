#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "utils.h"

SceInt getBrightness(SceVoid)
{
	SceInt brightness = 0;
	SceInt regBrightness = regMgrGetInt("/CONFIG/DISPLAY/", "brightness");
	
	brightness = (regBrightness * 0.00152590219);
	
	return brightness;
}

SceInt regMgrGetInt(const char * category, const char * name)
{
	int value = 0;
	
	if (R_SUCCEEDED(sceRegMgrGetKeyInt(category, name, &value)))
		return value;
	
	return 0;
}

char * regMgrGetStr(const char* category, const char* name)
{
	static char str[256];
	
	if (R_SUCCEEDED(sceRegMgrGetKeyStr(category, name, str, sizeof(str))))
		return str;
	
	return NULL;
}

SceVoid getSizeString(char * string, SceULong64 size) //Thanks TheOfficialFloW
{
	double double_size = (double)size;

	SceInt i = 0;
	static char * units[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
	
	while (double_size >= 1024.0f) 
	{
		double_size /= 1024.0f;
		i++;
	}

	sprintf(string, "%.*f %s", (i == 0) ? 0 : 2, double_size, units[i]);
}

const char * concat(char * s1, char * s2)
{
    char * ns = malloc(strlen(s1) + strlen(s2) + 1);
    ns[0] = '\0';
    strcat(ns, s1);
    strcat(ns, s2);
    return ns;
}