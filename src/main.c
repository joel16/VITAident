#include "graphics.h"
#include "main.h"
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

int getClockFrequency(int type)
{
	if (type == 0)
		return scePowerGetArmClockFrequency();
	else if (type == 1)
		return scePowerGetBusClockFrequency();
	else if (type == 2)
		return scePowerGetGpuClockFrequency();
	else if (type == 3)
		return scePowerGetGpuXbarClockFrequency();
	
	else 
		return 0;
}

const char * batteryStatus()
{
	int batteryStateBool = scePowerIsBatteryCharging();
	
    if (!batteryStateBool) 
        return "Not charging";
    else 
        return "Charging";
}

char * displayBatteryPercentage()
{
	static char percentage[5];
	
	int battery = scePowerGetBatteryLifePercent();
	
	sprintf(percentage, "%d%%", battery);
	
	return percentage;
}

char * GetBatteryRemainCapacity()
{
	static char capacity[10];
	
	int battery = scePowerGetBatteryRemainCapacity();
	
	sprintf(capacity, "%i mAh", battery);
	
	return capacity;
}

char * getBatteryTemp(int type) 
{
	static char c[10];
	sprintf(c, "%0.1f", ((float)scePowerGetBatteryTemp()) / 100);
	
	static char f[10];
	sprintf(f, "%0.1f", ((1.8 * (float)scePowerGetBatteryTemp()) / 100) + 32);
	
	if (type == 0)
		return c;
	else
		return f;
}

char * getBatteryVoltage() 
{
	static char volts[10];
	
	sprintf(volts, "%0.1f" , (((float)scePowerGetBatteryVolt()) / 1000));
	
	return volts;
}

char * getMacAddress()
{
	SceNetInitParam info;
	static char memory[16 * 1024];

	info.memory = memory;
	info.size = sizeof(memory);
	info.flags = 0;

	int netInit = sceNetInit(&info);
	
	static SceNetEtherAddr mac;
	
    static char macAddress[32];
	
	sceNetGetMacAddress(&mac, 0);
	
	sprintf(macAddress, "%02X:%02X:%02X:%02X:%02X:%02X", mac.data[0], mac.data[1], mac.data[2], mac.data[3], mac.data[4], mac.data[5]);
	
	if (netInit >= 0)
		sceNetTerm();

    return macAddress;
}

int main(int argc, char *argv[]) 
{
	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));
	
	psvDebugScreenInit();
	
	psvDebugScreenSetFgColor(COLOR_GREEN);
	printf("VITAident 0.2\n\n");
	
	SceSystemSwVersionParam param;
	param.size = sizeof(SceSystemSwVersionParam);
	sceKernelGetSystemSwVersion(&param);
	printStarWithColor(COLOR_RED); printf("Firmware version: %.4s\n", param.version_string);
	printStarWithColor(COLOR_RED); printf("Model version: 0x%08X\n", sceKernelGetModelForCDialog());
	printStarWithColor(COLOR_RED); printf("Language: %s\n", getLang());
	//printStarWithColor(COLOR_RED); printf("MAC Address: %s\n\n", getMacAddress());
	char CID[32];
	char idps[2 * 16] = {0};
	
	// Get IDPS
	_vshSblAimgrGetConsoleId(CID);
	
	int i = 0;
    for (i = 0; i < 16; i++)
		snprintf(idps + (i * 2), (2 * 16) - (i * 2) + 1, "%02X", CID[i]);
	
	SceKernelOpenPsId id;
	sceKernelGetOpenPsId(&id);
	
	printStarWithColor(COLOR_RED); printf("PS Vita CID: %s\n", idps); //Thanks Major_Tom
	printStarWithColor(COLOR_RED); printf("PSID: %02X\n\n", id); //Thanks SMOKE
	
	printStarWithColor(COLOR_GOLD); printf("ARM clock frequency: %d MHz\n", getClockFrequency(0));
	printStarWithColor(COLOR_GOLD); printf("BUS clock frequency: %d MHz\n", getClockFrequency(1));
	printStarWithColor(COLOR_GOLD); printf("GPU clock frequency: %d MHz\n", getClockFrequency(2));
	printStarWithColor(COLOR_GOLD); printf("GPU Xbar clock frequency: %d MHz\n\n", getClockFrequency(3));
	
	printStarWithColor(COLOR_BLUE); printf("Battery percentage: %s\n", displayBatteryPercentage());
	printStarWithColor(COLOR_BLUE); printf("Battery remaining Capacity: %s\n", GetBatteryRemainCapacity());
	int batteryLifeTime = scePowerGetBatteryLifeTime();
	printStarWithColor(COLOR_BLUE); printf("Battery life time: %02dh %02dm\n", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
	printStarWithColor(COLOR_BLUE); printf("Battery temperature: %s C (%s F)\n", getBatteryTemp(0), getBatteryTemp(1));
	printStarWithColor(COLOR_BLUE); printf("Battery voltage: %s V\n\n", getBatteryVoltage());
	
	uint64_t free_size = 0, max_size = 0;
	sceAppMgrGetDevInfo("ux0:", &max_size, &free_size);
	
	char free_size_string[16], max_size_string[16];
	getSizeString(free_size_string, free_size);
	getSizeString(max_size_string, max_size);
	
	printStarWithColor(COLOR_GREEN); printf("Memory card size: %s\n", max_size_string);
	printStarWithColor(COLOR_GREEN); printf("Memory card free: %s\n", free_size_string);
	
	psvDebugScreenSetFgColor(COLOR_GREEN);
	printf("\n> Press start to exit =)");
	
	while (1) 
	{
		sceCtrlPeekBufferPositive(0, &pad, 1);
	
		if (pad.buttons & SCE_CTRL_START)
			break;
	}
	
	//sceScreenshotEnable();
	
	sceKernelExitProcess(0);
	
	//sceScreenshotDisable();
	return 0;
}
