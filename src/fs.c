#include "fs.h"

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