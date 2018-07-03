#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <vitasdk.h>

/// Checks whether a result code indicates success.
#define R_SUCCEEDED(res)   ((res)>=0)
/// Checks whether a result code indicates failure.
#define R_FAILED(res)      ((res)<0)
/// Returns the level of a result code.

SceUInt32 pressed;

SceInt Utils_HandleControls(SceVoid);
SceVoid Utils_GetSizeString(char *string, SceOff size);
char*Utils_StringConcat(char *s1, char *s2);

#endif