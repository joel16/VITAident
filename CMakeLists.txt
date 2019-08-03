cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(VITAident)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "VITAident")
set(VITA_TITLEID  "VITAIDENT")
set(VITA_VERSION  "00.80")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

include_directories(
  common
  include
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(${PROJECT_NAME}
  common/kernel.c
  source/main.c
  source/menus.c
  source/utils.c
)

target_link_libraries(${PROJECT_NAME}
  vita2d
  freetype
  png
  jpeg
  z
  c
  m
  SceAppMgr_stub
  SceAppUtil_stub
  SceCommonDialog_stub
  SceCtrl_stub
  SceDisplay_stub
  SceGxm_stub
  ScePower_stub
  SceRtc_stub
  SceShellSvc_stub
  SceSysmodule_stub
  SceVshBridge_stub
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME} UNSAFE)
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE res/drive.png res/drive.png
  FILE res/Ubuntu-R.ttf res/Ubuntu-R.ttf
)
