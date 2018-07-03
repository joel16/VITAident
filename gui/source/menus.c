#include "app.h"
#include "kernel.h"
#include "menus.h"
#include "net.h"
#include "power.h"
#include "regmgr.h"
#include "SDL_helper.h"
#include "touch.h"
#include "utils.h"

#define MENU_Y_DIST 55
#define MAX_ITEMS   8

static int item_height = 0;

static char *devices[] = 
{
	"ur0:",
	"ux0:",
	"imc0:",
	"uma0:",
};

static void Menu_DrawItem(int x, int y, char *item_title, const char* text, ...)
{
	int title_width = 0;
	TTF_SizeText(Ubuntu_R, item_title, &title_width, NULL);
	SDL_DrawText(RENDERER, Ubuntu_R, x, y, MENU_INFO_TITLE_COLOUR, item_title);

    char buffer[256];
	va_list args;
	va_start(args, text);
	vsnprintf(buffer, 256, text, args);
	SDL_DrawText(RENDERER, Ubuntu_R, x + title_width + 20, y, MENU_INFO_DESC_COLOUR, buffer);
	va_end(args);
}

static SceVoid Menu_Kernel(SceVoid)
{
    Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 5, "Firmware version:",  Kernel_GetFirmwareVersion(SCE_FALSE));
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 45, "System version:",  Kernel_GetFirmwareVersion(SCE_TRUE));
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 85, "Model:", "%s %s", Kernel_GetDeviceModel(), vshSysconHasWWAN()? "3G" : "WiFi");
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 125, "Unit:", Kernel_GetDeviceUnit());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 165, "Motherboard:", Kernel_GetDeviceBoard());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 205, "Console ID:", Kernel_GetCID());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 245, "PSID:", Kernel_GetPSID());
}

static SceVoid Menu_System(SceVoid)
{
    Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 5, "Language:",  App_GetLanguage());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 45, "MAC address:",  Net_GetMacAddr());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 85, "ARM clock frequency:", "%d MHz", Power_GetClockFrequency(clockFrequencyType_cpu));
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 125, "BUS clock frequency:", "%d MHz", Power_GetClockFrequency(clockFrequencyType_bus));
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 165, "GPU clock frequency:", "%d MHz", Power_GetClockFrequency(clockFrequencyType_gpu));
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 205, "GPU Xbar clock frequency:", "%d MHz", Power_GetClockFrequency(clockFrequencyType_gpuXbar));
}

static SceVoid Menu_Battery(SceVoid)
{
    int batteryLifeTime = scePowerGetBatteryLifeTime();

    Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 5, "Battery percentage:",  "%s (%s)", Power_GetBatteryPercentage(), Power_GetBatteryStatus());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 45, "Battery capacity:",  "%s (remaining: %s)", Power_GetBatteryCapacity(), Power_GetBatteryRemainCapacity());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 85, "Battery life time:", "%02dh %02dm (SOH: %s)", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60), Power_GetBatterySOH());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 125, "Battery temperature:", "%s C (%s F)", Power_GetBatteryTemp(0), Power_GetBatteryTemp(1));
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 165, "Battery voltage:", "%s V (cycle count: %s)", Power_GetBatteryVoltage(), Power_GetBatteryCycleCount());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 205, "UDCD state:", "%s (%s)", Power_GetUdcdCableState(), Power_GetUsbChargingState());
}

