#include "fs.h"
#include "kernel.h"
#include "utils.h"

char * getFwVersion(SceBool spoofed)
{
	static char version[16];
	unsigned char str[32] = "";
	
	if (spoofed == SCE_TRUE)
	{
		SceKernelFwInfo info;
		info.size = sizeof(SceKernelFwInfo);
		sceKernelGetSystemSwVersion(&info);
	
		snprintf(version, 16, "%s", info.versionString);
		
		return version;
	}
	
	SceUID file = sceIoOpen("os0:psp2bootconfig.skprx", SCE_O_RDONLY, 0777);
	
	if(file < 0)
		return "Unknown firmware";
	
	sceIoLseek(file, 146, SCE_SEEK_SET);
	sceIoRead(file, &str, 8);
	sceIoClose(file);
		
	snprintf(version, 8, "%x.%02x", str[3], str[2]);
	
	return version;
}

char getHenkakuVersion(SceVoid)
{
	char henkakuVersion[10];
	
	SceKernelFwInfo info;
	info.size = sizeof(SceKernelFwInfo);
	sceKernelGetSystemSwVersion(&info);
	
	strcpy(henkakuVersion, (char *)info.versionString);
	
	return henkakuVersion[(strlen(henkakuVersion) - 1)];
}

SceInt getModel(SceVoid)
{
	return sceKernelGetModelForCDialog();
}

char * getCID(SceVoid)
{
	char CID[32];
	static char idps[32];
	
	// Get IDPS
	_vshSblAimgrGetConsoleId(CID);
	
	SceInt i = 0;
	for (i = 0; i < 16; i++)
		snprintf(idps + (i * 2), (32) - (i * 2) + 1, "%02X", CID[i]);
	
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
	else if(isVTE1000)
		return "DOL-1001";
	else if (isPDEL)
		return "IRT-002";
	else
		return "Uknown";
}