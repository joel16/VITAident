#include <psp2/apputil.h>
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>
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
	
	sprintf(capacity, "%d", battery);
	
	return capacity;
}

char * getMacAddress()
{
	static SceNetEtherAddr mac;
	
    static char macAddress[32];
	
	sceNetGetMacAddress(&mac, 0);
	
	sprintf(macAddress, "%02X:%02X:%02X:%02X:%02X:%02X", mac.data[0], mac.data[1], mac.data[2], mac.data[3], mac.data[4], mac.data[5]);

    return macAddress;
}

int _vshSblAimgrGetConsoleId(char CID[32]);

char * getCID() //Thanks tomtomdu80
{	
	int i;
	char CID[32];
	static char output[32];
	
	// Get IDPS
	_vshSblAimgrGetConsoleId(CID);
	
	for (i = 0; i < 32; i++) 
	{
		sprintf(output, "%02X", CID[i]);
	}
	
	return output;
}

int main(int argc, char *argv[]) 
{
	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));
	
	psvDebugScreenInit();
	
	printf("VITAident 0.1\n");
	
	printf("* Language: %s\n", getLang());
	printf("* MAC Address: %s\n\n", getMacAddress());
	
	printf("* ARM Clock Frequency: %d MHz\n", getClockFrequency(0));
	printf("* BUS Clock Frequency: %d MHz\n", getClockFrequency(1));
	printf("* GPU Clock Frequency: %d MHz\n\n", getClockFrequency(2));
	printf("* GPU Clock Frequency: %d MHz\n\n", getClockFrequency(3));
		
	printf("* Battery Percentage: %s\n", displayBatteryPercentage());
	printf("* Battery Reamaing Capacity: %s\n", GetBatteryRemainCapacity());
	int batteryLifeTime = scePowerGetBatteryLifeTime();
	printf("* Battery life time: (%02dh%02dm)\n", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
	printf("* Battery Percentage: %s\n", scePowerGetBatteryTemp());
	printf("* Battery Percentage: %s\n", scePowerGetBatteryVolt());
	
	printf("* PS Vita CID: %s\n\n", getCID());
	
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
