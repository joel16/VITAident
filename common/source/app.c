#include <stdio.h>
#include <string.h>

#include "app.h"
#include "utils.h"

SceInt App_InitAppUtil(SceVoid)
{
	SceAppUtilInitParam init;
	SceAppUtilBootParam boot;
	memset(&init, 0, sizeof(SceAppUtilInitParam));
	memset(&boot, 0, sizeof(SceAppUtilBootParam));
	
	SceInt ret = 0;
	
	if (R_FAILED(ret = sceAppUtilInit(&init, &boot)))
		return ret;
	
	return 0;
}

SceInt App_TermAppUtil(SceVoid)
{
	SceInt ret = 0;
	
	if (R_FAILED(ret = sceAppUtilShutdown()))
		return ret;
	
	return 0;
}

SceChar8 *App_GetUser(SceVoid)
{
	static SceChar8 userName[SCE_SYSTEM_PARAM_USERNAME_MAXSIZE];
	
	if (R_SUCCEEDED(sceAppUtilSystemParamGetString(SCE_SYSTEM_PARAM_ID_USERNAME, userName, SCE_SYSTEM_PARAM_USERNAME_MAXSIZE)))
		return userName;
	
	return NULL;
}

const char *App_GetLanguage(SceVoid)
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
	
	if (R_SUCCEEDED(sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, &language)))
	{
		if (language < 0x12)
			return languages[language];
		else
			return languages[0x12];
	}
	
	return NULL;
}

SceOff App_GetTotalCapacity(const char *device)
{
	SceIoDevInfo info;
	
	if (R_SUCCEEDED(sceIoDevctl(device, 0x3001, NULL, 0, &info, sizeof(SceIoDevInfo))))
		return info.max_size;
	
	return 0;
}

static SceOff App_GetFreeCapacity(const char *device)
{
	SceIoDevInfo info;
	
	if (R_SUCCEEDED(sceIoDevctl(device, 0x3001, NULL, 0, &info, sizeof(SceIoDevInfo))))
		return info.free_size;
	
	return 0;
}

SceOff App_GetUsedCapacity(const char *device)
{
	SceIoDevInfo info;
	
	if (R_SUCCEEDED(sceIoDevctl(device, 0x3001, NULL, 0, &info, sizeof(SceIoDevInfo))))
		return info.max_size - info.free_size;
	
	return 0;
}

char *App_GetStorageInfo(const char *device, SceInt type)
{
	static char size_string[0x10];

	switch (type)
	{
		case 0: // Max size
			Utils_GetSizeString(size_string, App_GetTotalCapacity(device));
			break;
		
		case 1: // Free size
			Utils_GetSizeString(size_string, App_GetFreeCapacity(device));
			break;
			
		case 2: // Used size
			Utils_GetSizeString(size_string, App_GetUsedCapacity(device));
			break;
	}
	
	return size_string;
}

SceBool App_GetEnterButton(SceVoid)
{
	int enterButton = 0;
	sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, &enterButton);
	
	if (enterButton == SCE_SYSTEM_PARAM_ENTER_BUTTON_CROSS)
		return SCE_TRUE;
	
	return SCE_FALSE;
}