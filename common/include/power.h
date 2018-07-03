#ifndef _VITAIDENT_POWER_H_
#define _VITAIDENT_POWER_H_

#include <vitasdk.h>

typedef enum 
{
	clockFrequencyType_cpu,
	clockFrequencyType_bus,
	clockFrequencyType_gpu,
	clockFrequencyType_gpuXbar
} clockFrequencyType;

//SceInt scePowerPower_GetBatteryElec(SceVoid); Crashes the VITA

SceInt Power_GetClockFrequency(clockFrequencyType type);
const char *Power_GetBatteryStatus(SceVoid);
const char *Power_GetBatteryPercentage(SceVoid);
const char *Power_GetUsingWireless(SceVoid);
const char *Power_GetBatterySOH(SceVoid);
const char *Power_GetBatteryCycleCount(SceVoid);
const char *Power_GetBatteryCapacity(SceVoid);
const char *Power_GetBatteryRemainCapacity(SceVoid);
const char *Power_GetBatteryTemp(SceInt type);
const char *Power_GetBatteryVoltage(SceVoid);
const char *Power_GetUdcdCableState(SceVoid);
const char *Power_GetUsbChargingState(SceVoid);

#endif