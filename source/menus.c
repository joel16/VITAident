#include <psp2/ctrl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <vita2d.h>

#include "kernel.h"
#include "plugin.h"
#include "utils.h"

#define BACKGROUND_COLOUR      RGBA8(245, 245, 247, 255)
#define STATUS_BAR_COLOUR      RGBA8(42, 40, 41, 255)
#define MENU_BAR_COLOUR        RGBA8(255, 255, 255, 255)
#define ITEM_COLOUR            RGBA8(0, 0, 0, 255)
#define ITEM_SELECTED_COLOUR   MENU_BAR_COLOUR
#define MENU_SELECTOR_COLOUR   RGBA8(220, 70, 35, 255)
#define MENU_INFO_TITLE_COLOUR RGBA8(144, 137, 129, 255)
#define MENU_INFO_DESC_COLOUR  RGBA8(51, 51, 51, 255)

#define MENU_Y_DIST    50
#define MAX_MENU_ITEMS 8

SceUInt32 pressed = 0;
char factory_fw[8];

static void Menu_DrawText(vita2d_font *font, int x, int y, char *title, const char *text, ...) {
    int title_width = 0;
    title_width = vita2d_font_text_width(font, 25, title);
    vita2d_font_draw_text(font, x, y, MENU_INFO_TITLE_COLOUR, 25, title);
    
    char buffer[128];
    va_list args;
    va_start(args, text);
    vsnprintf(buffer, 128, text, args);
    vita2d_font_draw_text(font, x + title_width + 10, y, MENU_INFO_DESC_COLOUR, 25, buffer);
    va_end(args);
}

static void Menu_KernelInfo(vita2d_font *font) {
    SceUInt real_version = 0, spoofed_version = 0;
    char *model = NULL, *unit = NULL, *CID = NULL, *PSID = NULL;

    Kernel_GetSystemSwVer(&real_version);
    Kernel_GetSystemSwVer2(&spoofed_version);
    Kernel_GetProduct(&model);
    Kernel_GetUnit(&unit);
    Kernel_GetConsoleID(&CID);
    Kernel_GetPSID(&PSID);

    Menu_DrawText(font, 330, 235, "System software version:", "%x", real_version);
    Menu_DrawText(font, 330, 270, "Spoofed software version:", "%x", spoofed_version);
    Menu_DrawText(font, 330, 305, "Factory software version:", "%x", factory_fw);
    Menu_DrawText(font, 330, 340, "Model:", model);
    Menu_DrawText(font, 330, 375, "Unit:", unit);
    Menu_DrawText(font, 330, 410, "Console ID:", CID);
    Menu_DrawText(font, 330, 445, "PS ID:", PSID);
}

static void Menu_SetMax(int *set, int value, int max) {
	if (*set > max)
		*set = value;
}

static void Menu_SetMin(int *set, int value, int min) {
	if (*set < min)
		*set = value;
}

void firmware_string(char string[8], unsigned int version) {
  char a = (version >> 24) & 0xf;
  char b = (version >> 20) & 0xf;
  char c = (version >> 16) & 0xf;
  char d = (version >> 12) & 0xf;

  memset(string, 0, 8);
  string[0] = '0' + a;
  string[1] = '.';
  string[2] = '0' + b;
  string[3] = '0' + c;
  string[4] = '\0';

  if (d) {
    string[4] = '0' + d;
    string[5] = '\0';
  }
}

void Menu_Main(void) {
    vita2d_texture *banner = NULL, *drive_icon = NULL;
    vita2d_font *font = NULL;

    font = vita2d_load_font_file("app0:res/Ubuntu-R.ttf");

    banner = vita2d_load_PNG_file("app0:sce_sys/icon0.png");
    vita2d_texture_set_filters(banner, SCE_GXM_TEXTURE_FILTER_LINEAR, SCE_GXM_TEXTURE_FILTER_LINEAR);

    drive_icon = vita2d_load_PNG_file("app0:res/drive.png");
    vita2d_texture_set_filters(drive_icon, SCE_GXM_TEXTURE_FILTER_LINEAR, SCE_GXM_TEXTURE_FILTER_LINEAR);

    vita2d_set_clear_color(BACKGROUND_COLOUR);

    int font_height = 0, selection = 0;
    font_height = vita2d_font_text_height(font, 25, "VITAident");

    const char *menu_item[] = {
        "Kernel",
        "System",
        "Battery",
        "Storage",
        "WiFi",
        "Misc",
        "Config",
        "PSN",
        "Exit"
    };

    unsigned int factory_version = modoru_get_factory_firmware();
    firmware_string(factory_fw, factory_version);

    while(SCE_TRUE) {
        vita2d_start_drawing();
        vita2d_clear_screen();

        vita2d_draw_rectangle(0, 0, 960, 38, STATUS_BAR_COLOUR);
		vita2d_draw_rectangle(0, 38, 300, 506, MENU_BAR_COLOUR);

        vita2d_font_draw_text(font, 20, ((38 - font_height) / 2) + 20, BACKGROUND_COLOUR, 25, "VITAident v0.8.0");

        vita2d_draw_rectangle(0, 38 + (MENU_Y_DIST * selection), 300, MENU_Y_DIST, MENU_SELECTOR_COLOUR);

        vita2d_draw_texture(banner, 566, 60);

        for (int i = 0; i < MAX_MENU_ITEMS + 1; i++) {
            vita2d_font_draw_text(font, 30, 70 + MENU_Y_DIST * i, selection == i? ITEM_SELECTED_COLOUR : ITEM_COLOUR, 25, menu_item[i]);
        }

        switch(selection) {
            case 0:
                Menu_KernelInfo(font);
                break;
            
            default:
                break;
        }

        vita2d_end_drawing();
        vita2d_swap_buffers();

        Utils_ReadControls();
        
        if (pressed & SCE_CTRL_UP)
            selection--;
        else if (pressed & SCE_CTRL_DOWN)
            selection++;
            
        Menu_SetMax(&selection, 0, MAX_MENU_ITEMS);
        Menu_SetMin(&selection, MAX_MENU_ITEMS, 0);
        
        if (pressed & SCE_CTRL_START)
            break;
    }

    vita2d_wait_rendering_done();
    vita2d_free_texture(drive_icon);
    vita2d_free_texture(banner);
    vita2d_free_font(font);
}
