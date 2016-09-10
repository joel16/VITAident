#ifndef _VITAIDENT_NET_H_
#define _VITAIDENT_NET_H_

#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/sysmodule.h>

#include <stdio.h>
#include <string.h>

void initNet();
void termNet();
char * getMacAddress();
char * getIP();

#endif