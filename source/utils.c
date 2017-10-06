#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "utils.h"

SceInt getVolume(SceVoid)
{
	SceInt volume = 0;
	SceInt regVolume = regMgrGetInt("/CONFIG/SOUND/", "main_volume");
	
	volume = (regVolume * 3.33333333);
	
	if (volume == 99)
		volume = 100;
	
	return volume;
}

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

SceVoid setColor(Color color)
{
	psvDebugScreenSetFgColor(color);
}

SceInt printStr(SceBool printStar, Color color, char message[250], char * info, ...)
{
	char buf[512];

	va_list opt;
	va_start(opt, info);
	
	if (printStar) // SCE_TRUE
	{
		setColor(color); 
		printf("* "); 
	}
	
	setColor(WHITE); 
	printf("%s", message); 
	
	setColor(color); 
	SceInt ret = vsnprintf(buf, sizeof(buf), info, opt);
	printTextScreen(buf);
	va_end(opt);
	
	return ret;
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