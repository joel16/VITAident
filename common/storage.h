#ifndef _VITAIDENT_STORAGE_H_
#define _VITAIDENT_STORAGE_H_

int Storage_GetTotalCapacity(const char *device, SceOff *size);
int Storage_GetFreeCapacity(const char *device, SceOff *size);
int Storage_GetUsedCapacity(const char *device, SceOff *size);
char *Storage_GetCapacityString(SceOff size);

#endif
