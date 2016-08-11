#include <psp2/kernel/processmgr.h>
#include <psp2/net/net.h>
#include <psp2/power.h>
#include <psp2/screenshot.h>
#include <stdio.h>

int getClockFreqeuncy(int type)
{
	if (type == 0)
		return scePowerGetArmClockFrequency();
	else if (type == 1)
		return scePowerGetBusClockFrequency();
	else if (type == 2)
		return scePowerGetGpuClockFrequency();
	
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

/*char * GetBatteryRemainCapacity()
{
	int batttery = scePowerGetBatteryRemainCapacity();
	
	return "";
}*/

static SceNetEtherAddr mac;

char * getMacAddress()
{
    static char macAddress[32];
	
	sprintf(macAddress, "%02X:%02X:%02X:%02X:%02X:%02X", mac.data[0], mac.data[1], mac.data[2], mac.data[3], mac.data[4], mac.data[5]);

    return macAddress;
}

int main(int argc, char *argv[]) 
{
	printf("\x1b[32mVITAident 0.1\x1b[0m\n");
	
	printf("\x1b[33m*\x1b[0m ARM Clock Frequency: %d MHz\n", getClockFreqeuncy(0));
	printf("\x1b[33m*\x1b[0m BUS Clock Frequency: %d MHz\n", getClockFreqeuncy(1));
	printf("\x1b[33m*\x1b[0m GPU Clock Frequency: %d MHz\n\n", getClockFreqeuncy(2));
	
	printf("\x1b[31m*\x1b[0m MAC Address: %s\n\n", getMacAddress());
	
	printf("\x1b[34m*\x1b[0m Battery Status: %s\n", batteryStatus());
	printf("\x1b[34m*\x1b[0m Battery Percentage: %s\n\n", displayBatteryPercentage());
	
	//sceScreenshotEnable();
	
	sceKernelExitProcess(0);
	
	//sceScreenshotDisable();
	return 0;
}
