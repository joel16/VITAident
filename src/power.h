#ifndef _VITAIDENT_POWER_H_
#define _VITAIDENT_POWER_H_

#include <psp2/power.h>

#include <stdio.h>
#include <string.h>

typedef enum {
	ClockFrequencyType_Cpu = 0,
	ClockFrequencyType_Bus,
	ClockFrequencyType_Gpu,
	ClockFrequencyType_GpuXbar
} ClockFrequencyType;

int scePowerGetBatteryTemp();
int scePowerGetBatteryVolt();

int scePowerGetGpuXbarClockFrequency();

int getClockFrequency(ClockFrequencyType type);
const char * batteryStatus();
char * displayBatteryPercentage();
char * GetBatteryRemainCapacity();
char * getBatteryTemp(int type);
char * getBatteryVoltage();

#endif