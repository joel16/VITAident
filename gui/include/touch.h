/*
		
		Taken from VitaComix by Arkanite.
		A manga/comic book reader for the Playstation Vita
		
		File: touch.c
		
*/
#ifndef TOUCH_H
#define TOUCH_H

#include <vitasdk.h>

#define lerp(value, from_max, to_max) ((((value * 10) * (to_max * 10)) / (from_max * 10)) / 10)

#define touchInRect(x1, x2, y1, y2)  ((Touch_CheckIsPressed()) && (Touch_GetX() >= (x1) && Touch_GetX() <= (x2) && Touch_GetY() >= (y1) && Touch_GetY() <= (y2)))

SceTouchData touch;

typedef struct 
{
	int posX;
	int posY;
	int held;
	int pressed;
	int pressedPrev;
	int released;
	int releasedPrev;
} TouchStateData;

SceInt Touch_Init();

SceInt Touch_GetX(SceVoid);
SceInt Touch_GetY(SceVoid);
SceInt Touch_CheckIsPressed(SceVoid);
SceInt Touch_CheckIsReleased(SceVoid);
SceInt Touch_CheckIsHeld(SceVoid);
SceVoid Touch_Update(SceVoid);

#endif