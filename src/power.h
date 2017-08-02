#ifndef _VITAIDENT_POWER_H_
#define _VITAIDENT_POWER_H_

#include <psp2/power.h>
#include <psp2/udcd.h>

#include <stdio.h>
#include <string.h>

typedef enum 
{
	clockFrequencyType_cpu,
	clockFrequencyType_bus,
	clockFrequencyType_gpu,
	clockFrequencyType_gpuXbar
} clockFrequencyType;

//SceInt scePowerGetBatteryElec(SceVoid); Crashes the VITA
SceInt scePowerGetUsingWireless(SceVoid);

SceInt getClockFrequency(clockFrequencyType type);
const char * getBatteryStatus(SceVoid);
char * getBatteryPercentage(SceVoid);
char * getUsingWireless(SceVoid);
char * getBatterySOH(SceVoid);
char * getBatteryCycleCount(SceVoid);
char * getBatteryCapacity(SceVoid);
char * getBatteryRemainCapacity(SceVoid);
char * getBatteryTemp(SceInt type);
char * getBatteryVoltage(SceVoid);
char * getUdcdCableState(SceVoid);
char * getUsbChargingState(SceVoid);

#endif