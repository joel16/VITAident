#ifndef _VITAIDENT_POWER_H_
#define _VITAIDENT_POWER_H_

typedef enum {
    ClockFrequencyTypeCPU,
    ClockFrequencyTypeBUS,
    ClockFrequencyTypeGPU,
    ClockFrequencyTypeGPUXbar
} ClockFrequencyType;

int Power_GetBatteryStatus(char **status);
int Power_GetBatteryPercentage(int *percent);
int Power_GetBatterySOH(int *SOH);
int Power_GetBatteryCycleCount(int *count);
int Power_GetBatteryFullCapacity(int *capacity);
int Power_GetBatteryRemainCapacity(int *capacity);
int Power_GetBatteryTemp(int *temp);
int Power_GetBatteryVoltage(int *voltage);
int Power_GetCableStatus(char **status);
int Power_GetClockFrequency(ClockFrequencyType type);

#endif
