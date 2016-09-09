#include <psp2/power.h>

#include <stdio.h>
#include <string.h>

int scePowerGetBatteryTemp();
int scePowerGetBatteryVolt();

int scePowerGetGpuXbarClockFrequency();

int getClockFrequency(int type);
const char * batteryStatus();
char * displayBatteryPercentage();
char * GetBatteryRemainCapacity();
char * getBatteryTemp(int type);
char * getBatteryVoltage();