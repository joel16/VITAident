#ifndef _VITAIDENT_KERNEL_H_
#define _VITAIDENT_KERNEL_H_

int Kernel_GetSystemSwVer(char *version);
int Kernel_GetSystemSwVer2(char *version);
int Kernel_GetSystemSwVerFactory(char *version);
int Kernel_GetProduct(char **product);
int Kernel_GetUnit(char **unit);
int Kernel_GetConsoleID(char **CID);
int Kernel_GetPSID(char **PSID);

#endif
