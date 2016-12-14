#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char u8;
typedef unsigned u32;
typedef u32 Color;

// allocates memory for framebuffer and initializes it
void psvDebugScreenInit();

// clears screen with a given color
void psvDebugScreenClear(int bg_color);

// printf to the screen
void psvDebugScreenPrintf(const char *format, ...);

// set foreground (text) color
Color psvDebugScreenSetFgColor(Color color);

// set background color
Color psvDebugScreenSetBgColor(Color color);

void *psvDebugScreenGetVram();
int psvDebugScreenGetX();
int psvDebugScreenGetY();
void psvDebugScreenSetXY();

enum {
	CYAN = 0xFFFFFF00,
	GOLD = 0xFF0B86B8,
	WHITE = 0xFFFFFFFF,
	BLACK = 0xFF000000,
	RED = 0xFF0000FF,
	BLUE = 0xFFE16941,
	YELLOW = 0xFF00FFFF,
	GREY = 0xFF808080,
	GREEN = 0xFF00FF00,
};

#ifdef __cplusplus
}
#endif

#endif /* GRAPHICS_H */

