#ifndef _VITAIDENT_SYSROOT_H_
#define _VITAIDENT_SYSROOT_H_

#include <psp2/types.h>

typedef struct SceBootArgs {
	SceUInt16 version;
	SceUInt16 size;
	SceUInt32 current_fw_version;
	SceUInt32 factory_fw_version;
	SceUInt8 unk_C[0x14];
	SceUInt8 qa_flags[0x10];
	SceUInt8 boot_flags[0x10];
	SceUInt32 devkit_cp_timestamp_1;
	SceUInt16 devkit_cp_version;
	SceUInt16 devkit_cp_build_id;
	SceUInt32 devkit_cp_timestamp_2;
	SceUInt32 aslr_seed;
	SceUInt32 devkit_boot_parameters;
	SceUInt32 unk_54;
	SceUInt32 devkit_unk_flags;
	SceUInt32 devkit_flags_3;
	SceUInt32 dram_base;
	SceUInt32 dram_size;
	SceUInt32 unk_68;
	SceUInt32 boot_type_indicator_1;
	SceUInt8 openpsid[0x10];
	SceUInt32 secure_kernel_enp_addr;
	SceUInt32 secure_kernel_enp_size;
	SceUInt8 unk_88[0x8];
	SceUInt32 kprx_auth_sm_self_addr;
	SceUInt32 kprx_auth_sm_self_size;
	SceUInt32 prog_rvk_srvk_addr;
	SceUInt32 prog_rvk_srvk_size;
	SceUInt8 pscode[0x8];
	SceUInt8 unk_A8[0x8];
	SceUInt8 session_id[0x10];
	SceUInt32 unk_C0;
	SceUInt32 wakeup_factor;
	SceUInt32 unk_C8;
	SceUInt32 unk_CC;
	SceUInt32 resume_context_addr;
	SceUInt32 hardware_info;
	SceUInt32 boot_type_indicator_2;
	SceUInt8 unk_DC[0xC];
	SceUInt8 hardware_flags[0x10];
	SceUInt32 bootldr_revision;
	SceUInt32 magic;
	SceUInt8 session_key[0x20];
	SceUInt8 unused[0xE0];
} __attribute__((packed)) SceBootArgs;

extern SceBootArgs sysroot;

// Kernel functions
int Kenel_GetCurrentFirmware(void);
int Kenel_GetFactoryFirmware(void);

// User functions
int User_GetCurrentFirmware(void);
int User_GetFactoryFirmware(void);

#endif
