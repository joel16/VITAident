#ifndef _VITAIDENT_FS_H_
#define _VITAIDENT_FS_H_

#include <vitasdk.h>

SceBool fileExists(const char * path);
SceBool dirExists(const char * path);
SceInt writeFile(char * file, SceVoid * buf, SceInt size);
SceOff getPartitionInfo(SceInt storage, const char * partition);
char * getVitaModel(SceVoid);

#endif