#include <stdlib.h>

#include "kernel.h"
#include "utils.h"

char *Kernel_GetFirmwareVersion(SceBool spoofed)
{
	static char version[16];
	
	SceKernelFwInfo data;
	data.size = sizeof(SceKernelFwInfo);
	
	// Get the spoofed version
	if (spoofed)
	{	
		if (R_SUCCEEDED(sceKernelGetSystemSwVersion(&data)))
			snprintf(version, 16, "%s", data.versionString);
		
		return version;
	}
	
	// Get the actual version
	if (R_SUCCEEDED(_vshSblGetSystemSwVersion(&data)))
	{
		snprintf(version, 16, "%s", data.versionString);
		return version;
	}
	
	return NULL;
}

SceInt Kernel_GetModel(SceVoid)
{
	SceInt model = 0;
	
	if (R_SUCCEEDED(model = sceKernelGetModelForCDialog()))
		return model;
	
	return 0;
}

char *Kernel_GetCID(SceVoid)
{
	SceInt ret = 0;
	char CID[16];

	if (R_FAILED(ret = _vshSblAimgrGetConsoleId(CID)))
		return NULL;

	static char IDPS[33];
	for (SceInt i = 0; i < 16; i++)
		snprintf(&IDPS[2 * i], 33, "%02X", CID[i]);
	
	return IDPS;
}

char *Kernel_GetPSID(SceVoid)
{	
	SceInt ret = 0;
	SceKernelOpenPsId id;
	
	if (R_FAILED(ret = sceKernelGetOpenPsId(&id)))
		return NULL;

	static char PSID[33];
	for(SceInt i = 0; i < 16; i++)
		snprintf(&PSID[2 * i], 33, "%02X", id.id[i]);
	
	return PSID;
}

static int Kernel_GetModelRev(SceVoid)
{
	SceInt ret = 0;
    PsCode pscode;
    
	if (R_FAILED(ret = _vshSblAimgrGetPscode(&pscode)))
        return ret;
    
	char model[5];
    snprintf(model, 5, "%02X%02X", pscode.model_revision[1], pscode.model_revision[0]);

	return atoi(model);
}

static char *Kernel_GetTargetID(SceVoid)
{
	SceInt ret = 0;
    PsCode pscode;
    
	if (R_FAILED(ret = _vshSblAimgrGetPscode(&pscode)))
        return NULL;
    
	static char targetID[5];
    snprintf(targetID, 5, "%01X%02X", pscode.target_id[1], pscode.target_id[0]);

	return targetID;
}

char *Kernel_GetDeviceModel(SceVoid)
{
	static char out[9];

	switch(Kernel_GetModelRev())
	{
		case 10:
			snprintf(out, 9, "PCH-10XX");
			break;
		case 14:
			snprintf(out, 9, "PCH-20XX");
			break;
		case 18:
			snprintf(out, 9, "PCH-20XX");
			break;
		case 201:
			snprintf(out, 9, "VTE-10XX");
			break;
	}

	return out;
}

char *Kernel_GetDeviceBoard(SceVoid)
{
	static char out[9];

	switch(Kernel_GetModelRev())
	{
		case 10:
			snprintf(out, 8, "IRS-002");
			break;
		case 14:
			snprintf(out, 9, "USS-1001");
			break;
		case 18:
			snprintf(out, 8, "Unknown");
			break;
		case 201:
			snprintf(out, 9, "DOL-1001");
			break;
	}

	return out;
}

char *Kernel_GetDeviceUnit(SceVoid)
{
	static char out[27];

	if (strncasecmp(Kernel_GetTargetID(), "100", 3) == 0)
		snprintf(out, 27, "Test unit");
	else if (strncasecmp(Kernel_GetTargetID(), "101", 3) == 0)
		snprintf(out, 27, "Tool unit");
	else if (strncasecmp(Kernel_GetTargetID(), "102", 3) == 0)
		snprintf(out, 27, "DEX unit");
	else if (strncasecmp(Kernel_GetTargetID(), "103", 3) == 0)
		snprintf(out, 27, "CEX - Japan");
	else if (strncasecmp(Kernel_GetTargetID(), "104", 3) == 0)
		snprintf(out, 27, "CEX - North America");
	else if (strncasecmp(Kernel_GetTargetID(), "105", 3) == 0)
		snprintf(out, 27, "CEX - Europe/Africa");
	else if (strncasecmp(Kernel_GetTargetID(), "106", 3) == 0)
		snprintf(out, 27, "CEX - Korea");
	else if (strncasecmp(Kernel_GetTargetID(), "107", 3) == 0)
		snprintf(out, 27, "CEX - United Kingdom");
	else if (strncasecmp(Kernel_GetTargetID(), "108", 3) == 0)
		snprintf(out, 27, "CEX - Mexico/Latin America");
	else if (strncasecmp(Kernel_GetTargetID(), "109", 3) == 0)
		snprintf(out, 27, "CEX - Australia/New Zeland");
	else if (strncasecmp(Kernel_GetTargetID(), "10A", 3) == 0)
		snprintf(out, 27, "CEX - Hong Kong/Singapore");
	else if (strncasecmp(Kernel_GetTargetID(), "10B", 3) == 0)
		snprintf(out, 27, "CEX - Taiwan");
	else if (strncasecmp(Kernel_GetTargetID(), "10C", 3) == 0)
		snprintf(out, 27, "CEX - Russia");
	else if (strncasecmp(Kernel_GetTargetID(), "10D", 3) == 0)
		snprintf(out, 27, "CEX - China");

	return out;
}