#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <stdio.h>

#include "utils.h"

int Misc_GetMacAddress(char address[20]) {
    int ret = 0;
    SceNetEtherAddr mac;
    
    if (R_FAILED(ret = sceNetGetMacAddress(&mac, 0)))
        return ret;

    snprintf(address, 20, "%02X:%02X:%02X:%02X:%02X:%02X", mac.data[0], mac.data[1], mac.data[2], mac.data[3], mac.data[4], mac.data[5]);
    return 0;
}

int Misc_GetIPAddress(char address[20]) {
    int ret = 0;
    SceNetCtlInfo info;
    
    if (R_FAILED(ret = sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &info)))
        return ret;
        
    snprintf(address, 20, info.ip_address);
    return 0;
}

int Misc_GetRSSIPercent(unsigned int *percent) {
    int ret = 0;
    SceNetCtlInfo info;
    
    if (R_FAILED(ret = sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_RSSI_PERCENTAGE, &info)))
        return ret;
    
    *percent = info.rssi_percentage;
    return 0;
}
