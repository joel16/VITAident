#include <stdio.h>

#include "net.h"
#include "utils.h"

SceVoid initNet(SceVoid)
{
	if (sceSysmoduleIsLoaded(SCE_SYSMODULE_NET) != SCE_SYSMODULE_LOADED)
		sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
		
	static char memory[0x10 * 0x400];

	SceNetInitParam param;
	param.memory = memory;
	param.size = sizeof(memory);
	param.flags = 0;

	sceNetInit(&param);
	sceNetCtlInit();
}

SceVoid termNet(SceVoid)
{
	sceNetCtlTerm();
	sceNetTerm();
}

char * getMacAddress(SceVoid)
{	
	SceNetEtherAddr mac;
	static char macAddress[0x12];
	
	if (R_SUCCEEDED(sceNetGetMacAddress(&mac, 0)))
		snprintf(macAddress, 0x12, "%02X:%02X:%02X:%02X:%02X:%02X", mac.data[0], mac.data[1], mac.data[2], mac.data[3], mac.data[4], mac.data[5]);

	return macAddress;
}

char * getIP(SceVoid)
{
	SceNetCtlInfo info;
	static char address[0x11];
	
	if (R_SUCCEEDED(sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &info)))
		snprintf(address, 0x11, info.ip_address);
	
	return address;
}