static SceVoid Menu_Storage(SceVoid)
{
	SDL_DrawRect(RENDERER, 300, 40, 660, 504, BACKGROUND_COLOUR);
	
	SDL_DrawImage(RENDERER, drive, 330, 64, 100, 100);
	SDL_DrawRect(RENDERER, 460, 146, 430, 16, STATUS_BAR_COLOUR);
	SDL_DrawRect(RENDERER, 462, 148, 426, 12, BACKGROUND_COLOUR);
	SDL_DrawRect(RENDERER, 462, 148, (((double)App_GetUsedCapacity(devices[0]) / (double)App_GetTotalCapacity(devices[0])) * 426.00), 12, MENU_SELECTOR_COLOUR);
	SDL_DrawText(RENDERER, Ubuntu_R, 460, 64, MENU_INFO_DESC_COLOUR, devices[0]);
    Menu_DrawItem(460, 89, "Free size:",  App_GetStorageInfo(devices[0], 1));
    Menu_DrawItem(460, 114, "Max size:",  App_GetStorageInfo(devices[0], 0));
    
	if (vshRemovableMemoryGetCardInsertState()) // if mem card is inserted
	{
		SDL_DrawImage(RENDERER, drive, 330, 184, 100, 100);
		SDL_DrawRect(RENDERER, 460, 266, 430, 16, STATUS_BAR_COLOUR);
		SDL_DrawRect(RENDERER, 462, 268, 426, 12, BACKGROUND_COLOUR);
		SDL_DrawRect(RENDERER, 462, 268, (((double)App_GetUsedCapacity(devices[1]) / (double)App_GetTotalCapacity(devices[1])) * 426.00), 12, MENU_SELECTOR_COLOUR);
		SDL_DrawText(RENDERER, Ubuntu_R, 460, 184, MENU_INFO_DESC_COLOUR, devices[1]);
        Menu_DrawItem(460, 209, "Free size:",  App_GetStorageInfo(devices[1], 1));
        Menu_DrawItem(460, 234, "Max size:",  App_GetStorageInfo(devices[1], 0));
	}
	
	else if ((!vshRemovableMemoryGetCardInsertState()) || (isVTE1000))
	{
		SDL_DrawImage(RENDERER, drive, 330, 184, 100, 100);
		SDL_DrawRect(RENDERER, 460, 266, 430, 16, STATUS_BAR_COLOUR);
		SDL_DrawRect(RENDERER, 462, 268, 426, 12, BACKGROUND_COLOUR);
		SDL_DrawRect(RENDERER, 462, 268, (((double)App_GetUsedCapacity(devices[2]) / (double)App_GetTotalCapacity(devices[2])) * 426.00), 12, MENU_SELECTOR_COLOUR);
		SDL_DrawText(RENDERER, Ubuntu_R, 460, 184, MENU_INFO_DESC_COLOUR, devices[2]);
        Menu_DrawItem(460, 209, "Free size:",  App_GetStorageInfo(devices[2], 1));
        Menu_DrawItem(460, 234, "Max size:",  App_GetStorageInfo(devices[2], 0));
	}
	
	if (App_GetTotalCapacity(devices[3]))
	{
		SDL_DrawImage(RENDERER, drive, 330, 304, 100, 100);
		SDL_DrawRect(RENDERER, 460, 386, 430, 16, STATUS_BAR_COLOUR);
		SDL_DrawRect(RENDERER, 462, 388, 426, 12, BACKGROUND_COLOUR);
		SDL_DrawRect(RENDERER, 462, 388, (((double)App_GetUsedCapacity(devices[3]) / (double)App_GetTotalCapacity(devices[3])) * 426.00), 12, MENU_SELECTOR_COLOUR);
		SDL_DrawText(RENDERER, Ubuntu_R, 460, 304, MENU_INFO_DESC_COLOUR, devices[3]);
        Menu_DrawItem(460, 329, "Free size:",  App_GetStorageInfo(devices[3], 1));
        Menu_DrawItem(460, 354, "Max size:",  App_GetStorageInfo(devices[3], 0));
	}
}

static SceInt wifiPage = 0;

