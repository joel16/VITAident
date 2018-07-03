cmake_minimum_required(VERSION 2.8)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	if (DEFINED ENV{VITASDK})
		set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
	else()
		message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
	endif()
endif()

set(SHORT_NAME VITAident-GUI)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "VITAident GUI")
set(VITA_TITLEID  "VID000162")
set(VITA_VERSION  "00.75")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -O3 -Wno-unused-variable -Wno-unused-but-set-variable -Wno-format-truncation -fno-lto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

include_directories(
	../common/include
	include
)

add_executable(${SHORT_NAME}
	../common/source/app.c
	../common/source/kernel.c
	../common/source/net.c
	../common/source/power.c
	../common/source/regmgr.c
	../common/source/utils.c
	source/main.c
	source/menus.c
	source/SDL_helper.c
	source/touch.c
)

target_link_libraries(${SHORT_NAME}
	SDL2_ttf
	SDL2_image
	SDL2
	vita2d
	freetype
	png16
	jpeg
	z
	m
	c
	SceAppMgr_stub
	SceAppUtil_stub
	SceAudio_stub
	SceAVConfig_stub
	SceBtForDriver_stub
	SceCommonDialog_stub
	SceCompat_stub
	SceCtrl_stub
	SceDisplay_stub
	SceGxm_stub
	SceHid_stub
	SceIofilemgr_stub 
	SceLibKernel_stub
	SceNet_stub
	SceNetCtl_stub
	ScePower_stub
	ScePvf_stub
	SceRegistryMgr_stub
	SceSysconForDriver_stub
	SceSysmodule_stub 
	SceTouch_stub 
	SceUdcd_stub
	SceUsbstorVStorDriver_stub
	SceVshBridge_stub
)

vita_create_self(${SHORT_NAME}.self ${SHORT_NAME} UNSAFE)
vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
	VERSION ${VITA_VERSION}
	NAME ${VITA_APP_NAME}
	FILE ../sce_sys/icon0.png sce_sys/icon0.png
	FILE ../sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
	FILE ../sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
	FILE ../sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
	FILE res/Ubuntu-R.ttf sce_sys/res/Ubuntu-R.ttf
	FILE res/drive.png sce_sys/res/drive.png
)
