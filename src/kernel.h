#ifndef _VITAIDENT_KERNEL_H_
#define _VITAIDENT_KERNEL_H_

#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/kernel/openpsid.h>

#include <stdio.h>
#include <string.h>

typedef struct {
	SceUInt size;
	SceChar8 version_string[28];
	SceUInt version_value;
	SceUInt unk;
} SceSystemSwVersionParam;

int sceKernelGetSystemSwVersion(SceSystemSwVersionParam *param);

int _vshSblAimgrGetConsoleId(char CID[32]);
int _vshAppMgrCloudDataGetMcId(char mCID[32]);

int vshSblAimgrIsCEX();
int vshSblAimgrIsDEX();
int vshSysconIsIduMode();
int vshSysconIsShowMode();
int vshSblAimgrIsGenuineVITA();
int vshSblAimgrIsGenuineDolce();
int vshSblAimgrIsTest();
int vshSblAimgrIsTool();

int vshRemovableMemoryGetCardInsertState();

char * getFwVersion();
char getHenkakuVersion();
int getModel();
char * getCID();
char * getmCID();
SceKernelOpenPsId getPSID();
char * getUnit();
const char * getDeviceModel();
const char * getBoard();

#endif