static SceVoid Menu_WiFi(SceVoid)
{		
	SDL_DrawRect(RENDERER, 300, 40, 660, 504, BACKGROUND_COLOUR);
	
	switch(wifiPage)
	{
		case 0:
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/01/WIFI/", "ssid"), "") != 0)
			{
				SDL_DrawRect(RENDERER, 330, 56, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 58, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 334, 60, MENU_INFO_DESC_COLOUR, "Profile 1:");

                Menu_DrawItem(334, 85, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/01/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/01/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 110, "Password:",  RegMgr_GetInt("/CONFIG/NET/01/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/01/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/01/WIFI/", "wpa_key"));
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/02/WIFI/", "ssid"), "") != 0)
			{
				SDL_DrawRect(RENDERER, 330, 154, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 156, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 334, 158, MENU_INFO_DESC_COLOUR, "Profile 2:");

                Menu_DrawItem(334, 183, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/02/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/02/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 208, "Password:",  RegMgr_GetInt("/CONFIG/NET/02/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/02/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/02/WIFI/", "wpa_key"));
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/03/WIFI/", "ssid"), "") != 0)
			{
				SDL_DrawRect(RENDERER, 330, 252, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 254, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 334, 256, MENU_INFO_DESC_COLOUR, "Profile 3:");

                Menu_DrawItem(334, 281, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/03/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/03/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 306, "Password:",  RegMgr_GetInt("/CONFIG/NET/03/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/03/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/03/WIFI/", "wpa_key"));
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/04/WIFI/", "ssid"), "") != 0)
			{
				SDL_DrawRect(RENDERER, 330, 350, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 352, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 334, 354, MENU_INFO_DESC_COLOUR, "Profile 4:");

                Menu_DrawItem(334, 379, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/04/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/04/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 404, "Password:",  RegMgr_GetInt("/CONFIG/NET/04/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/04/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/04/WIFI/", "wpa_key"));
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/05/WIFI/", "ssid"), "") != 0)
			{
				SDL_DrawRect(RENDERER, 330, 448, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 450, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 334, 452, MENU_INFO_DESC_COLOUR, "Profile 5:");

                Menu_DrawItem(334, 477, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/05/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/05/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 502, "Password:",  RegMgr_GetInt("/CONFIG/NET/05/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/05/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/05/WIFI/", "wpa_key"));
			}
			break;
			
		case 1:
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "ssid"), "") != 0)
			{
                SDL_DrawRect(RENDERER, 330, 56, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 58, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 364, 60, MENU_INFO_DESC_COLOUR, "Profile 6:");

                Menu_DrawItem(334, 85, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/06/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 110, "Password:",  RegMgr_GetInt("/CONFIG/NET/06/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "wpa_key"));
            }
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/07/WIFI/", "ssid"), "") != 0)
			{
                SDL_DrawRect(RENDERER, 330, 154, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 156, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 334, 158, MENU_INFO_DESC_COLOUR, "Profile 7:");

                Menu_DrawItem(334, 183, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/07/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/07/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 208, "Password:",  RegMgr_GetInt("/CONFIG/NET/07/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/07/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/07/WIFI/", "wpa_key"));
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/08/WIFI/", "ssid"), "") != 0)
			{
                SDL_DrawRect(RENDERER, 330, 252, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 254, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 334, 256, MENU_INFO_DESC_COLOUR, "Profile 8:");

                Menu_DrawItem(334, 281, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/08/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/08/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 306, "Password:",  RegMgr_GetInt("/CONFIG/NET/08/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/08/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/08/WIFI/", "wpa_key"));
            }
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/09/WIFI/", "ssid"), "") != 0)
			{
                SDL_DrawRect(RENDERER, 330, 350, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 352, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 334, 354, MENU_INFO_DESC_COLOUR, "Profile 9:");

                Menu_DrawItem(334, 379, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/09/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/09/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 404, "Password:",  RegMgr_GetInt("/CONFIG/NET/09/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/09/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/09/WIFI/", "wpa_key"));
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/10/WIFI/", "ssid"), "") != 0)
			{
                SDL_DrawRect(RENDERER, 330, 448, 600, 80, STATUS_BAR_COLOUR);
				SDL_DrawRect(RENDERER, 332, 450, 596, 76, MENU_BAR_COLOUR);
		
				SDL_DrawText(RENDERER, Ubuntu_R, 334, 452, MENU_INFO_DESC_COLOUR, "Profile 10:");

                Menu_DrawItem(334, 477, "SSID:",  "%s %s", RegMgr_GetStr("/CONFIG/NET/10/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/10/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
                Menu_DrawItem(334, 502, "Password:",  RegMgr_GetInt("/CONFIG/NET/10/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/10/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/10/WIFI/", "wpa_key"));
			}
			break;
	}
}

static SceVoid Menu_Misc(SceVoid)
{
    Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 5, "Username:", App_GetUser());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 45, "IP address:", Net_GetIPAddr());
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 85, "Enter button:", App_GetEnterButton()? "cross (X)" : "circle (O)");

    SceInt fw = 0;
	if (R_SUCCEEDED(fw = sceCompatGetPspSystemSoftwareVersion()))
        Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 125, "PSP firmware version:", "%d.%.2d", fw / 100, fw % 100);
}

static SceVoid Menu_Config(SceVoid)
{
    Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 5, "Airplane mode:", RegMgr_GetInt("/CONFIG/SYSTEM/", "flight_mode")? "enabled" : "disabled");
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 45, "Bluetooth:",  RegMgr_GetInt("/CONFIG/BT/", "bt_enable")? "enabled" : "disabled");
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 85, "WiFi power save:", RegMgr_GetInt("/CONFIG/NET/", "wifi_power_save")? "enabled" : "disabled");
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 125, "Screen lock passcode:", RegMgr_GetStr("/CONFIG/SECURITY/SCREEN_LOCK/", "passcode"));
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 165, "Brightness:", "%d%%", RegMgr_GetBrightness());

    int volume = 0;
	if (R_SUCCEEDED(sceAVConfigGetSystemVol(&volume)))
	    Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 205, "Volume:", "%d", volume);
}

