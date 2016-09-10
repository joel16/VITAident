#ifndef _VITAIDENT_SCREENSHOT_H_
#define _VITAIDENT_SCREENSHOT_H_

#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/display.h>
#include <psp2/screenshot.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void captureScreenshot(char* path);

#endif