#include <stdio.h>

#include "power.h"
#include "regmgr.h"
#include "utils.h"

SceInt Power_GetClockFrequency(clockFrequencyType type)
{
	SceInt ret = 0;
	
	switch(type)
	{
		case clockFrequencyType_cpu:
			ret = scePowerGetArmClockFrequency();
			break;
		
		case clockFrequencyType_bus:
			ret = scePowerGetBusClockFrequency();
			break;
		
		case clockFrequencyType_gpu:
			ret = scePowerGetGpuClockFrequency();
			break;
		
		case clockFrequencyType_gpuXbar:
			ret = scePowerGetGpuXbarClockFrequency();
			break;
	}
	
	return ret;
}

const char *Power_GetBatteryStatus(SceVoid)
{
	if (scePowerIsBatteryCharging())
		return "Charging";
	
	return "Not charging";
}

const char *Power_GetBatteryPercentage(SceVoid)
{
	static char percentage[0x6];
	int battery = 0;
	
	if (R_SUCCEEDED(battery = scePowerGetBatteryLifePercent()))
		snprintf(percentage, 0x6, "%d%%", battery);
	
	return percentage;
}

const char *Power_GetUsingWireless(SceVoid)
{
	static char usingWireless[0xA];
	int wireless = 0;
	
	if (R_SUCCEEDED(wireless = scePowerGetUsingWireless()))
		snprintf(usingWireless, 0xA, "%d", wireless);

	return usingWireless;
}

const char *Power_GetBatterySOH(SceVoid)
{
	static char SOH[0x6];
	int batterySOH = 0;
	
	if (R_SUCCEEDED(batterySOH = scePowerGetBatterySOH()))
		snprintf(SOH, 0x6, "%d%%", batterySOH);
	
	return SOH;
}

const char *Power_GetBatteryCycleCount(SceVoid)
{
	static char count[0x6];
	int cycleCount = 0;
	
	if (R_SUCCEEDED(cycleCount = scePowerGetBatteryCycleCount()))
		snprintf(count, 0x6, "%d", cycleCount);
	
	return count;
}

const char *Power_GetBatteryCapacity(SceVoid)
{
	static char capacity[0xA];
	int fullCapacity = 0;
	
	if (R_SUCCEEDED(fullCapacity = scePowerGetBatteryFullCapacity()))
		snprintf(capacity, 0xA, "%i mAh", fullCapacity);
	
	return capacity;
}

const char *Power_GetBatteryRemainCapacity(SceVoid)
{
	static char capacity[0xA];
	int remainCapacity = 0;
	
	if (R_SUCCEEDED(remainCapacity = scePowerGetBatteryRemainCapacity()))
		snprintf(capacity, 0xA, "%i mAh", remainCapacity);
	
	return capacity;
}

const char *Power_GetBatteryTemp(SceInt type) 
{
	SceFloat temp = 0;
	
	static char c[0x7];
	static char f[0x8];
	
	if (R_SUCCEEDED(temp = scePowerGetBatteryTemp()))
	{
		snprintf(c, 0x7, "%0.1f", (temp / 100.0));
		snprintf(f, 0x8, "%0.1f", ((1.8 *temp) / 100.0) + 32.0);
	}
	
	return (type)? f : c;
}

const char *Power_GetBatteryVoltage(SceVoid) 
{
	static char volts[0x6];
	SceFloat voltage = 0;
	
	if (R_SUCCEEDED(voltage = scePowerGetBatteryVolt()))
		snprintf(volts, 0x6, "%0.1f" , (voltage / 1000.0));
	
	return volts;
}

const char *Power_GetUdcdCableState(SceVoid)
{
	static char udcdState[0x13];
	SceUdcdDeviceState state;
	
	if (R_SUCCEEDED(sceUdcdGetDeviceState(&state)))
	{
		if (state.cable & SCE_UDCD_STATUS_CABLE_CONNECTED)
			snprintf(udcdState, 0x10, "Cable connected");
		else if (state.cable & SCE_UDCD_STATUS_CABLE_DISCONNECTED)
			snprintf(udcdState, 0x13, "Cable disconnected");
	}
	
	return udcdState;
}

const char *Power_GetUsbChargingState(SceVoid) // USB power supply is system settings
{
	static char usbChargeState[0x16];
	SceUdcdDeviceState state;
	
	if (R_SUCCEEDED(sceUdcdGetDeviceState(&state)))
	{
		SceInt usbChargeEnable = RegMgr_GetInt("/CONFIG/USB/", "usb_charge_enable");

		if (usbChargeEnable == 1)
			snprintf(usbChargeState, 0x15, "USB charging enabled");
		else 
			snprintf(usbChargeState, 0x16, "USB charging disabled");
	}
	
	return usbChargeState;
}