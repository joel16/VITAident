#include <stdio.h>

#include "power.h"
#include "utils.h"

SceInt getClockFrequency(clockFrequencyType type)
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

const char * getBatteryStatus(SceVoid)
{
	if (scePowerIsBatteryCharging())
		return "Charging";
	
	return "Not charging";
}

char * getBatteryPercentage(SceVoid)
{
	static char percentage[0x6];
	int battery = 0;
	
	if (R_SUCCEEDED(battery = scePowerGetBatteryLifePercent()))
		snprintf(percentage, 0x6, "%d%%", battery);
	
	return percentage;
}

char * getUsingWireless(SceVoid)
{
	static char usingWireless[0xA];
	int wireless = 0;
	
	if (R_SUCCEEDED(wireless = scePowerGetUsingWireless()))
		snprintf(usingWireless, 0xA, "%d", wireless);

	return usingWireless;
}

char * getBatterySOH(SceVoid)
{
	static char SOH[0x6];
	int batterySOH = 0;
	
	if (R_SUCCEEDED(batterySOH = scePowerGetBatterySOH()))
		snprintf(SOH, 0x6, "%d%%", batterySOH);
	
	return SOH;
}

char * getBatteryCycleCount(SceVoid)
{
	static char count[0x6];
	int cycleCount = 0;
	
	if (R_SUCCEEDED(cycleCount = scePowerGetBatteryCycleCount()))
		snprintf(count, 0x6, "%d", cycleCount);
	
	return count;
}

char * getBatteryCapacity(SceVoid)
{
	static char capacity[0xA];
	int fullCapacity = 0;
	
	if (R_SUCCEEDED(fullCapacity = scePowerGetBatteryFullCapacity()))
		snprintf(capacity, 0xA, "%i mAh", fullCapacity);
	
	return capacity;
}

char * getBatteryRemainCapacity(SceVoid)
{
	static char capacity[0xA];
	int remainCapacity = 0;
	
	if (R_SUCCEEDED(remainCapacity = scePowerGetBatteryRemainCapacity()))
		snprintf(capacity, 0xA, "%i mAh", remainCapacity);
	
	return capacity;
}

char * getBatteryTemp(SceInt type) 
{
	SceFloat temp = 0;
	
	static char c[0x7];
	static char f[0x8];
	
	if (R_SUCCEEDED(temp = scePowerGetBatteryTemp()))
	{
		snprintf(c, 0x7, "%0.1f", (temp / 100.0));
		snprintf(f, 0x8, "%0.1f", ((1.8 * temp) / 100.0) + 32.0);
	}
	
	return (type)? f : c;
}

char * getBatteryVoltage(SceVoid) 
{
	static char volts[0x6];
	SceFloat voltage = 0;
	
	if (R_SUCCEEDED(voltage = scePowerGetBatteryVolt()))
		snprintf(volts, 0x6, "%0.1f" , (voltage / 1000.0));
	
	return volts;
}

char * getUdcdCableState(SceVoid)
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

char * getUsbChargingState(SceVoid) // USB power supply is system settings
{
	static char usbChargeState[0x16];
	SceUdcdDeviceState state;
	
	if (R_SUCCEEDED(sceUdcdGetDeviceState(&state)))
	{
		SceInt usbChargeEnable = regMgrGetInt("/CONFIG/USB/", "usb_charge_enable");

		if (usbChargeEnable == 1)
			snprintf(usbChargeState, 0x15, "USB charging enabled");
		else 
			snprintf(usbChargeState, 0x16, "USB charging disabled");
	}
	
	return usbChargeState;
}