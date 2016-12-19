#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"

#define printf psvDebugScreenPrintf

void setColor(Color color); //Set font color
void getSizeString(char *string, uint64_t size);
const char *concat(char* s1, char* s2);

#endif