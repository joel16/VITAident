#include "kernel.h"

char * getFwVersion()
{
	static char version[10];
	
	SceSystemSwVersionParam param;
	param.size = sizeof(SceSystemSwVersionParam);
	sceKernelGetSystemSwVersion(&param);
	
	sprintf(version, "%s", param.version_string);
	
	return version;
}

int getModel()
{
	return sceKernelGetModelForCDialog();
}

char * getCID()
{
	char CID[32];
	static char idps[2 * 16] = {0};
	
	// Get IDPS
	_vshSblAimgrGetConsoleId(CID);
	
	int i = 0;
	for (i = 0; i < 16; i++)
		snprintf(idps + (i * 2), (2 * 16) - (i * 2) + 1, "%02X", CID[i]);
	
	return idps;
}

SceKernelOpenPsId getPSID()
{
	
	SceKernelOpenPsId id;
	sceKernelGetOpenPsId(&id);
	
	return id;
}