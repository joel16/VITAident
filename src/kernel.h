#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/kernel/openpsid.h>

#include <stdio.h>

typedef struct {
	SceUInt size;
	SceChar8 version_string[28];
	SceUInt version_value;
	SceUInt unk;
} SceSystemSwVersionParam;

int sceKernelGetSystemSwVersion(SceSystemSwVersionParam *param);

int _vshSblAimgrGetConsoleId(char CID[32]);

int vshSblAimgrIsCEX();
int vshSblAimgrIsDEX();
int vshSysconIsIduMode();
int vshSblAimgrIsGenuineVITA();
int vshSblAimgrIsTest();
int vshSblAimgrIsTool();

char * getFwVersion();
int getModel();
char * getCID();
SceKernelOpenPsId getPSID();
char * getUnit();