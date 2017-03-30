#include "graphics.h"
#include "utils.h"

int getVolume()
{
	int calculatedVolume = 0;
	int volume = regMgrGetInt("/CONFIG/SOUND/", "main_volume");
	
	calculatedVolume = (volume * 3.33333333);
	
	if (calculatedVolume == 99)
		calculatedVolume = 100;
	
	return calculatedVolume;
}

int getBrightness()
{
	int calculatedBrightness = 0;
	int brightness = regMgrGetInt("/CONFIG/DISPLAY/", "brightness");
	
	calculatedBrightness = (brightness * 0.00152590219);
	
	return calculatedBrightness;
}

int regMgrGetInt(const char * category, const char * name)
{
	int value = -1;
	
	int ret = sceRegMgrGetKeyInt(category, name, &value);
	
	if (ret < 0)
		return 0;
	else
		return value;
}

char * regMgrGetStr(const char* category, const char* name)
{
	static char str[256];
	
	int ret = sceRegMgrGetKeyStr(category, name, str, sizeof(str)); 
	
	if (ret < 0)
		return NULL;
	else
		return str;
}

void setColor(Color color)
{
	psvDebugScreenSetFgColor(color);
}

int printStr(bool printStar, Color color, char message[250], char *info, ...)
{
	char buf[512];

	va_list opt;
	va_start(opt, info);
	
	if (printStar == true)
	{
		setColor(color); 
		printf("* "); 
	}
	
	setColor(WHITE); 
	printf("%s", message); 
	
	setColor(color); 
	int ret = vsnprintf(buf, sizeof(buf), info, opt);
	printTextScreen(buf);
	va_end(opt);
	
	return ret;
}

void getSizeString(char *string, uint64_t size) //Thanks TheOfficialFloW
{
	double double_size = (double)size;

	int i = 0;
	static char *units[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
	while (double_size >= 1024.0f) {
		double_size /= 1024.0f;
		i++;
	}

	sprintf(string, "%.*f %s", (i == 0) ? 0 : 2, double_size, units[i]);
}

const char * concat(char* s1, char* s2)
{
    char *ns = malloc(strlen(s1) + strlen(s2) + 1);
    ns[0] = '\0';
    strcat(ns, s1);
    strcat(ns, s2);
    return ns;
}