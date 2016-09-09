#include "power.h"

int getClockFrequency(int type)
{
	if (type == 0)
		return scePowerGetArmClockFrequency();
	else if (type == 1)
		return scePowerGetBusClockFrequency();
	else if (type == 2)
		return scePowerGetGpuClockFrequency();
	else if (type == 3)
		return scePowerGetGpuXbarClockFrequency();
	
	else 
		return 0;
}

const char * batteryStatus()
{
	int batteryStateBool = scePowerIsBatteryCharging();
	
	if (!batteryStateBool) 
		return "Not charging";
	else 
		return "Charging";
}

char * displayBatteryPercentage()
{
	static char percentage[5];
	
	int battery = scePowerGetBatteryLifePercent();
	
	sprintf(percentage, "%d%%", battery);
	
	return percentage;
}

char * GetBatteryRemainCapacity()
{
	static char capacity[10];
	
	int battery = scePowerGetBatteryRemainCapacity();
	
	sprintf(capacity, "%i mAh", battery);
	
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