/*
		
		Taken from VitaComix by Arkanite.
		A manga/comic book reader for the Playstation Vita
		
		File: touch.c
		
*/
#ifndef TOUCH_H
#define TOUCH_H

#include <vitasdk.h>

#define lerp(value, from_max, to_max) ((((value * 10) * (to_max * 10)) / (from_max * 10)) / 10)

#define touchInRect(x1, x2, y1, y2)  ((touchCheckIsPressed()) && (touchGetX() >= (x1) && touchGetX() <= (x2) && touchGetY() >= (y1) && touchGetY() <= (y2)))

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
} touchStateData;

touchStateData* touchState;

int initTouch();

int touchGetX();
int touchGetY();
int touchCheckIsPressed();
int touchCheckIsReleased();
int touchCheckIsHeld();
void touchUpdate();

#endif