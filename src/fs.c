#include "fs.h"
#include "utils.h"

SceInt fileExists(const char * path)
{
	SceUID file = sceIoOpen(path, SCE_O_RDONLY, 0777);
	
	if (file >= 0)
	{
		sceIoClose(file);
		return 1;
	}
	
	return 0;
}

SceInt dirExists(const char * path)
{
	SceUID dir = sceIoDopen(path);
	
	if (dir >= 0)
	{
		sceIoDclose(dir);
		return 1;
	}
	
	return 0;
}

SceInt writeFile(char * file, SceVoid * buf, SceInt size) 
{
	SceUID fd = sceIoOpen(file, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777);
	
	if (fd < 0)
		return fd;

	SceInt written = sceIoWrite(fd, buf, size);
	sceIoClose(fd);
	
	return written;
}

SceOff getPartitionInfo(SceInt storage, const char * partition)
{
	SceOff maxSize = 0;
	SceOff freeSize = 0;

	SceIoStat stat;
	memset(&stat, 0, sizeof(SceIoStat));
	
	if (sceIoGetstat(partition, &stat) >= 0) 
	{		
		SceIoDevInfo info;
		memset(&info, 0, sizeof(SceIoDevInfo));
		SceInt res = sceIoDevctl(partition, 0x3001, 0, 0, &info, sizeof(SceIoDevInfo));
		
		if (res >= 0) 
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