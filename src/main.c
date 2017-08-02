#include "app.h"
#include "fs.h"
#include "graphics.h"
#include "kernel.h"
#include "main.h"
#include "net.h"
#include "power.h"
#include "utils.h"

int main(int argc, char *argv[]) 
{
	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));
	
	initAppUtil();
	initNet();
	psvDebugScreenInit();
	
	printStr(SCE_FALSE, GREEN, "", "VITAident 0.7.4\n\n");

	/*Kernel Info*/
	
	printStr(SCE_TRUE, RED, "Firmware version: ", "%s\n", getFwVersion(SCE_FALSE));

	printStr(SCE_TRUE, RED, "System version: ", "%s\n", getFwVersion(SCE_TRUE));

	printStr(SCE_TRUE, RED, "Model version: ", "%s %s (0x%08X)\n", getDeviceModel(), vshSysconHasWWAN()? "3G" : "WiFi", getModel());

	printStr(SCE_TRUE, RED, "PS Vita unit:", "%s\n", getUnit());

	printStr(SCE_TRUE, RED, "Motherboard: ", "%s\n", getBoard());

	printStr(SCE_TRUE, RED, "PS Vita CID: ", "%s\n", getCID());  //Thanks Major_Tom

	/* printStr(SCE_TRUE, RED, "PS Vita MCID: ", "%.8s\n", getmCID()); */

	printStr(SCE_TRUE, RED, "PSID: ", "%02X\n\n", getPSID()); //Thanks SMOKE
	

	/*System Info*/
	
	printStr(SCE_TRUE, YELLOW, "Language: ", "%s\n", getLang());
	
	printStr(SCE_TRUE, YELLOW, "MAC address:", "%s\n", getMacAddress());
	
	printStr(SCE_TRUE, YELLOW, "IP address: ", "%s\n", getIP());
	
	printStr(SCE_TRUE, YELLOW, "Username: ", "%s\n", getUser());
	
	printStr(SCE_TRUE, YELLOW, "ARM clock frequency: ", "%d MHz\n", getClockFrequency(clockFrequencyType_cpu));
	
	printStr(SCE_TRUE, YELLOW, "BUS clock frequency: ", "%d MHz\n", getClockFrequency(clockFrequencyType_bus));
	
	printStr(SCE_TRUE, YELLOW, "GPU clock frequency: ", "%d MHz ", getClockFrequency(clockFrequencyType_gpu)); 
	printStr(SCE_FALSE, YELLOW, "(GPU xbar: ", "%d MHz", getClockFrequency(clockFrequencyType_gpuXbar));
	printStr(SCE_FALSE, YELLOW, ")\n\n", "");
	
	
	/*Battery Info*/
	
	if (!(getModel() == 0x00020000))//if its a PS Vita TV this info is uselsss.
	{
		printStr(SCE_TRUE, BLUE, "Battery percentage: ", "%s ", getBatteryPercentage());
		printStr(SCE_FALSE, BLUE, "(", "%s", getBatteryStatus());
		printStr(SCE_FALSE, BLUE, ")\n", "");
		
		printStr(SCE_TRUE, BLUE, "Battery capacity: ", "%s ", getBatteryCapacity());
		printStr(SCE_FALSE, BLUE, "(remaining: ", "%s", getBatteryRemainCapacity());
		printStr(SCE_FALSE, BLUE, ")\n", "");
		
		int batteryLifeTime = scePowerGetBatteryLifeTime();
		printStr(SCE_TRUE, BLUE, "Battery life time: ", "%02dh %02dm ", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
		printStr(SCE_FALSE, BLUE, "(SOH: ", " %s", getBatterySOH());
		printStr(SCE_FALSE, BLUE, ")\n", "");
		
		printStr(SCE_TRUE, BLUE, "Battery temperature: ", "%s C ", getBatteryTemp(0));
		printStr(SCE_FALSE, BLUE, "(", "%s F", getBatteryTemp(1));
		printStr(SCE_FALSE, BLUE, ")\n", "");
		
		printStr(SCE_TRUE, BLUE, "Battery voltage: ", "%s V ", getBatteryVoltage());
		printStr(SCE_FALSE, BLUE, "(cycle count: ", "%s", getBatteryCycleCount());
		printStr(SCE_FALSE, BLUE, ")\n", "");
		
		printStr(SCE_TRUE, BLUE, "Udcd state: ", "%s ", getUdcdCableState());
		printStr(SCE_FALSE, BLUE, "(", "%s", getUsbChargingState());
		printStr(SCE_FALSE, BLUE, ")\n\n", "");
	}
	
	
	/* Misc info */

	printStr(SCE_TRUE, GREEN, "Enter button: ", "%s\n", getEnterButton()? "Cross (X)" : "Circle (O)");
	
	printStr(SCE_TRUE, GREEN, "Brightness: ", "%d%%\n",  getBrightness());
	printStr(SCE_TRUE, GREEN, "Volume: ", "%d%%\n",  getVolume());
	
	if (vshRemovableMemoryGetCardInsertState() == 1) //Memory card is inserted
	{
		printStr(SCE_TRUE, GREEN, "Memory card storage: ", "%s\n", getStorageInfo(0));

		printStr(SCE_TRUE, GREEN, "Memory card storage free: ", "%s\n", getStorageInfo(1));
	}
	
	char free_size_string[16], max_size_string[16];
	SceOff freeSize = getPartitionInfo(0, "ur0:");
	SceOff maxSize = getPartitionInfo(1, "ur0:");
	
	getSizeString(free_size_string, freeSize);
	getSizeString(max_size_string, maxSize);
	
	printStr(SCE_TRUE, GREEN, "Internal storage: ", "%s\n", max_size_string);

	printStr(SCE_TRUE, GREEN, "Internal storage free: ", "%s\n", free_size_string);

	printStr(SCE_FALSE, GREEN, "", "\n> Press any key to exit =)");
	
	while (1) 
	{	
		sceCtrlPeekBufferPositive(0, &pad, 1);
		
		if (pad.buttons & SCE_CTRL_ANY_KEY)
			break;
	}
	
	termNet();
	termAppUtil();
	sceKernelExitProcess(0);
	
	return 0;
}
