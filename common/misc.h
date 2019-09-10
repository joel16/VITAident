#ifndef _VITAIDENT_MISC_H_
#define _VITAIDENT_MISC_H_

int Misc_GetMacAddress(char address[20]);
int Misc_GetIPAddress(char address[20]);
int Misc_GetRSSIPercent(unsigned int *percent);

#endif
