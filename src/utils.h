#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <stdio.h>
#include "graphics.h"

#define printf psvDebugScreenPrintf

void printStarWithColor(Color color);
void getSizeString(char *string, uint64_t size);

#endif