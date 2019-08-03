#ifndef _VITAIDENT_UTILS_H_
#define _VITAIDENT_UTILS_H_

#include <psp2/types.h>

/// Checks whether a result code indicates success.
#define R_SUCCEEDED(res)   ((res)>=0)
/// Checks whether a result code indicates failure.
#define R_FAILED(res)      ((res)<0)
/// Returns the level of a result code.

extern SceUInt32 pressed;

int Utils_ReadControls(void);
int Utils_InitAppUtil(void);
int Utils_TermAppUtil(void);
int Utils_GetEnterButton(void);
int Utils_GetCancelButton(void);

#endif
