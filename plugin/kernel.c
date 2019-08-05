#include <psp2kern/kernel/cpu.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/sysmem.h>
#include <taihen.h>

// Thanks TheOfficialFloW!
int k_sysroot_get_factoryfirmware(void) {
    SceUInt32 state = 0;
    ENTER_SYSCALL(state);
    
    unsigned int factory_fw = -1;
    void *sysroot = ksceKernelGetSysrootBuffer();
    
    if (sysroot)
        factory_fw = *(unsigned int *)(sysroot + 8);
        
    EXIT_SYSCALL(state);
    return factory_fw;
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize args, void *argp) {
    return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
    return SCE_KERNEL_STOP_SUCCESS;
}
