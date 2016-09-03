#include <psp2/apputil.h>
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/net/net.h>
#include <psp2/power.h>
#include <psp2/screenshot.h>
#include <psp2/system_param.h>
#include <stdio.h>
#include <string.h>

#include "graphics.h"

#define printf psvDebugScreenPrintf

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
	/*else if (type == 3)
		return scePowerGetGpuXbarClockFrequency();*/
	
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
	
	sprintf(capacity, "%d", battery);
	
	return capacity;
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

typedef struct {
	SceUInt size;
	SceChar8 version_string[28];
	SceUInt version_value;
	SceUInt unk;
} SceSystemSwVersionParam;

int sceKernelGetSystemSwVersion(SceSystemSwVersionParam *param);

void printStarWithColor(Color color)
{
	psvDebugScreenSetFgColor(color);
	printf("* ");
	psvDebugScreenSetFgColor(COLOR_WHITE);
}

int _vshSblAimgrGetConsoleId(char CID[32]);

int main(int argc, char *argv[]) 
{
	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));
	
	psvDebugScreenInit();
	
	psvDebugScreenSetFgColor(COLOR_GREEN);
	printf("VITAident 0.1\n\n");
	
	SceSystemSwVersionParam param;
	param.size = sizeof(SceSystemSwVersionParam);
	sceKernelGetSystemSwVersion(&param);
	printStarWithColor(COLOR_RED); printf("Firmware version: %.4s\n", param.version_string);
	printStarWithColor(COLOR_RED); printf("Model version: 0x%08X\n", sceKernelGetModelForCDialog());
	printStarWithColor(COLOR_RED); printf("Language: %s\n", getLang());
	//printStarWithColor(COLOR_RED); printf("MAC Address: %s\n\n", getMacAddress());
	printStarWithColor(COLOR_RED); printf("ARM Clock Frequency: %d MHz\n", getClockFrequency(0));
	printStarWithColor(COLOR_RED); printf("BUS Clock Frequency: %d MHz\n", getClockFrequency(1));
	printStarWithColor(COLOR_RED); printf("GPU Clock Frequency: %d MHz\n", getClockFrequency(2));
	//printStarWithColor(COLOR_RED); printf("GPU Clock Frequency: %d MHz\n\n", getClockFrequency(3));

	char CID[32];
	char idps[2 * 16] = {0};
	
	// Get IDPS
	_vshSblAimgrGetConsoleId(CID);
	
    for (int i = 0; i < 16; i++)
		snprintf(idps + (i * 2), (2 * 16) - (i * 2) + 1, "%02X", CID[i]);
	
	printStarWithColor(COLOR_RED); printf("PS Vita CID: %s\n\n", idps);
	
	printStarWithColor(COLOR_YELLOW); printf("Battery Percentage: %s\n", displayBatteryPercentage());
	printStarWithColor(COLOR_YELLOW); printf("Battery Reamaing Capacity: %s\n", GetBatteryRemainCapacity());
	int batteryLifeTime = scePowerGetBatteryLifeTime();
	printStarWithColor(COLOR_YELLOW); printf("Battery life time: %02dh %02dm\n\n", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
	//printStarWithColor(COLOR_YELLOW); printf("Battery Percentage: %s\n", scePowerGetBatteryTemp());
	//printStarWithColor(COLOR_YELLOW); printf("Battery Percentage: %s\n", scePowerGetBatteryVolt());
	
	psvDebugScreenSetFgColor(COLOR_GREEN);
	printf("> Press start to exit =)");
	
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
