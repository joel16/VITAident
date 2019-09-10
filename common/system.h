#ifndef _VITAIDENT_SYSTEM_H_
#define _VITAIDENT_SYSTEM_H_

int System_GetSystemSwVer(char *version);
int System_GetSystemSwVer2(char *version);
int System_GetSystemSwVerFactory(char *version);
int System_GetProduct(char **product);
int System_GetUnit(char **unit);
int System_GetConsoleID(char **CID);
int System_GetPSID(char **PSID);

#endif
