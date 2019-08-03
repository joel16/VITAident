#include <vita2d.h>

#include "menus.h"
#include "utils.h"

static int Init_services(void) {
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
