#include <psp2/power.h>
#include <psp2/udcd.h>

#include "power.h"
#include "utils.h"

int Power_GetBatteryStatus(char **status) {
    int ret = 0;

    if (R_FAILED(ret = scePowerIsBatteryCharging()))
        return ret;
    
    *status = ret? "Charging" : "Not charging";
    return 0;
}

int Power_GetBatteryPercentage(int *percent) {
    int ret = 0;

    if (R_FAILED(ret = *percent = scePowerGetBatteryLifePercent()))
        return ret;
    
    return 0;
}

int Power_GetBatterySOH(int *SOH) {
    int ret = 0;

    if (R_FAILED(ret = *SOH = scePowerGetBatterySOH()))
        return ret;
    
    return 0;
}

int Power_GetBatteryCycleCount(int *count) {
    int ret = 0;

    if (R_FAILED(ret = *count = scePowerGetBatteryCycleCount()))
        return ret;
    
    return 0;
}

int Power_GetBatteryFullCapacity(int *capacity) {
    int ret = 0;

    if (R_FAILED(ret = *capacity = scePowerGetBatteryFullCapacity()))
        return ret;

    return 0;
}

int Power_GetBatteryRemainCapacity(int *capacity) {
    int ret = 0;

    if (R_FAILED(ret = *capacity = scePowerGetBatteryRemainCapacity()))
        return ret;

    return 0;
}

int Power_GetBatteryTemp(int *temp) {
    int ret = 0;

    if (R_FAILED(ret = *temp = scePowerGetBatteryTemp()))
        return ret;

    return 0;
}

int Power_GetBatteryVoltage(int *voltage) {
    int ret = 0;

    if (R_FAILED(ret = *voltage = scePowerGetBatteryVolt()))
        return ret;

    return 0;
}

int Power_GetCableStatus(char **status) {
    int ret = 0;
    SceUdcdDeviceState state;

    if (R_FAILED(ret = sceUdcdGetDeviceState(&state)))
        return ret;

    if (state.cable & SCE_UDCD_STATUS_CABLE_CONNECTED)
        *status = "connected";
    else if (state.cable & SCE_UDCD_STATUS_CABLE_DISCONNECTED)
        *status = "disconnected";

    return 0;
}

int Power_GetClockFrequency(ClockFrequencyType type) {
    int ret = 0;

    switch (type) {
        case ClockFrequencyTypeCPU:
            ret = scePowerGetArmClockFrequency();
            break;
        
        case ClockFrequencyTypeBUS:
            ret = scePowerGetBusClockFrequency();
            break;

        case ClockFrequencyTypeGPU:
            ret = scePowerGetGpuClockFrequency();
            break;

        case ClockFrequencyTypeGPUXbar:
            ret = scePowerGetGpuXbarClockFrequency();
            break;

        default:
            break;
    }

    return ret;
}
