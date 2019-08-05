#include <psp2/kernel/modulemgr.h>
#include <taihen.h>

#include "sysroot.h"

// Thanks TheOfficialFloW!
int sysroot_get_factoryfirmware(void) {
    return k_sysroot_get_factoryfirmware();
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
    return SCE_KERNEL_STOP_SUCCESS;
}
