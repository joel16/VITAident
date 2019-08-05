#include <psp2/kernel/openpsid.h>
#include <psp2/vshbridge.h>
#include <stdio.h>
#include <string.h>

#include "plugin.h"
#include "utils.h"

typedef struct PsCode {
	SceUInt16 company_code;
	SceUInt16 product_code;
	SceUInt16 product_sub_code;
	SceUInt16 factory_code;
} PsCode;

int _vshSblAimgrGetPscode(PsCode *code);

// Thanks TheOfficialFloW!
static void firmware_string(char string[8], unsigned int version) {
    char a = (version >> 24) & 0xf;
    char b = (version >> 20) & 0xf;
    char c = (version >> 16) & 0xf;
    char d = (version >> 12) & 0xf;
    
    memset(string, 0, 8);
    string[0] = '0' + a;
    string[1] = '.';
    string[2] = '0' + b;
    string[3] = '0' + c;
    string[4] = '\0';
    
    if (d) {
        string[4] = '0' + d;
        string[5] = '\0';
    }
}

// Actual firmware regardless of spoofing.
int Kernel_GetSystemSwVer(char *version) {
    int ret = 0;
    SceKernelFwInfo data;

    data.size = sizeof(SceKernelFwInfo);
    if (R_FAILED(ret = _vshSblGetSystemSwVersion(&data)))
        return ret;
    
    firmware_string(version, data.version);
    return 0;
}

// Spoofed firmware version
int Kernel_GetSystemSwVer2(char *version) {
    int ret = 0;
    SceKernelFwInfo data;

    data.size = sizeof(SceKernelFwInfo);
    if (R_FAILED(ret = sceKernelGetSystemSwVersion(&data)))
        return ret;
    
    firmware_string(version, data.version);
    return 0;
}

// Factory firmware from sysroot
int Kernel_GetSystemSwVerFactory(char *version) {
    firmware_string(version, sysroot.factory_fw_version);
    return 0;
}

// Thanks CeleseBlue and contributors: https://github.com/CelesteBlue-dev/PS-ConsoleId-wiki/blob/master/PS-ConsoleId-wiki.txt
int Kernel_GetProduct(char **product) {
    int ret = 0;

    PsCode pscode;
    if (R_FAILED(ret = _vshSblAimgrGetPscode(&pscode)))
        return ret;

    switch (pscode.product_code) {
        case 0x100:
            *product = "TEST (Prototype/Test unit)";
            break;
        
        case 0x101:
            *product = "TOOL - DevKit/Tool unit - PDEL/DEM";
            break;
        
        case 0x102:
            *product = "DEX - TestKit/DEX unit - PTEL";
            break;
        
        case 0x103:
            *product = "CEX - J1 - Japan";
            break;
        
        case 0x104:
            *product = "CEX - UC2 - North America";
            break;
        
        case 0x105:
            *product = "CEX - CEL - Europe/East/Africa";
            break;
        
        case 0x106:
            *product = "CEX - KR2 - South Korea";
            break;

        case 0x107:
            *product = "CEX - CEK - Great Britain/UK";
            break;

        case 0x108:
            *product = "CEX - MX2 - Mexico/Latin America";
            break;

        case 0x109:
            *product = "CEX - AU3 - Australia/New Zealand";
            break;

        case 0x10A:
            *product = "CEX - E12 - HK/Macao/Singapore/Malaysia";
            break;

        case 0x10B:
            *product = "CEX - TW1 - Taiwan";
            break;

        case 0x10C:
            *product = "CEX - RU3 - Russia";
            break;

        case 0x10D:
            *product = "CEX - CN9";
            break;
        
        default:
            *product = "Unknown";
            break;
    }

    return 0;
}

int Kernel_GetUnit(char **unit) {
    int ret = 0;

    PsCode pscode;
    if (R_FAILED(ret = _vshSblAimgrGetPscode(&pscode)))
        return ret;

    switch (pscode.product_sub_code) {
        case 0x05:
            *unit = "IRT-001 (DEM-3000H, CP board GCP-001)";
            break;

        case 0x0B:
            *unit = "Prototype DevKit (DEM-3000L)";
            break;

        case 0x0F:
            *unit = "CEM-3000NP1";
            break;

        case 0x10:
            *unit = "FAT - IRS-002/IRT-002";
            break;

        case 0x11:
            *unit = "FAT - IRS-1001";
            break;

        case 0x14:
            *unit = "SLIM - USS-1001";
            break;

        case 0x18:
            *unit = "SLIM (2016) - USS-1002";
            break;

        case 0x201:
            *unit = "PS TV - DOL-1001";
            break;

        default:
            *unit = "Unknown";
            break;
    }
    
    return 0;
}

int Kernel_GetConsoleID(char **CID) {
    int ret = 0;

    char ID[16];
    if (R_FAILED(ret = _vshSblAimgrGetConsoleId(ID)))
        return ret;

    static char temp[33];
    for (int i = 0; i < 16; i++)
        snprintf(&temp[2 * i], 33, "%02X", ID[i]);

    *CID = temp;
    return 0;
}

int Kernel_GetPSID(char **PSID) {
    int ret = 0;
    SceKernelOpenPsId ID;

    if (R_FAILED(ret = sceKernelGetOpenPsId(&ID)))
        return ret;
        
    static char temp[33];
    for(int i = 0; i < 16; i++)
        snprintf(&temp[2 * i], 33, "%02X", ID.id[i]);
    
    *PSID = temp;
    return 0;
}
