#include "app.h"
#include "debugScreen.h"
#include "kernel.h"
#include "net.h"
#include "power.h"
#include "regmgr.h"
#include "utils.h"

#define POS(C,L) "\033[" C ";" L "H"

#define SCE_CTRL_ANY_KEY (SCE_CTRL_SELECT | SCE_CTRL_L3 | SCE_CTRL_R3 | SCE_CTRL_START | SCE_CTRL_UP | SCE_CTRL_RIGHT | SCE_CTRL_DOWN | SCE_CTRL_LEFT | \
	SCE_CTRL_LTRIGGER | SCE_CTRL_RTRIGGER | SCE_CTRL_L1 | SCE_CTRL_R1 | SCE_CTRL_TRIANGLE | SCE_CTRL_CIRCLE | SCE_CTRL_CROSS | SCE_CTRL_SQUARE)

int main(int argc, char *argv[]) 
{
	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));
	
	App_InitAppUtil();
	Net_Init();
	psvDebugScreenInit();
	struct{int mutex;SceDisplayFrameBuf*fbuf;} arg = {psvDebugScreenMutex, &psvDebugScreenFrameBuf};
	
	while(1)
	{
		printStr(SCE_FALSE, COLOR_GREEN, POS("0", "0")"", "VITAident 0.7.5\n\n");

		/*Kernel Info*/
		printStr(SCE_TRUE, COLOR_RED, POS("2", "2")"Firmware version: ", "%s     \n", Kernel_GetFirmwareVersion(SCE_FALSE));
		printStr(SCE_TRUE, COLOR_RED, POS("2", "3")"System version: ", "%s     \n", Kernel_GetFirmwareVersion(SCE_TRUE));
		printStr(SCE_TRUE, COLOR_RED, POS("2", "4")"Model version: ", "%s %s     \n", Kernel_GetDeviceModel(), vshSysconHasWWAN()? "3G" : "WiFi");
		printStr(SCE_TRUE, COLOR_RED, POS("2", "5")"PS Vita unit:", "%s     \n", Kernel_GetDeviceUnit());
		printStr(SCE_TRUE, COLOR_RED, POS("2", "6")"Motherboard: ", "%s     \n", Kernel_GetDeviceBoard());
		printStr(SCE_TRUE, COLOR_RED, POS("2", "7")"PS Vita CID: ", "%s     \n", Kernel_GetCID());
		printStr(SCE_TRUE, COLOR_RED, POS("2", "8")"PSID: ", "%s     \n\n", Kernel_GetPSID());

		/*System Info*/
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "10")"Language: ", "%s     \n", App_GetLanguage());
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "11")"MAC address:", "%s     \n", Net_GetMacAddr());
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "12")"IP address: ", "%s     \n", Net_GetIPAddr());
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "13")"Username: ", "%s     \n", App_GetUser());
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "14")"ARM clock frequency: ", "%d MHz     \n", Power_GetClockFrequency(clockFrequencyType_cpu));
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "15")"BUS clock frequency: ", "%d MHz     \n", Power_GetClockFrequency(clockFrequencyType_bus));
		
		printStr(SCE_TRUE, COLOR_YELLOW, POS("2", "16")"GPU clock frequency: ", "%d MHz ", Power_GetClockFrequency(clockFrequencyType_gpu)); 
		printStr(SCE_FALSE, COLOR_YELLOW, "(GPU xbar: ", "%d MHz", Power_GetClockFrequency(clockFrequencyType_gpuXbar));
		printStr(SCE_FALSE, COLOR_YELLOW, ")", "     \n\n");
	
	
		/*Battery Info*/
		if ((Kernel_GetModel() != 0x00020000))// if its a PS Vita TV this info is uselsss.
		{
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "18")"Battery percentage: ", "%s ", Power_GetBatteryPercentage());
			printStr(SCE_FALSE, COLOR_BLUE, "(", "%s", Power_GetBatteryStatus());
			printStr(SCE_FALSE, COLOR_BLUE, ")", "     \n");
			
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "19")"Battery capacity: ", "%s ", Power_GetBatteryCapacity());
			printStr(SCE_FALSE, COLOR_BLUE, "(remaining: ", "%s", Power_GetBatteryRemainCapacity());
			printStr(SCE_FALSE, COLOR_BLUE, ")", "     \n");
		
			int batteryLifeTime = scePowerGetBatteryLifeTime();
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "20")"Battery life time: ", "%02dh %02dm ", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
			printStr(SCE_FALSE, COLOR_BLUE, "(SOH: ", " %s", Power_GetBatterySOH());
			printStr(SCE_FALSE, COLOR_BLUE, ")", "     \n");
		
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "21")"Battery temperature: ", "%s C ", Power_GetBatteryTemp(0));
			printStr(SCE_FALSE, COLOR_BLUE, "(", "%s F", Power_GetBatteryTemp(1));
			printStr(SCE_FALSE, COLOR_BLUE, ")", "     \n");
		
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "22")"Battery voltage: ", "%s V ", Power_GetBatteryVoltage());
			printStr(SCE_FALSE, COLOR_BLUE, "(cycle count: ", "%s", Power_GetBatteryCycleCount());
			printStr(SCE_FALSE, COLOR_BLUE, ")", "     \n");
		
			printStr(SCE_TRUE, COLOR_BLUE, POS("2", "23")"Udcd state: ", "%s ", Power_GetUdcdCableState());
			printStr(SCE_FALSE, COLOR_BLUE, "(", "%s", Power_GetUsbChargingState());
			printStr(SCE_FALSE, COLOR_BLUE, ")", "     \n");
		}
	
		/* Misc info */
		(Kernel_GetModel() == 0x00020000)? printf(POS("2", "18")) : printf(POS("2", "25"));
		printStr(SCE_TRUE, COLOR_GREEN, "Enter button: ", "%s     \n", App_GetEnterButton()? "cross (X)" : "circle (O)");
		
		(Kernel_GetModel() == 0x00020000)? printf(POS("2", "19")) : printf(POS("2", "26"));
		printStr(SCE_TRUE, COLOR_GREEN, "Brightness: ", "%d%%     \n", RegMgr_GetBrightness());

		int volume = 0;
		if (R_SUCCEEDED(sceAVConfigGetSystemVol(&volume)))
		{
			(Kernel_GetModel() == 0x00020000)? printf(POS("2", "20")) : printf(POS("2", "27"));
			printStr(SCE_TRUE, COLOR_GREEN, "Volume: ", "%d     \n",  volume);
		}
	
		if (vshRemovableMemoryGetCardInsertState() == 1) //Memory card is inserted
		{
			(Kernel_GetModel() == 0x00020000)? printf(POS("2", "21")) : printf(POS("2", "28"));
			printStr(SCE_TRUE, COLOR_GREEN, "Memory card storage: ", "%s     \n", App_GetStorageInfo("ux0:", 0));
			
			(Kernel_GetModel() == 0x00020000)? printf(POS("2", "22")) : printf(POS("2", "29"));
			printStr(SCE_TRUE, COLOR_GREEN, "Memory card storage free: ", "%s     \n", App_GetStorageInfo("ux0:", 1));
		}
		else if ((!vshRemovableMemoryGetCardInsertState()) || (isVTE1000))
		{
			(Kernel_GetModel() == 0x00020000)? printf(POS("2", "21")) : printf(POS("2", "28"));
			printStr(SCE_TRUE, COLOR_GREEN, "Internal storage: ", "%s     \n", App_GetStorageInfo("imc0:", 0));
			
			(Kernel_GetModel() == 0x00020000)? printf(POS("2", "22")) : printf(POS("2", "29"));
			printStr(SCE_TRUE, COLOR_GREEN, "Internal storage free: ", "%s     \n", App_GetStorageInfo("imc0:", 1));
		}
		
		(Kernel_GetModel() == 0x00020000)? printf(POS("2", "23")) : printf(POS("2", "30"));
		printStr(SCE_TRUE, COLOR_GREEN, "Internal storage: ", "%s     \n", App_GetStorageInfo("ur0:", 0));
		
		(Kernel_GetModel() == 0x00020000)? printf(POS("2", "24")) : printf(POS("2", "31"));
		printStr(SCE_TRUE, COLOR_GREEN, "Internal storage free: ", "%s     \n", App_GetStorageInfo("ur0:", 1));
		
		(Kernel_GetModel() == 0x00020000)? printf(POS("0", "26")) : printf(POS("0", "32"));
		printStr(SCE_FALSE, COLOR_GREEN, "", "\nPress any key to exit =)");
	
		sceCtrlPeekBufferPositive(0, &pad, 1);
		
		if (pad.buttons & SCE_CTRL_ANY_KEY)
			break;
	}
	
	Net_Term();
	App_TermAppUtil();
	sceKernelExitProcess(0);
	
	return 0;
}
