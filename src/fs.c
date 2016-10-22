#include "fs.h"
#include "utils.h"

int fileExists(const char* path)
{
	SceUID dir = sceIoOpen(path, SCE_O_RDONLY, 0777);
	if (dir >= 0)
	{
		sceIoClose(dir);
		return 1;
	}
	else
	{
		return 0;
	}
}

int dirExists(const char* path)
{
	SceUID dir = sceIoDopen(path);
	if (dir >= 0)
	{
		sceIoDclose(dir);
		return 1;
	}
	else 
	{
		return 0;
	}
}

const char * getVitaModel()
{	
	SceOff maxSize = 0;

	SceIoStat stat;
	memset(&stat, 0, sizeof(SceIoStat));
	
	if (sceIoGetstat("ur0:", &stat) >= 0) 
	{		
		SceIoDevInfo info;
		memset(&info, 0, sizeof(SceIoDevInfo));
		int res = sceIoDevctl("ur0:", 0x3001, 0, 0, &info, sizeof(SceIoDevInfo));
		if (res >= 0) 
			maxSize = info.max_size;
		else 
			maxSize = 0;
	}
	
	static char string[16];
	getSizeString(string, maxSize);
	
	if (strcmp(string, "1.50 GB") == 0)
		return "PCH-2000";
	else 
		return "PCH-1000";
}
