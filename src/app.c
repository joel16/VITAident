#include "app.h"
#include "utils.h"

SceVoid initAppUtil(SceVoid)
{
	SceAppUtilInitParam init;
	SceAppUtilBootParam boot;
	memset(&init, 0, sizeof(SceAppUtilInitParam));
	memset(&boot, 0, sizeof(SceAppUtilBootParam));
	sceAppUtilInit(&init, &boot);
}

SceVoid termAppUtil(SceVoid)
{
	sceAppUtilShutdown();
}

SceChar8 * getUser(SceVoid)
{
	static SceChar8 userName[SCE_SYSTEM_PARAM_USERNAME_MAXSIZE];
	sceAppUtilSystemParamGetString(SCE_SYSTEM_PARAM_ID_USERNAME, userName, SCE_SYSTEM_PARAM_USERNAME_MAXSIZE);
	
	return userName;
}

const char * getLang(SceVoid)
{
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
}

char * getStorageInfo(SceInt type)
{
	SceULong64 free_size = 0, max_size = 0;
	sceAppMgrGetDevInfo("ux0:", &max_size, &free_size);
	
	static char free_size_string[16], max_size_string[16];
	getSizeString(free_size_string, free_size);
	getSizeString(max_size_string, max_size);
	
	if (type == 0)
		return max_size_string;
	else 
		return free_size_string;
}

SceBool getEnterButton(SceVoid) // Circle = 0, cross = 1
{
	int enterButton = 0;
	sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, &enterButton);
	
	if (enterButton == SCE_SYSTEM_PARAM_ENTER_BUTTON_CROSS)
		return SCE_TRUE;
	
	return SCE_FALSE;
}