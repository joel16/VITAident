#include <psp2/apputil.h>
#include <psp2/appmgr.h>
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/net/net.h>
#include <psp2/power.h>
#include <psp2/screenshot.h>
#include <psp2/system_param.h>
#include <stdio.h>
#include <string.h>

#define printf psvDebugScreenPrintf

typedef struct {
	SceUInt size;
	SceChar8 version_string[28];
	SceUInt version_value;
	SceUInt unk;
} SceSystemSwVersionParam;

int sceKernelGetSystemSwVersion(SceSystemSwVersionParam *param);

int _vshSblAimgrGetConsoleId(char CID[32]);

int scePowerGetBatteryTemp();
int scePowerGetBatteryVolt();

int scePowerGetGpuXbarClockFrequency();