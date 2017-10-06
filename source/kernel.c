#include "fs.h"
#include "kernel.h"
#include "utils.h"

char * getFwVersion(SceBool spoofed)
{
	static char version[0x10];
	unsigned char str[0x20] = "";
	
	if (spoofed)
	{
		SceKernelFwInfo info;
		info.size = sizeof(SceKernelFwInfo);
		
		if (R_SUCCEEDED(sceKernelGetSystemSwVersion(&info)))
			snprintf(version, 0x10, "%s", info.versionString);
		
		return version;
	}
	
	SceUID file = sceIoOpen("os0:psp2bootconfig.skprx", SCE_O_RDONLY, 0777);
	
	if (R_FAILED(file))
		return "Unknown firmware";
	
	sceIoLseek(file, 0x92, SCE_SEEK_SET);
	sceIoRead(file, &str, 0x8);
	sceIoClose(file);
		
	snprintf(version, 0x8, "%x.%02x", str[0x3], str[0x2]);
	
	return version;
}

char getHenkakuVersion(SceVoid)
{
	char henkakuVersion[0xA];
	
	SceKernelFwInfo info;
	info.size = sizeof(SceKernelFwInfo);
	
	if (R_SUCCEEDED(sceKernelGetSystemSwVersion(&info)))
		strcpy(henkakuVersion, (char *)info.versionString);
	
	return henkakuVersion[(strlen(henkakuVersion) - 1)];
}

SceInt getModel(SceVoid)
{
	SceInt model = 0;
	
	if (R_SUCCEEDED(model = sceKernelGetModelForCDialog()))
		return model;
	
	return 0;
}

char * getCID(SceVoid)
{
	char CID[0x20];
	static char idps[0x20];
	
	// Get IDPS
	if (R_SUCCEEDED(_vshSblAimgrGetConsoleId(CID)))
	{
		for (SceInt i = 0; i < 0x10; i++)
			snprintf(idps + (i * 0x2), (0x20) - (i * 0x2) + 0x1, "%02X", CID[i]);
	}
	
	return idps;
}

SceKernelOpenPsId getPSID(SceVoid)
{
	SceKernelOpenPsId id;
	sceKernelGetOpenPsId(&id);
	
	return id;
}

char * getUnit(SceVoid)
{
	if ((vshSblAimgrIsGenuineVITA() | vshSblAimgrIsGenuineDolce()) && (vshSblAimgrIsCEX()))
		return "CEX unit";
	else if ((vshSblAimgrIsGenuineVITA() | vshSblAimgrIsGenuineDolce()) && (vshSblAimgrIsCEX()) && (vshSysconIsIduMode()))
		return "CEX | IDU unit";
	else if ((vshSblAimgrIsTest()) && (vshSysconIsShowMode()))
		return "Devkit | Show unit";
	else if (vshSblAimgrIsTest())
		return "Testing unit";
	else if (vshSblAimgrIsTool())
		return "Development unit";
	else 
		return "PS Vita TV"; //Because it returns NULL running on a VITA TV
}

const char * getDeviceModel(SceVoid)
{
	if (isPCHX000)
		return concat("PCH-", getVitaModel());
	else if (isPDEL)
		return concat("PDEL-", getVitaModel());
	else if (isPTEL)
		return concat("PTEL-", getVitaModel());
	else if (isVTE1000)
		return "VTE-1000";
	else
		return "Uknown";
}

const char * getBoard(SceVoid)
{
	if ((isPCHX000) && (strcmp(getVitaModel(), "2000") == 0))
		return "USS-1001";
	else if ((isPCHX000) && (strcmp(getVitaModel(), "1000") == 0))
		return "IRS-002";
	else if (isVTE1000)
		return "DOL-1001";
	else if (isPDEL)
		return "IRT-002";
	else
		return "Uknown";
}