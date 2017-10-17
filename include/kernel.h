#ifndef _VITAIDENT_KERNEL_H_
#define _VITAIDENT_KERNEL_H_

#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/openpsid.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>

#include <stdio.h>
#include <string.h>

#define isPCHX000 ((vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()))
#define isVTE1000 ((vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineDolce()))
#define isPDEL ((!vshSblAimgrIsCEX()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()) && (vshSblAimgrIsTool()))
#define isPTEL ((!vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()))

SceInt32 ksceSysconGetBaryonVersion(SceInt32 * baryonVersion);
SceInt _vshSblGetSystemSwVersion(SceKernelFwInfo * data);

SceInt _vshSblAimgrGetConsoleId(char CID[32]);
SceInt _vshAppMgrCloudDataGetMcId(char mCID[32]);

SceInt vshSblAimgrIsCEX(SceVoid);
SceInt vshSblAimgrIsDEX(SceVoid);
SceInt vshSblAimgrIsGenuineVITA(SceVoid);
SceInt vshSblAimgrIsGenuineDolce(SceVoid);
SceInt vshSblAimgrIsTest(SceVoid);
SceInt vshSblAimgrIsTool(SceVoid);

SceInt vshSysconIsIduMode(SceVoid);
SceInt vshSysconIsShowMode(SceVoid);
SceInt vshSysconHasWWAN(SceVoid);

SceInt vshRemovableMemoryGetCardInsertState(SceVoid);

char * getFwVersion(SceBool spoofed);
char getHenkakuVersion(SceVoid);
SceInt getModel(SceVoid);
char * getCID(SceVoid);
char * getmCID(SceVoid);
SceKernelOpenPsId getPSID(SceVoid);
char * getUnit(SceVoid);
const char * getDeviceModel(SceVoid);
const char * getBoard(SceVoid);
const char * getSysrootKernelModes(SceInt data);

#endif