#include <psp2/kernel/modulemgr.h>
#include <taihen.h>

#include "plugin.h"

int User_GetCurrentFirmware(void) {
    return Kenel_GetCurrentFirmware();
}

// Thanks TheOfficialFloW!
int User_GetFactoryFirmware(void) {
    return Kenel_GetFactoryFirmware();
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
    return SCE_KERNEL_STOP_SUCCESS;
}
