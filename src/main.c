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
	
	printStr(false, GREEN, "", "VITAident 0.7\n\n");
	

	/*Kernel Info*/
	
	printStr(true, RED, "Firmware version: ", "%s\n", getFwVersion(false));

	printStr(true, RED, "System version: ", "%s\n", getFwVersion(true));

	printStr(true, RED, "Model version: ", "%s %s (0x%08X)\n", getDeviceModel(), vshSysconHasWWAN()? "3G" : "WiFi", getModel());

	printStr(true, RED, "PS Vita unit:", "%s\n", getUnit());

	printStr(true, RED, "Motherboard: ", "%s\n", getBoard());

	printStr(true, RED, "PS Vita CID: ", "%s\n", getCID());  //Thanks Major_Tom

	/* printStr(true, RED, "PS Vita MCID: ", "%.8s\n", getmCID()); */

	printStr(true, RED, "PSID: ", "%02X\n\n", getPSID()); //Thanks SMOKE
	

	/*System Info*/
	
	printStr(true, YELLOW, "Language: ", "%s\n", getLang());
	
	printStr(true, YELLOW, "MAC address:", "%s\n", getMacAddress());
	
	printStr(true, YELLOW, "IP address: ", "%s\n", getIP());
	
	printStr(true, YELLOW, "ARM clock frequency: ", "%d MHz\n", getClockFrequency(ClockFrequencyType_Cpu));
	
	printStr(true, YELLOW, "BUS clock frequency: ", "%d MHz\n", getClockFrequency(ClockFrequencyType_Bus)); 
	
	//printStr(true, YELLOW, "GPU clock frequency: ", "%d MHz\n", getClockFrequency(ClockFrequencyType_Gpu));
	
	printStr(true, YELLOW, "GPU Xbar clock frequency: ", "%d MHz\n\n", getClockFrequency(ClockFrequencyType_GpuXbar)); 
	
	
	/*Battery Info*/
	
	if (!(getModel() == 0x00020000))//if its a PS Vita TV this info is uselsss.
	{
		printStr(true, BLUE, "Battery percentage: ", "%s (%s)\n", getBatteryPercentage(), getBatteryStatus());
		
		printStr(true, BLUE, "Battery capacity: ", "%s ", getBatteryCapacity());
		printStr(false, BLUE, "(remaining: ", "%s", getBatteryRemainCapacity());
		printStr(false, BLUE, ")\n", "");
		
		int batteryLifeTime = scePowerGetBatteryLifeTime();
		printStr(true, BLUE, "Battery life time: ", "%02dh %02dm ", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
		printStr(false, BLUE, "(SOH: ", " %s", getBatterySOH());
		printStr(false, BLUE, ")\n", "");
		
		printStr(true, BLUE, "Battery voltage: ", "%s V ", getBatteryVoltage());
		printStr(false, BLUE, "(cycle count: ", "%s", getBatteryCycleCount());
		printStr(false, BLUE, ")\n", "");
		
		printStr(true, BLUE, "Udcd state: ", "%s", getUdcdCableState());
		printStr(false, BLUE, "(", "%s", getUdcdChargingState());
		printStr(false, BLUE, ")\n\n", "");
	}
	
	
	/* Misc info */
	
	printStr(true, GREEN, "Username: ", "%s\n", getUser());

	printStr(true, GREEN, "Enter button: ", "%s\n", getEnterButton());
	
	if (vshRemovableMemoryGetCardInsertState() == 1) //Memory card is inserted
	{
		printStr(true, GREEN, "Memory card storage: ", "%s\n", getStorageInfo(0));

		printStr(true, GREEN, "Memory card storage free: ", "%s\n", getStorageInfo(1));
	}
	
	char free_size_string[16], max_size_string[16];
	SceOff freeSize = getPartitionInfo(0, "ur0:");
	SceOff maxSize = getPartitionInfo(1, "ur0:");
	
	getSizeString(free_size_string, freeSize);
	getSizeString(max_size_string, maxSize);
	
	printStr(true, GREEN, "Internal storage: ", "%s\n", max_size_string);

	printStr(true, GREEN, "Internal storage free: ", "%s\n", free_size_string);

	printStr(false, GREEN, "", "\n> Press any key to exit =)");
	
	while (1) 
	{	
		//sceDisplayWaitVblankStart();
		
		sceCtrlPeekBufferPositive(0, &pad, 1);
	
		if (pad.buttons & SCE_CTRL_ANY_KEY)
			break;
	}
	
	termNet();
	termAppUtil();
	sceKernelExitProcess(0);
	
	return 0;
}
