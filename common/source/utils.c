#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

static SceCtrlData pad, old_pad;

SceInt Utils_HandleControls(SceVoid)
{
	memset(&pad, 0, sizeof(SceCtrlData));
	sceCtrlPeekBufferPositive(0, &pad, 1);

	pressed = pad.buttons & ~old_pad.buttons;
	
	old_pad = pad;
	return 0;
}

SceVoid Utils_GetSizeString(char *string, SceOff size)
{
	double double_size = (double)size;

	SceInt i = 0;
	static char *units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};

	while (double_size >= 1024.0f)
	{
		double_size /= 1024.0f;
		i++;
	}

	sprintf(string, "%.*f %s", (i == 0) ? 0 : 2, double_size, units[i]);
}

char*Utils_StringConcat(char *s1, char *s2)
{
    char *ns = malloc(strlen(s1) + strlen(s2) + 1);
    ns[0] = '\0';
    strcat(ns, s1);
    strcat(ns, s2);
    return ns;
}