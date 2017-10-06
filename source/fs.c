#include <string.h>

#include "fs.h"
#include "utils.h"

SceBool fileExists(const char * path)
{
	SceUID file = 0;
	
	if (R_SUCCEEDED(file = sceIoOpen(path, SCE_O_RDONLY, 0777)))
	{
		sceIoClose(file);
		return SCE_TRUE;
	}
	
	return SCE_FALSE;
}

SceBool dirExists(const char * path)
{	
	SceUID dir = 0;
	
	if (R_SUCCEEDED(dir = sceIoDopen(path)))
	{
		sceIoDclose(dir);
		return SCE_TRUE;
	}
	
	return SCE_FALSE;
}

SceInt writeFile(char * file, SceVoid * buf, SceInt size) 
{
	SceUID fd = 0;
	
	if (R_SUCCEEDED(sceIoOpen(file, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777)))
	{
		SceInt written = sceIoWrite(fd, buf, size);
		sceIoClose(fd);
		return written;
	}
		
	return fd;
}

SceOff getPartitionInfo(SceInt storage, const char * partition)
{
	SceOff maxSize = 0;
	SceOff freeSize = 0;

	SceIoStat stat;
	memset(&stat, 0, sizeof(SceIoStat));
	
	if (R_SUCCEEDED(sceIoGetstat(partition, &stat))) 
	{		
		SceIoDevInfo info;
		memset(&info, 0, sizeof(SceIoDevInfo));
		
		if (R_SUCCEEDED(sceIoDevctl(partition, 0x3001, 0, 0, &info, sizeof(SceIoDevInfo))))
		{
			freeSize = info.free_size;
			maxSize = info.max_size;
		}
	}
	
	if (storage == 0)
		return freeSize;
	
	return maxSize;
}

char * getVitaModel(SceVoid)
{	
	SceOff maxSize = getPartitionInfo(1, "ur0:");
	
	static char string[16];
	getSizeString(string, maxSize);
	
	if (strcmp(string, "1.50 GB") == 0)
		return "2000";
	
	return "1000";
}