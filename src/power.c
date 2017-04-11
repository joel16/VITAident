#include "power.h"
#include "utils.h"

int getClockFrequency(ClockFrequencyType type)
{
	if (type == ClockFrequencyType_Cpu)
		return scePowerGetArmClockFrequency();
	else if (type == ClockFrequencyType_Bus)
		return scePowerGetBusClockFrequency();
	else if (type == ClockFrequencyType_Gpu)
		return scePowerGetGpuClockFrequency();
	else if (type == ClockFrequencyType_GpuXbar)
		return scePowerGetGpuXbarClockFrequency();
	
	else 
		return 0;
}

const char * getBatteryStatus()
{
	int batteryStateBool = scePowerIsBatteryCharging();
	
	if (!batteryStateBool) 
		return "Not charging";
	else 
		return "Charging";
}

char * getBatteryPercentage()
{
	static char percentage[5];
	
	int battery = scePowerGetBatteryLifePercent();
	
	sprintf(percentage, "%d%%", battery);
	
	return percentage;
}

/*char * getBatteryElec() //Crashes the VITA
{
	static char batteryElec[10];
	
	int elec = scePowerGetBatteryElec();
	
	sprintf(batteryElec, "%d", elec);
	
	return batteryElec;
}*/

char * getUsingWireless()
{
	static char usingWireless[10];
	
	int wireless = scePowerGetUsingWireless();
	
	sprintf(usingWireless, "%d", wireless);
	
	return usingWireless;
}

char * getBatterySOH()
{
	static char SOH[10];
	
	int batterySOH = scePowerGetBatterySOH();
	
	sprintf(SOH, "%d%%", batterySOH);
	
	return SOH;
}

char * getBatteryCycleCount()
{
	static char count[10];
	
	int cycleCount = scePowerGetBatteryCycleCount();
	
	sprintf(count, "%d", cycleCount);
	
	return count;
}

char * getBatteryCapacity()
{
	static char capacity[10];
	
	int fullCapacity = scePowerGetBatteryFullCapacity();
	
	sprintf(capacity, "%i mAh", fullCapacity);
	
	return capacity;
}

char * getBatteryRemainCapacity()
{
	static char capacity[10];
	
	int remainCapacity = scePowerGetBatteryRemainCapacity();
	
	sprintf(capacity, "%i mAh", remainCapacity);
	
	return capacity;
}

char * getBatteryTemp(int type) 
{
	static char c[10];
	sprintf(c, "%0.1f", ((float)scePowerGetBatteryTemp()) / 100);
	
	static char f[10];
	sprintf(f, "%0.1f", ((1.8 * (float)scePowerGetBatteryTemp()) / 100) + 32);
	
	if (type == 0)
		return c;
	else
		return f;
}

char * getBatteryVoltage() 
{
	static char volts[10];
	
	sprintf(volts, "%0.1f" , (((float)scePowerGetBatteryVolt()) / 1000));
	
	return volts;
}

char * getUdcdCableState()
{
	static char udcdState[20];
	SceUdcdDeviceState state;
	sceUdcdGetDeviceState(&state);

	if (state.cable & SCE_UDCD_STATUS_CABLE_CONNECTED)
		sprintf(udcdState, "Cable connected");
	else if (state.cable & SCE_UDCD_STATUS_CABLE_DISCONNECTED)
		sprintf(udcdState, "Cable disconnected");
	
	return udcdState;
}

char * getUsbChargingState() //USB power supply is system settings
{
	static char usbChargeState[20];
	SceUdcdDeviceState state;
	sceUdcdGetDeviceState(&state);
	
	int usbChargeEnable = regMgrGetInt("/CONFIG/USB/", "usb_charge_enable");

	if (usbChargeEnable == 1)
		sprintf(usbChargeState, "USB charging enabled");
	else 
		sprintf(usbChargeState, "USB charging disabled");
	
	return usbChargeState;
}