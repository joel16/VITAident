#include "fs.h"
#include "kernel.h"
#include "utils.h"

char * getFwVersion()
{
	static char version[10];
	
	SceSystemSwVersionParam param;
	param.size = sizeof(SceSystemSwVersionParam);
	sceKernelGetSystemSwVersion(&param);
	
	sprintf(version, "%s", param.version_string);
	
	return version;
}

char getHenkakuVersion()
{
	char henkakuVersion[10];
	
	SceSystemSwVersionParam param;
	param.size = sizeof(SceSystemSwVersionParam);
	sceKernelGetSystemSwVersion(&param);
	
	strcpy(henkakuVersion, (char *) param.version_string);
	
	return henkakuVersion[(strlen(henkakuVersion) - 1)];
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

char * getmCID()
{
	char mCID[32];
	static char id[2 * 16] = {0};

	_vshAppMgrCloudDataGetMcId(mCID);
	
	int i = 0;
	for (i = 0; i < 16; i++)
		snprintf(id + (i * 2), (2 * 16) - (i * 2) + 1, "%02X", mCID[i]);
	
	return id;
}

SceKernelOpenPsId getPSID()
{
	SceKernelOpenPsId id;
	sceKernelGetOpenPsId(&id);
	
	return id;
}

char * getUnit()
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

const char * getDeviceModel()
{
	if ((vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()))
		return concat("PCH-", getVitaModel());
	else if ((vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineDolce()))
		return "VTE-1000";
	else if ((!vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (vshSblAimgrIsDEX()))
		return concat("PTEL-", getVitaModel());
	else if (vshSblAimgrIsTool())
		return concat("PDEL-", getVitaModel());
	else
		return "Uknown";
}

const char * getBoard()
{
	if (strcmp(getVitaModel(), "2000") == 0)
		return "USS-1001";
	else if (strcmp(getVitaModel(), "1000") == 0)
		return "IRS-002";
	else if(vshSblAimgrIsGenuineDolce())
		return "DOL-1001";
	else
		return "Uknown";
}