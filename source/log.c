#include <psp2/io/fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "log.h"
#include "utils.h"

#define LOG_FILENAME   "ux0:vpk/log.txt"
#define LOG_BUFFER_LEN 4096

int Log_Print(const char* format, ...) {
	va_list list;
	char string[LOG_BUFFER_LEN] = {0};

	va_start(list, format);
	vsprintf(string, format, list);
	va_end(list);

	SceUID fd = 0;
	if (R_FAILED(fd = sceIoOpen(LOG_FILENAME, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_APPEND, 0777))) 
		return fd;

	sceIoWrite(fd, string, strlen(string));
	sceIoClose(fd);

	return 0;
}
