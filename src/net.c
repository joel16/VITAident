#include "net.h"

SceVoid initNet(SceVoid)
{
	if (sceSysmoduleIsLoaded(SCE_SYSMODULE_NET) != SCE_SYSMODULE_LOADED)
		sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	
	static char memory[16 * 1024];

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
	sceNetGetMacAddress(&mac, 0);

	static char macAddress[32];
	
	snprintf(macAddress, 32, "%02X:%02X:%02X:%02X:%02X:%02X", mac.data[0], mac.data[1], mac.data[2], mac.data[3], mac.data[4], mac.data[5]);

	return macAddress;
}

char * getIP(SceVoid)
{
	static char address[16];

	SceNetCtlInfo info;
	
	if (sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &info) < 0) 
		strcpy(address, "-");
	else 
		strcpy(address, info.ip_address);
	
	return address;
}