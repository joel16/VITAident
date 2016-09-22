#include "app.h"
#include "fs.h"
#include "graphics.h"
#include "kernel.h"
#include "main.h"
#include "net.h"
#include "power.h"
#include "screenshot.h"
#include "utils.h"

int main(int argc, char *argv[]) 
{
	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));
	
	initAppUtil();
	initNet();
	psvDebugScreenInit();
	
	psvDebugScreenSetFgColor(COLOR_GREEN);
	printf("VITAident 0.3\n\n");
	
	printStarWithColor(COLOR_RED); printf("Firmware version: %.4s\n", getFwVersion());
	printStarWithColor(COLOR_RED); printf("Model version: 0x%08X | %s\n", getModel(), getDeviceType());
	printStarWithColor(COLOR_RED); printf("Language: %s\n", getLang());
	printStarWithColor(COLOR_RED); printf("MAC address: %s\n", getMacAddress());
	printStarWithColor(COLOR_RED); printf("IP address: %s\n", getIP());
	printStarWithColor(COLOR_RED); printf("PS Vita CID: %s\n", getCID()); //Thanks Major_Tom
	printStarWithColor(COLOR_RED); printf("PSID: %02X\n", getPSID()); //Thanks SMOKE
	printStarWithColor(COLOR_RED); printf("PS Vita unit: %s\n\n", getUnit());
	
	printStarWithColor(COLOR_GOLD); printf("ARM clock frequency: %d MHz\n", getClockFrequency(ClockFrequencyType_Cpu));
	printStarWithColor(COLOR_GOLD); printf("BUS clock frequency: %d MHz\n", getClockFrequency(ClockFrequencyType_Bus));
	printStarWithColor(COLOR_GOLD); printf("GPU clock frequency: %d MHz\n", getClockFrequency(ClockFrequencyType_Gpu));
	printStarWithColor(COLOR_GOLD); printf("GPU Xbar clock frequency: %d MHz\n\n", getClockFrequency(ClockFrequencyType_GpuXbar));
	
	if (!(getModel() == 0x00020000))//if its a PS Vita TV this info is uselsss.
	{
		printStarWithColor(COLOR_BLUE); printf("Battery percentage: %s\n", displayBatteryPercentage());
		printStarWithColor(COLOR_BLUE); printf("Battery remaining Capacity: %s\n", GetBatteryRemainCapacity());
		int batteryLifeTime = scePowerGetBatteryLifeTime();
		printStarWithColor(COLOR_BLUE); printf("Battery life time: %02dh %02dm\n", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
		printStarWithColor(COLOR_BLUE); printf("Battery temperature: %s C (%s F)\n", getBatteryTemp(0), getBatteryTemp(1));
		printStarWithColor(COLOR_BLUE); printf("Battery voltage: %s V\n\n", getBatteryVoltage());
	}
	
	printStarWithColor(COLOR_GREEN); printf("Username: %s\n", getUser());
	
	if (vshRemovableMemoryGetCardInsertState())
	{
		printStarWithColor(COLOR_GREEN); printf("Memory card storage: %s\n", getStorageInfo(0));
		printStarWithColor(COLOR_GREEN); printf("Memory card storage free: %s\n", getStorageInfo(1));	
	}
	else
	{
		printStarWithColor(COLOR_GREEN); printf("Internal storage: %s\n", getStorageInfo(0));
		printStarWithColor(COLOR_GREEN); printf("Internal storage free: %s\n", getStorageInfo(1));
	}

	
	psvDebugScreenSetFgColor(COLOR_GREEN);
	printf("\n> Press start to exit =)");
	
	while (1) 
	{
		sceCtrlPeekBufferPositive(0, &pad, 1);
	
		if (pad.buttons & SCE_CTRL_START)
		{
			if (!(dirExists("ux0:/data/VID000016")))
			{
				SceUID dir;
				
				dir = sceIoDopen("ux0:/data/VID000016");
				sceIoMkdir("ux0:/data/VID000016", 0777);
				sceIoDclose(dir);
				
				dir = sceIoDopen("ux0:/data/VID000016/screenshots");
				sceIoMkdir("ux0:/data/VID000016/screenshots", 0777);
				sceIoDclose(dir);
			}
			
			captureScreenshot("ux0:/data/VID000016/screenshots/VITAident.bmp");
			break;
		}
	}
	
	termNet();
	termAppUtil();
	sceKernelExitProcess(0);
	
	return 0;
}
