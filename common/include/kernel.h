#ifndef _VITAIDENT_KERNEL_H_
#define _VITAIDENT_KERNEL_H_

#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/openpsid.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>

#include <stdio.h>
#include <string.h>

#define isPCHX000 ((vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()))
#define isVTE1000 ((vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (sceKernelIsPSVitaTV()))
#define isPDEL ((!vshSblAimgrIsCEX()) && (!vshSblAimgrIsTest()) && (!vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()) && (vshSblAimgrIsTool()))
#define isPTEL ((!vshSblAimgrIsCEX()) && (!vshSblAimgrIsTool()) && (!vshSblAimgrIsTest()) && (vshSblAimgrIsDEX()) && (vshSblAimgrIsGenuineVITA()))

typedef struct PsCode 
{
	char magic[2];
	char target_id[2];
	char model_revision[2];
	uint16_t chassis;
} PsCode;

SceInt _vshSblAimgrGetPscode(PsCode *code);

char *Kernel_GetFirmwareVersion(SceBool spoofed);
SceInt Kernel_GetModel(SceVoid);
char *Kernel_GetCID(SceVoid);
char *Kernel_GetPSID(SceVoid);
char *Kernel_GetDeviceModel(SceVoid);
char *Kernel_GetDeviceBoard(SceVoid);
char *Kernel_GetDeviceUnit(SceVoid);

#endif