static SceVoid Menu_PSN(SceVoid)
{
    Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 5, "NP:", RegMgr_GetInt("/CONFIG/NP/", "enable_np")? "enabled" : "disabled");
	Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 45, "Login ID:", RegMgr_GetStr("/CONFIG/NP/", "login_id"));
    Menu_DrawItem(330, 200 + ((MENU_Y_DIST - item_height) / 2) + 85, "Password:", RegMgr_GetStr("/CONFIG/NP/", "password"));
}

static int Menu_HandleTouch(int selection)
{
	if (Touch_CheckIsPressed()) 
	{
		if (Touch_GetX() >= 0 && Touch_GetX() <= 300 && Touch_GetY() >= 40 && Touch_GetY() <= 94)
			selection = 0;
		else if (Touch_GetX() >= 0 && Touch_GetX() <= 300 && Touch_GetY() >= 95 && Touch_GetY() <= 149)
			selection = 1;
		else if (Touch_GetX() >= 0 && Touch_GetX() <= 300 && Touch_GetY() >= 150 && Touch_GetY() <= 204)
			selection = 2;
		else if (Touch_GetX() >= 0 && Touch_GetX() <= 300 && Touch_GetY() >= 205 && Touch_GetY() <= 259)
			selection = 3;
		else if (Touch_GetX() >= 0 && Touch_GetX() <= 300 && Touch_GetY() >= 260 && Touch_GetY() <= 314)
			selection = 4;
		else if (Touch_GetX() >= 0 && Touch_GetX() <= 300 && Touch_GetY() >= 315 && Touch_GetY() <= 369)
			selection = 5;
		else if (Touch_GetX() >= 0 && Touch_GetX() <= 300 && Touch_GetY() >= 370 && Touch_GetY() <= 424)
			selection = 6;
		else if (Touch_GetX() >= 0 && Touch_GetX() <= 300 && Touch_GetY() >= 425 && Touch_GetY() <= 479)
			selection = 7;
		else if (Touch_GetX() >= 0 && Touch_GetX() <= 300 && Touch_GetY() >= 480 && Touch_GetY() <= 534)
			selection = 8;
	}
	
	return selection;
}

