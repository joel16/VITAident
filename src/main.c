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
	
	//printf("\x1b[0;0H"); //Move the cursor to the top left corner of the screen
	setColor(GREEN); printf("VITAident 0.5\n\n");
	
	setColor(RED); printf("* "); setColor(WHITE); printf("Firmware version: "); 
		setColor(RED); printf("%.4s\n", getFwVersion());//, getHenkakuVersion());
	setColor(RED); printf("* "); setColor(WHITE); printf("Model version: "); 
		setColor(RED); printf("%s %s (0x%08X)\n", getDeviceModel(), vshSysconHasWWAN()? "3G" : "WiFi", getModel());
	setColor(RED); printf("* "); setColor(WHITE); printf("PS Vita unit:"); 
		setColor(RED); printf("%s\n", getUnit());
	setColor(RED); printf("* "); setColor(WHITE); printf("Motherboard: "); 
		setColor(RED); printf("%s\n", getBoard());
	setColor(RED); printf("* "); setColor(WHITE); printf("PS Vita CID: "); 
		setColor(RED); printf("%s\n", getCID());  //Thanks Major_Tom
	/*setColor(RED); printf("* "); setColor(WHITE); printf("PS Vita MCID: "); 
		setColor(RED); printf("%.8s\n", getmCID());*/
	setColor(RED); printf("* "); setColor(WHITE); printf("PSID: "); 
		setColor(RED); printf("%02X\n\n", getPSID()); //Thanks SMOKE
	
	setColor(GOLD); printf("* "); setColor(WHITE); printf("Language: "); 
		setColor(GOLD); printf("%s\n", getLang());
	setColor(GOLD); printf("* "); setColor(WHITE); printf("MAC address:"); 
		setColor(GOLD); printf("%s\n", getMacAddress());
	setColor(GOLD); printf("* "); setColor(WHITE); printf("IP address: ");
		setColor(GOLD); printf("%s\n", getIP());
	setColor(GOLD); printf("* "); setColor(WHITE); printf("ARM clock frequency: "); 
		setColor(GOLD); printf("%d MHz\n", getClockFrequency(ClockFrequencyType_Cpu));
	setColor(GOLD); printf("* "); setColor(WHITE); printf("BUS clock frequency: "); 
		setColor(GOLD); printf("%d MHz\n", getClockFrequency(ClockFrequencyType_Bus)); 
	/*setColor(GOLD); printf("* "); setColor(WHITE); printf("GPU clock frequency: "); 
		setColor(GOLD); printf("%d MHz\n", getClockFrequency(ClockFrequencyType_Gpu));*/
	setColor(GOLD); printf("* "); setColor(WHITE); printf("GPU Xbar clock frequency: "); 
		setColor(GOLD); printf("%d MHz\n\n", getClockFrequency(ClockFrequencyType_GpuXbar)); 
	
	if (!(getModel() == 0x00020000))//if its a PS Vita TV this info is uselsss.
	{
		setColor(BLUE); printf("* "); setColor(WHITE); printf("Battery percentage: "); 
			setColor(BLUE); printf("%s\n", displayBatteryPercentage());
		setColor(BLUE); printf("* "); setColor(WHITE); printf("Battery remaining Capacity: "); 
			setColor(BLUE); printf("%s\n", GetBatteryRemainCapacity());
		int batteryLifeTime = scePowerGetBatteryLifeTime();
		setColor(BLUE); printf("* "); setColor(WHITE); printf("Battery life time: "); 
			setColor(BLUE); printf("%02dh %02dm\n", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
		setColor(BLUE); printf("* "); setColor(WHITE); printf("Battery temperature: "); 
			setColor(BLUE); printf("%s C (%s F)\n", getBatteryTemp(0), getBatteryTemp(1)); 
		setColor(BLUE); printf("* "); setColor(WHITE); printf("Battery voltage: "); 
			setColor(BLUE); printf("%s V\n\n", getBatteryVoltage());
	}
	
	setColor(GREEN); printf("* "); setColor(WHITE); printf("Username: "); 
		setColor(GREEN); printf("%s\n", getUser());
	setColor(GREEN); printf("* "); setColor(WHITE); printf("Enter button: "); 
		setColor(GREEN); printf("%s\n", getEnterButton());
	
	if (vshRemovableMemoryGetCardInsertState() == 1)
	{
		setColor(GREEN); printf("* "); setColor(WHITE); printf("Memory card storage: "); 
			setColor(GREEN); printf("%s\n", getStorageInfo(0));
		setColor(GREEN); printf("* "); setColor(WHITE); printf("Memory card storage free: "); 
			setColor(GREEN); printf("%s\n", getStorageInfo(1));	
	}
	
	char free_size_string[16], max_size_string[16];
	SceOff freeSize = getPartitionInfo(0, "ur0:");
	SceOff maxSize = getPartitionInfo(1, "ur0:");
	
	getSizeString(free_size_string, freeSize);
	getSizeString(max_size_string, maxSize);
	
	setColor(GREEN); printf("* "); setColor(WHITE); printf("Internal storage: "); 
		setColor(GREEN); printf("%s\n", max_size_string);
	setColor(GREEN); printf("* "); setColor(WHITE); printf("Internal storage free: "); 
		setColor(GREEN); printf("%s\n", free_size_string);
	
	/*else
		printf("* "); printf("Memory card not inserted."); //Although this is basically impossible on PCH-1000*/

	setColor(GREEN); printf("\n> Press start to exit =)");
	
	while (1) 
	{	
		//sceDisplayWaitVblankStart();
		
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
