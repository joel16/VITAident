#include <psp2kern/kernel/cpu.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/sysmem.h>
#include <taihen.h>

int ksceKernelSysrootGetSystemSwVersion(void);

int Kenel_GetCurrentFirmware(void) {
    SceUInt32 state = 0;
    ENTER_SYSCALL(state);
    
    unsigned int current_fw = -1;
    int ret = ksceKernelSysrootGetSystemSwVersion();
    
    if (ret)
        current_fw = ret;
      
    EXIT_SYSCALL(state);
    return current_fw;
}

// Thanks TheOfficialFloW!
int Kenel_GetFactoryFirmware(void) {
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
