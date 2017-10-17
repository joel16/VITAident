#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "graphics.h"

enum {
	SCREEN_WIDTH = 960,
	SCREEN_HEIGHT = 544,
	LINE_SIZE = 960,
	FRAMEBUFFER_SIZE = 2 * 1024 * 1024,
	FRAMEBUFFER_ALIGNMENT = 256 * 1024
};

typedef union
{
	SceInt rgba;
	struct
	{
		char r;
		char g;
		char b;
		char a;
	} c;
} color_t;

extern SceUChar8 psvDebugScreenFont[];
void* g_vram_base;
static SceInt gX = 0;
static SceInt gY = 0;

static Color g_fg_color;
static Color g_bg_color;

static Color* getVramDisplayBuffer()
{
	Color* vram = (Color*) g_vram_base;
	return vram;
}

void *psvDebugScreenGetVram() {
	return g_vram_base;
}

SceInt psvDebugScreenGetX() {
	return gX;
}

SceInt psvDebugScreenGetY() {
	return gY;
}

void psvDebugScreenSetXY(SceInt x, SceInt y) {
	gX = x;
	gY = y;
}

 // #define LOG(args...)  		vita_logf (__FILE__, __LINE__, args)  ///< Write a log entry

SceInt g_log_mutex;

void psvDebugScreenInit() {
	g_log_mutex = sceKernelCreateMutex("log_mutex", 0, 0, NULL);

	SceKernelAllocMemBlockOpt opt = { 0 };
	opt.size = sizeof(opt);
	opt.attr = 0x00000004;
	opt.alignment = FRAMEBUFFER_ALIGNMENT;
	SceUID displayblock = sceKernelAllocMemBlock("display", SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW, FRAMEBUFFER_SIZE, &opt);
	printf("displayblock: 0x%08x", displayblock);
	void *base;
	sceKernelGetMemBlockBase(displayblock, &base);
	// LOG("base: 0x%08x", base);

	SceDisplayFrameBuf framebuf = { 0 };
	framebuf.size = sizeof(framebuf);
	framebuf.base = base;
	framebuf.pitch = SCREEN_WIDTH;
	framebuf.pixelformat = SCE_DISPLAY_PIXELFORMAT_A8B8G8R8;
	framebuf.width = SCREEN_WIDTH;
	framebuf.height = SCREEN_HEIGHT;

	g_vram_base = base;

	sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);

	g_fg_color = 0xFFFFFFFF;
	g_bg_color = 0x00000000;
}

void psvDebugScreenClear(SceInt bg_color)
{
	gX = gY = 0;
	color_t *pixel = (color_t *)getVramDisplayBuffer();
	for(SceInt i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		pixel->rgba = bg_color;
		pixel++;
	}
}

void printTextScreen(const char * text)
{
	SceInt c, i, j, l;
	SceUChar8 *font;
	Color *vram_ptr;
	Color *vram;

	for (c = 0; c < strlen(text); c++) {
		if (gX + 16 > SCREEN_WIDTH) {
			gY += 16;
			gX = 0;
		}
		if (gY + 16 > SCREEN_HEIGHT) {
			gY = 0;
			psvDebugScreenClear(g_bg_color);
		}
		char ch = text[c];
		if (ch == '\n') {
			gX = 0;
			gY += 16;
			continue;
		} else if (ch == '\r') {
			gX = 0;
			continue;
		}

		vram = getVramDisplayBuffer() + gX + gY * LINE_SIZE;

		font = &psvDebugScreenFont[(SceInt)ch * 8];
		for (i = l = 0; i < 8; i++, l += 8, font++) {
			vram_ptr  = vram;
			for (j = 0; j < 8; j++) {
				if ((*font & (128 >> j))) {
					*(SceUInt32 *)(vram_ptr) = g_fg_color;
					*(SceUInt32 *)(vram_ptr + 1) = g_fg_color;
					*(SceUInt32 *)(vram_ptr + LINE_SIZE) = g_fg_color;
					*(SceUInt32 *)(vram_ptr + LINE_SIZE + 1) = g_fg_color;
				} else {
					*(SceUInt32 *)(vram_ptr) = g_bg_color;
					*(SceUInt32 *)(vram_ptr + 1) = g_bg_color;
					*(SceUInt32 *)(vram_ptr + LINE_SIZE) = g_bg_color;
					*(SceUInt32 *)(vram_ptr + LINE_SIZE + 1) = g_bg_color;
				}
				vram_ptr += 2;
			}
			vram += 2 * LINE_SIZE;
		}
		gX += 16;
	}
}

void psvDebugScreenPrintf(const char *format, ...) {
	char buf[1024];

	sceKernelLockMutex(g_log_mutex, 1, NULL);

	va_list opt;
	va_start(opt, format);
	vsnprintf(buf, sizeof(buf), format, opt);
	printTextScreen(buf);
	va_end(opt);

	sceKernelUnlockMutex(g_log_mutex, 1);
}

Color psvDebugScreenSetFgColor(Color color) {
	Color prev_color = g_fg_color;
	g_fg_color = color;
	return prev_color;
}

Color psvDebugScreenSetBgColor(Color color) {
	Color prev_color = g_bg_color;
	g_bg_color = color;
	return prev_color;
}