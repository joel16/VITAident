#include <psp2/kernel/processmgr.h>
#include <psp2/power.h>
#include <psp2/screenshot.h>
#include <stdio.h>

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

int main(int argc, char *argv[]) 
{
	printf("VITAident 0.1\n");
	
	printf("\x1b[34m*\x1b[0m Battery Status: %s\n", batteryStatus());
	printf("\x1b[34m*\x1b[0m Battery Percentage: %s\n\n", displayBatteryPercentage);
	
	sceScreenshotEnable();
	
	sceKernelExitProcess(0);
	sceScreenshotDisable();
	return 0;
}
