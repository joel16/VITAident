#include "power.h"
#include "utils.h"

SceInt getClockFrequency(clockFrequencyType type)
{
	if (type == clockFrequencyType_cpu)
		return scePowerGetArmClockFrequency();
	else if (type == clockFrequencyType_bus)
		return scePowerGetBusClockFrequency();
	else if (type == clockFrequencyType_gpu)
		return scePowerGetGpuClockFrequency();
	else if (type == clockFrequencyType_gpuXbar)
		return scePowerGetGpuXbarClockFrequency();
	
	else 
		return 0;
}

const char * getBatteryStatus(SceVoid)
{
	SceInt batteryStateBool = scePowerIsBatteryCharging();
	
	if (!batteryStateBool) 
		return "Not charging";
	
	return "Charging";
}

char * getBatteryPercentage(SceVoid)
{
	static char percentage[6];
	
	int battery = scePowerGetBatteryLifePercent();
	
	snprintf(percentage, 6, "%d%%", battery);
	
	return percentage;
}

/*char * getBatteryElec() //Crashes the VITA
{
	static char batteryElec[10];
	
	int elec = scePowerGetBatteryElec();
	
	sprintf(batteryElec, "%d", elec);
	
	return batteryElec;
}*/

char * getUsingWireless(SceVoid)
{
	static char usingWireless[10];
	
	int wireless = scePowerGetUsingWireless();
	
	snprintf(usingWireless, 10, "%d", wireless);
	
	return usingWireless;
}

char * getBatterySOH(SceVoid)
{
	static char SOH[6];
	
	int batterySOH = scePowerGetBatterySOH();
	
	snprintf(SOH, 6, "%d%%", batterySOH);
	
	return SOH;
}

char * getBatteryCycleCount(SceVoid)
{
	static char count[6];
	
	int cycleCount = scePowerGetBatteryCycleCount();
	
	snprintf(count, 6, "%d", cycleCount);
	
	return count;
}

char * getBatteryCapacity(SceVoid)
{
	static char capacity[10];
	
	int fullCapacity = scePowerGetBatteryFullCapacity();
	
	snprintf(capacity, 10, "%i mAh", fullCapacity);
	
	return capacity;
}

char * getBatteryRemainCapacity(SceVoid)
{
	static char capacity[10];
	
	int remainCapacity = scePowerGetBatteryRemainCapacity();
	
	snprintf(capacity, 10, "%i mAh", remainCapacity);
	
	return capacity;
}

char * getBatteryTemp(SceInt type) 
{
	static char c[7];
	snprintf(c, 7, "%0.1f", ((SceFloat)scePowerGetBatteryTemp()) / 100.0);
	
	static char f[8];
	snprintf(f, 8, "%0.1f", ((1.8 * (SceFloat)scePowerGetBatteryTemp()) / 100.0) + 32.0);
	
	if (type == 0)
		return c;
	
	return f;
}

char * getBatteryVoltage(SceVoid) 
{
	static char volts[6];
	
	snprintf(volts, 6, "%0.1f" , (((SceFloat)scePowerGetBatteryVolt()) / 1000.0));
	
	return volts;
}

char * getUdcdCableState(SceVoid)
{
	static char udcdState[19];
	SceUdcdDeviceState state;
	sceUdcdGetDeviceState(&state);

	if (state.cable & SCE_UDCD_STATUS_CABLE_CONNECTED)
		snprintf(udcdState, 16, "Cable connected");
	else if (state.cable & SCE_UDCD_STATUS_CABLE_DISCONNECTED)
		snprintf(udcdState, 19, "Cable disconnected");
	
	return udcdState;
}

char * getUsbChargingState(SceVoid) // USB power supply is system settings
{
	static char usbChargeState[21];
	SceUdcdDeviceState state;
	sceUdcdGetDeviceState(&state);
	
	SceInt usbChargeEnable = regMgrGetInt("/CONFIG/USB/", "usb_charge_enable");

	if (usbChargeEnable == 1)
		snprintf(usbChargeState, 21, "USB charging enabled");
	else 
		snprintf(usbChargeState, 21, "USB charging disabled");
	
	return usbChargeState;
}