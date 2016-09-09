#include "screenshot.h"

void captureScreenshot(char* path) //Heaviy relies on Rinnegatamante's RIN cheat source for now.
{
	SceDisplayFrameBuf param;
	param.size = sizeof(SceDisplayFrameBuf);
	
	sceDisplayWaitVblankStart();
	sceDisplayGetFrameBuf(&param, SCE_DISPLAY_SETBUF_NEXTFRAME);
	
	char filename[256];
	sprintf(filename, "%s", path);
	int fd = sceIoOpen(filename, SCE_O_CREAT|SCE_O_WRONLY, 0777);
	
	uint8_t* bmp_content;
	bmp_content = (uint8_t*)malloc(((param.pitch*param.height)<<2)+0x36);
	memset(bmp_content, 0, 0x36);
	
	*(uint16_t*)&bmp_content[0x0] = 0x4D42;
	*(uint32_t*)&bmp_content[0x2] = ((param.pitch*param.height)<<2)+0x36;
	*(uint32_t*)&bmp_content[0xA] = 0x36;
	*(uint32_t*)&bmp_content[0xE] = 0x28;
	*(uint32_t*)&bmp_content[0x12] = param.pitch;
	*(uint32_t*)&bmp_content[0x16] = param.height;
	*(uint32_t*)&bmp_content[0x1A] = 0x00200001;
	*(uint32_t*)&bmp_content[0x22] = ((param.pitch*param.height)<<2);
	
	int x, y;
	uint32_t* buffer = (uint32_t*)bmp_content;
	uint32_t* framebuf = (uint32_t*)param.base;
	
	for (y = 0; y<param.height; y++)
	{
		for (x = 0; x<param.pitch; x++)
		{
			buffer[x+y*param.pitch+0x36] = framebuf[x+(param.height-y)*param.pitch];
			uint8_t* clr = (uint8_t*)&buffer[x+y*param.pitch+0x36];
			uint8_t r = clr[1];
			clr[1] = clr[3];
			clr[3] = r;
		}
	}
	
	sceIoWrite(fd, bmp_content, ((param.pitch*param.height)<<2)+0x36);
	free(bmp_content);
		
	sceIoClose(fd);
}