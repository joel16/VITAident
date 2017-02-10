#ifndef _VITAIDENT_KERNEL_H_
#define _VITAIDENT_KERNEL_H_

#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/kernel/openpsid.h>

#include <stdio.h>
#include <stdbool.h>
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
int vshSblAimgrIsGenuineVITA();
int vshSblAimgrIsGenuineDolce();
int vshSblAimgrIsTest();
int vshSblAimgrIsTool();

/*int ksceSysrootIsExternalBootMode();
int ksceSysrootIsManufacturingMode();
int ksceSysrootIsSafeMode();
int ksceSysrootIsUpdateMode();*/

int vshSysconIsIduMode();
int vshSysconIsShowMode();
int vshSysconHasWWAN();

int vshRemovableMemoryGetCardInsertState();

char * getFwVersion(bool spoofed);
char getHenkakuVersion();
int getModel();
char * getCID();
char * getmCID();
SceKernelOpenPsId getPSID();
char * getUnit();
const char * getDeviceModel();
const char * getBoard();
const char * getSysrootKernelModes(int data);

#endif