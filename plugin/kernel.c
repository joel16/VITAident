/* kernel.c -- updater patches
 *
 * Copyright (C) 2019 TheFloW
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <psp2kern/kernel/cpu.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/sysmem.h>
#include <taihen.h>

int k_modoru_get_factory_firmware(void) {
  uint32_t state;
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
