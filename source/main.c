#include "app.h"
#include "fs.h"
#include "debugScreen.h"
#include "kernel.h"
#include "net.h"
#include "power.h"
#include "utils.h"

#define POS(C,L) "\033[" C ";" L "H"

int main(int argc, char *argv[]) 
{
	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));
	
	initAppUtil();
	initNet();
	psvDebugScreenInit();
	struct{int mutex;SceDisplayFrameBuf*fbuf;} arg = {psvDebugScreenMutex, &psvDebugScreenFrameBuf};
	
	while(1)
	{
		printStr(SCE_FALSE, COLOR_GREEN, POS("0", "0")"", "VITAident 0.7.4\n\n");

		/*Kernel Info*/
		printStr(SCE_TRUE, COLOR_RED, POS("2", "2")"Firmware version: ", "%s     \n", getFwVersion(SCE_FALSE));
		printStr(SCE_TRUE, COLOR_RED, POS("2", "3")"System version: ", "%s     \n", getFwVersion(SCE_TRUE));
		printStr(SCE_TRUE, COLOR_RED, POS("2", "4")"Model version: ", "%s %s (0x%08X)     \n", getDeviceModel(), vshSysconHasWWAN()? "3G" : "WiFi", getModel());
		printStr(SCE_TRUE, COLOR_RED, POS("2", "5")"PS Vita unit:", "%s     \n", getUnit());
		printStr(SCE_TRUE, COLOR_RED, POS("2", "6")"Motherboard: ", "%s     \n", getBoard());
		printStr(SCE_TRUE, COLOR_RED, POS("2", "7")"PS Vita CID: ", "%s     \n", getCID());  //Thanks Major_Tom
		printStr(SCE_TRUE, COLOR_RED, POS("2", "8")"PSID: ", "%02X     \n\n", getPSID()); //Thanks SMOKE

		/*System Info*/
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "10")"Language: ", "%s     \n", getLang());
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "11")"MAC address:", "%s     \n", getMacAddress());
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "12")"IP address: ", "%s     \n", getIP());
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "13")"Username: ", "%s     \n", getUser());
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "14")"ARM clock frequency: ", "%d MHz     \n", getClockFrequency(clockFrequencyType_cpu));
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "15")"BUS clock frequency: ", "%d MHz     \n", getClockFrequency(clockFrequencyType_bus));
		
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "16")"GPU clock frequency: ", "%d MHz ", getClockFrequency(clockFrequencyType_gpu)); 
		printStr(SCE_FALSE, COLOR_YELLOW, "(GPU xbar: ", "%d MHz", getClockFrequency(clockFrequencyType_gpuXbar));
		printStr(SCE_FALSE, COLOR_YELLOW, ")     \n\n", "");
	
	
		/*Battery Info*/
		if ((getModel() != 0x00020000))//if its a PS Vita TV this info is uselsss.
		{
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "18")"Battery percentage: ", "%s ", getBatteryPercentage());
			printStr(SCE_FALSE, COLOR_BLUE, "(", "%s", getBatteryStatus());
			printStr(SCE_FALSE, COLOR_BLUE, ")     \n", "");
			
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "19")"Battery capacity: ", "%s ", getBatteryCapacity());
			printStr(SCE_FALSE, COLOR_BLUE, "(remaining: ", "%s", getBatteryRemainCapacity());
			printStr(SCE_FALSE, COLOR_BLUE, ")     \n", "");
		
			int batteryLifeTime = scePowerGetBatteryLifeTime();
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "20")"Battery life time: ", "%02dh %02dm ", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
			printStr(SCE_FALSE, COLOR_BLUE, "(SOH: ", " %s", getBatterySOH());
			printStr(SCE_FALSE, COLOR_BLUE, ")     \n", "");
		
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "21")"Battery temperature: ", "%s C ", getBatteryTemp(0));
			printStr(SCE_FALSE, COLOR_BLUE, "(", "%s F", getBatteryTemp(1));
			printStr(SCE_FALSE, COLOR_BLUE, ")     \n", "");
		
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "22")"Battery voltage: ", "%s V ", getBatteryVoltage());
			printStr(SCE_FALSE, COLOR_BLUE, "(cycle count: ", "%s", getBatteryCycleCount());
			printStr(SCE_FALSE, COLOR_BLUE, ")     \n", "");
		
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "23")"Udcd state: ", "%s ", getUdcdCableState());
			printStr(SCE_FALSE, COLOR_BLUE, "(", "%s", getUsbChargingState());
			printStr(SCE_FALSE, COLOR_BLUE, ")     \n", "");
		}
	
		/* Misc info */
		(getModel() == 0x00020000)? printf(POS("2", "18")) : printf(POS("2", "25"));
		printStr(SCE_TRUE, COLOR_GREEN, "Enter button: ", "%s     \n", getEnterButton()? "Cross (X)" : "Circle (O)");
		
		(getModel() == 0x00020000)? printf(POS("2", "19")) : printf(POS("2", "26"));
		printStr(SCE_TRUE, COLOR_GREEN, "Brightness: ", "%d%%     \n",  getBrightness());

		int volume = 0;
		if (R_SUCCEEDED(sceAVConfigGetSystemVol(&volume)))
		{
			(getModel() == 0x00020000)? printf(POS("2", "20")) : printf(POS("2", "27"));
			printStr(SCE_TRUE, COLOR_GREEN, "Volume: ", "%d     \n",  volume);
		}
	
		if (vshRemovableMemoryGetCardInsertState() == 1) //Memory card is inserted
		{
			(getModel() == 0x00020000)? printf(POS("2", "21")) : printf(POS("2", "28"));
			printStr(SCE_TRUE, COLOR_GREEN, "Memory card storage: ", "%s     \n", getStorageInfo("ux0:", 0));
			
			(getModel() == 0x00020000)? printf(POS("2", "22")) : printf(POS("2", "29"));
			printStr(SCE_TRUE, COLOR_GREEN, "Memory card storage free: ", "%s     \n", getStorageInfo("ux0:", 1));
		}
		else if ((!vshRemovableMemoryGetCardInsertState()) && ((strcmp(getVitaModel(), "1000") == 0) || (isVTE1000)))
		{
			(getModel() == 0x00020000)? printf(POS("2", "21")) : printf(POS("2", "28"));
			printStr(SCE_TRUE, COLOR_GREEN, "Internal storage: ", "%s     \n", getStorageInfo("imc0:", 0));
			
			(getModel() == 0x00020000)? printf(POS("2", "22")) : printf(POS("2", "29"));
			printStr(SCE_TRUE, COLOR_GREEN, "Internal storage free: ", "%s     \n", getStorageInfo("imc0:", 1));
		}
		
		(getModel() == 0x00020000)? printf(POS("2", "23")) : printf(POS("2", "30"));
		printStr(SCE_TRUE, COLOR_GREEN, "Internal storage: ", "%s     \n", getStorageInfo("ur0:", 0));
		
		(getModel() == 0x00020000)? printf(POS("2", "24")) : printf(POS("2", "31"));
		printStr(SCE_TRUE, COLOR_GREEN, "Internal storage free: ", "%s     \n", getStorageInfo("ur0:", 1));
		
		(getModel() == 0x00020000)? printf(POS("0", "26")) : printf(POS("0", "32"));
		printStr(SCE_FALSE, COLOR_GREEN, "", "\nPress any key to exit =)");
	
		sceCtrlPeekBufferPositive(0, &pad, 1);
		
		if (pad.buttons & SCE_CTRL_ANY_KEY)
			break;
	}
	
	termNet();
	termAppUtil();
	sceKernelExitProcess(0);
	
	return 0;
}
