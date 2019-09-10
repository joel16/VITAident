#include <psp2/apputil.h>
#include <psp2/ctrl.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/shellutil.h>
#include <psp2/sysmodule.h>
#include <psp2/system_param.h>
#include <string.h>

#include "utils.h"

static SceCtrlData pad, old_pad;

int Utils_ReadControls(void) {
	memset(&pad, 0, sizeof(SceCtrlData));
	sceCtrlPeekBufferPositive(0, &pad, 1);

	pressed = pad.buttons & ~old_pad.buttons;
	
	old_pad = pad;
	return 0;
}

int Utils_InitAppUtil(void) {
	SceAppUtilInitParam init;
	SceAppUtilBootParam boot;
	memset(&init, 0, sizeof(SceAppUtilInitParam));
	memset(&boot, 0, sizeof(SceAppUtilBootParam));
	
	int ret = 0;
	
	if (R_FAILED(ret = sceAppUtilInit(&init, &boot)))
		return ret;

	if (R_FAILED(ret = sceAppUtilMusicMount()))
		return ret;
	
	return 0;
}

int Utils_TermAppUtil(void) {
	int ret = 0;

	if (R_FAILED(ret = sceAppUtilMusicUmount()))
	
	if (R_FAILED(ret = sceAppUtilShutdown()))
		return ret;
	
	return 0;
}

int Utils_InitNet(void) {
	int ret = 0;

	if (sceSysmoduleIsLoaded(SCE_SYSMODULE_NET) != SCE_SYSMODULE_LOADED)
		sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	
	static char memory[0x10 * 0x400];

	SceNetInitParam param;
	param.memory = memory;
	param.size = sizeof(memory);
	param.flags = 0;

	if (R_FAILED(ret = sceNetInit(&param)))
		return ret;

	if (R_FAILED(ret = sceNetCtlInit()))
		return ret;

	return 0;
}

int Utils_TermNet(void) {
	int ret = 0;

	sceNetCtlTerm();

	if (R_FAILED(ret = sceNetTerm()))
		return ret;

	return 0;
}

int Utils_GetEnterButton(void) {
	int button = 0;
	sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, &button);
	
	if (button == SCE_SYSTEM_PARAM_ENTER_BUTTON_CIRCLE)
		return SCE_CTRL_CIRCLE;
	else
		return SCE_CTRL_CROSS;

	return 0;
}

int Utils_GetCancelButton(void) {
	int button = 0;
	sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, &button);
	
	if (button == SCE_SYSTEM_PARAM_ENTER_BUTTON_CIRCLE)
		return SCE_CTRL_CROSS;
	else
		return SCE_CTRL_CIRCLE;

	return 0;
}
