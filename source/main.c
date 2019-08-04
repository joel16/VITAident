#include <psp2/kernel/modulemgr.h>
#include <taihen.h>
#include <vita2d.h>

#include "menus.h"
#include "utils.h"

#define APP_PATH "ux0:app/VITAIDENT/"

static SceUID vitaident_kernel_id = -1, vitaident_user_id = -1;

int unload_kernel_drivers(void) {
    if (vitaident_user_id >= 0)
        sceKernelStopUnloadModule(vitaident_user_id, 0, NULL, 0, NULL, NULL);
    
    if (vitaident_kernel_id >= 0)
        taiStopUnloadKernelModule(vitaident_kernel_id, 0, NULL, 0, NULL, NULL);

    return 0;
}

int load_kernel_drivers(void) {
    vitaident_kernel_id = taiLoadStartKernelModule(APP_PATH "vitaident_kernel.skprx", 0, NULL, 0);
    if (vitaident_kernel_id < 0)
        return vitaident_kernel_id;
        
    vitaident_user_id = sceKernelLoadStartModule(APP_PATH "vitaident_user.suprx", 0, NULL, 0, NULL, NULL);
    if (vitaident_user_id < 0)
        return vitaident_user_id;
        
    return 0;
}

static int Init_services(void) {
    int ret = 0;

    if (R_FAILED(ret = load_kernel_drivers()))
        return -1;
    
    vita2d_init();
    Utils_InitAppUtil();

    return 0;
}

static void Term_Services(void) {
    Utils_TermAppUtil();
    vita2d_fini();
    unload_kernel_drivers();
}

int main(int argc, char *argv[]) {
    Init_services();
    Menu_Main();
    Term_Services();
}
