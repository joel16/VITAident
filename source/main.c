#include <psp2/kernel/modulemgr.h>
#include <taihen.h>
#include <vita2d.h>

#include "log.h"
#include "menus.h"
#include "plugin.h"
#include "utils.h"

SceBootArgs sysroot;
int _vshKernelSearchModuleByName(const char *module, int unk[2]);

static int Init_services(void) {
    int search_unk[2], ret = 0;
    SceUID kernel_mod = 0, user_mod = 0, module_check = 0;
    
    if (R_FAILED(module_check = _vshKernelSearchModuleByName("vitaident_kernel", search_unk))) {
        if (R_FAILED(kernel_mod = taiLoadStartKernelModule("ux0:app/VITAIDENT/plugins/vitaident_kernel.skprx", 0, NULL, 0))) {
            Log_Print("taiLoadStartKernelModule: 0x%lx\n", kernel_mod);
            return kernel_mod;
        }
    }

    if (R_FAILED(user_mod = sceKernelLoadStartModule("ux0:app/VITAIDENT/plugins/vitaident_user.suprx", 0, NULL, 0, NULL, NULL))) {
        Log_Print("sceKernelLoadStartModule: 0x%lx\n", user_mod);
        return user_mod;
    }

    // Get sysroot buffer
    sysroot.factory_fw_version = User_GetFactoryFirmware();

    if (R_SUCCEEDED(user_mod)) {
        if (R_FAILED(ret = sceKernelStopUnloadModule(user_mod, 0, NULL, 0, NULL, NULL))) {
            Log_Print("sceKernelStopUnloadModule: 0x%lx\n", ret);
            return ret;
        }
    }
    
    if (R_SUCCEEDED(kernel_mod)) {
        if (R_FAILED(ret = taiStopUnloadKernelModule(kernel_mod, 0, NULL, 0, NULL, NULL))) {
            // This will almost always fail because kernel function that expose syscalls cannot be unloaded.
            // Log_Print("taiStopUnloadKernelModule: 0x%lx\n", ret);
            // return ret;
        }
    }
    
    vita2d_init();
    Utils_InitAppUtil();
    return 0;
}

static void Term_Services(void) {
    Utils_TermAppUtil();
    vita2d_fini();
}

int main(int argc, char *argv[]) {
    Init_services();
    Menu_Main();
    Term_Services();
}
