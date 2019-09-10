#include <psp2/io/devctl.h>
#include <stdio.h>

#include "utils.h"

// Thanks TheOfficialFloW!
static void Storage_GetSizeString(char *string, SceOff size) {
	double double_size = (double)size;

	SceInt i = 0;
	static char *units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};

	while (double_size >= 1024.0f) {
		double_size /= 1024.0f;
		i++;
	}

	sprintf(string, "%.*f %s", (i == 0) ? 0 : 2, double_size, units[i]);
}

static int Storage_GetDevInfo(const char *device, SceIoDevInfo *info) {
    int ret = 0;
    SceIoDevInfo device_info;

    if (R_FAILED(ret = sceIoDevctl(device, 0x3001, NULL, 0, &device_info, sizeof(SceIoDevInfo))))
        return ret;

    *info = device_info;
    return 0;
}

int Storage_GetTotalCapacity(const char *device, SceOff *size) {
    int ret = 0;
    SceIoDevInfo device_info;

    if (R_FAILED(ret = Storage_GetDevInfo(device, &device_info)))
        return ret;
        
    *size = device_info.max_size;
    return 0;
}

int Storage_GetFreeCapacity(const char *device, SceOff *size) {
    int ret = 0;
    SceIoDevInfo device_info;

    if (R_FAILED(ret = Storage_GetDevInfo(device, &device_info)))
        return ret;
        
    *size = device_info.free_size;
    return 0;
}

int Storage_GetUsedCapacity(const char *device, SceOff *size) {
    int ret = 0;
    SceIoDevInfo device_info;

    if (R_FAILED(ret = Storage_GetDevInfo(device, &device_info)))
        return ret;
        
    *size = device_info.max_size - device_info.free_size;
    return 0;
}

char *Storage_GetCapacityString(SceOff size) {
    static char size_string[0x10];
    Storage_GetSizeString(size_string, size);
    return size_string;
}
