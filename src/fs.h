#ifndef _VITAIDENT_FS_H_
#define _VITAIDENT_FS_H_

#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>

int fileExists(const char* path);
int dirExists(const char* path);

#endif