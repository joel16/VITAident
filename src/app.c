#include "app.h"
#include "utils.h"

const char * getLang()
{
	SceAppUtilInitParam init;
	SceAppUtilBootParam boot;
	memset(&init, 0, sizeof(SceAppUtilInitParam));
	memset(&boot, 0, sizeof(SceAppUtilBootParam));
	sceAppUtilInit(&init, &boot);
	
	const char *languages[] = 
	{
		"Japanese",
		"English US",
		"French",
		"Spanish",
		"German",
		"Italian",
		"Dutch",
		"Portugese",
		"Russian",
		"Korean",
		"Traditional Chinese",
		"Simplified Chinese",
		"Finnish",
		"Swedish",
		"Danish",
		"Norwegian",
		"Polish",
		"Brazlian Portugese",
		"English UK"
	};

	int language = 0;
	sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, &language);

	if (language < 18)
		return languages[language];
	else
		return languages[18];
			
	sceAppUtilShutdown();
}

char * getStorageInfo(int type)
{
	uint64_t free_size = 0, max_size = 0;
	sceAppMgrGetDevInfo("ux0:", &max_size, &free_size);
	
	static char free_size_string[16], max_size_string[16];
	getSizeString(free_size_string, free_size);
	getSizeString(max_size_string, max_size);
	
	if (type == 0)
		return max_size_string;
	else 
		return free_size_string;
}