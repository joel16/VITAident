#ifndef _VITAIDENT_FS_H_
#define _VITAIDENT_FS_H_

#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/devctl.h>

#include <string.h>

SceInt fileExists(const char * path);
SceInt dirExists(const char * path);
SceInt writeFile(char * file, SceVoid * buf, SceInt size);
SceOff getPartitionInfo(SceInt storage, const char * partition);
char * getVitaModel(SceVoid);

#endif