void Menu_Main(void)
{
	int title_height = 0;
	TTF_SizeText(Ubuntu_R_large, "VITAident", NULL, &title_height);

	TTF_SizeText(Ubuntu_R_large, "Test", NULL, &item_height);

	int banner_width = 0, banner_height = 0;
	SDL_QueryTexture(banner, NULL, NULL, &banner_width, &banner_height);

	int selection = 0;
	
	while (1) 
	{
        SDL_ClearScreen(RENDERER, BACKGROUND_COLOUR);
		SDL_RenderClear(RENDERER);
		SDL_DrawRect(RENDERER, 0, 0, 960, 40, STATUS_BAR_COLOUR);
		SDL_DrawRect(RENDERER, 0, 40, 300, 504, MENU_BAR_COLOUR);

		SDL_DrawText(RENDERER, Ubuntu_R_large, 30, ((40 - title_height) / 2), BACKGROUND_COLOUR, "VITAident");

		SDL_DrawImage(RENDERER, banner, 300 + ((660 - (banner_width)) / 2),  65, banner_width, banner_height);

		SDL_DrawRect(RENDERER, 0, 40 + (MENU_Y_DIST * selection), 300, MENU_Y_DIST, MENU_SELECTOR_COLOUR);

		SDL_DrawText(RENDERER, Ubuntu_R_large, 30, 55, selection == 0? ITEM_SELECTED_COLOUR : ITEM_COLOUR, "Kernel");
		SDL_DrawText(RENDERER, Ubuntu_R_large, 30, 55 * 2, selection == 1? ITEM_SELECTED_COLOUR : ITEM_COLOUR, "System");
		SDL_DrawText(RENDERER, Ubuntu_R_large, 30, 55 * 3, selection == 2? ITEM_SELECTED_COLOUR : ITEM_COLOUR, "Battery");
		SDL_DrawText(RENDERER, Ubuntu_R_large, 30, 55 * 4, selection == 3? ITEM_SELECTED_COLOUR : ITEM_COLOUR, "Storage");
		SDL_DrawText(RENDERER, Ubuntu_R_large, 30, 55 * 5, selection == 4? ITEM_SELECTED_COLOUR : ITEM_COLOUR, "WiFi");
        SDL_DrawText(RENDERER, Ubuntu_R_large, 30, 55 * 6, selection == 5? ITEM_SELECTED_COLOUR : ITEM_COLOUR, "Misc");
        SDL_DrawText(RENDERER, Ubuntu_R_large, 30, 55 * 7, selection == 6? ITEM_SELECTED_COLOUR : ITEM_COLOUR, "Config");
        SDL_DrawText(RENDERER, Ubuntu_R_large, 30, 55 * 8, selection == 7? ITEM_SELECTED_COLOUR : ITEM_COLOUR, "PSN");
        SDL_DrawText(RENDERER, Ubuntu_R_large, 30, 55 * 9, selection == 8? ITEM_SELECTED_COLOUR : ITEM_COLOUR, "Exit");
		
        Utils_HandleControls();
		Touch_Update();

        switch (selection)
		{
			case 0:
				Menu_Kernel();
				break;
            case 1:
                Menu_System();
                break;
            case 2:
                Menu_Battery();
                break;
            case 3:
                Menu_Storage();
                break;
            case 4:
                Menu_WiFi();
				
				if (pressed & SCE_CTRL_LTRIGGER)
				{
					if (wifiPage == 1)
						wifiPage = 0;
				}
				else if (pressed & SCE_CTRL_RTRIGGER)
				{
					if ((wifiPage == 0) && (strcmp(RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "ssid"), "") != 0))
						wifiPage = 1;
				}
                break;
            case 5:
				Menu_Misc();
				break;
			case 6:
				Menu_Config();
				break;
			case 7:
				Menu_PSN();
				break;
        }

        SDL_RenderPresent(RENDERER);
		
		selection = Menu_HandleTouch(selection);

		if (pressed & SCE_CTRL_DOWN)
			selection++; //Moves the selector down
        else if (pressed & SCE_CTRL_UP)
			selection--; //Moves the selector up
        
        if (selection > MAX_ITEMS) 
			selection = 0; //Sets the selection to the first
        if (selection < 0) 
			selection = MAX_ITEMS; //Sets the selection back to last

        if (selection == MAX_ITEMS)
        {
            if ((App_GetEnterButton() == SCE_FALSE) && (pressed & SCE_CTRL_CIRCLE))
				break;
			else if (pressed & SCE_CTRL_CROSS)
				break;
        }
	}
}
