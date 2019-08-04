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
  plugin
)

link_directories(
  ${CMAKE_BINARY_DIR}/vitaident_kernel_stubs
  ${CMAKE_BINARY_DIR}/vitaident_user_stubs
  ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(${PROJECT_NAME}
  common/kernel.c
  source/main.c
  source/menus.c
  source/utils.c
)

add_dependencies(${PROJECT_NAME} vitaident_kernel.skprx)

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
  taihen_stub
  vitaident_user_stub_weak
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME} UNSAFE)

add_executable(vitaident_kernel
  plugin/kernel.c
)

set_target_properties(vitaident_kernel
  PROPERTIES LINK_FLAGS
  -nostdlib
)

target_link_libraries(vitaident_kernel
  SceModulemgrForKernel_stub
  SceSysmemForDriver_stub
  SceSysrootForKernel_stub
  taihenForKernel_stub
)

vita_create_self(vitaident_kernel.skprx vitaident_kernel
  CONFIG ${CMAKE_SOURCE_DIR}/plugin/kernel_exports.yml
  UNSAFE
)

vita_create_stubs(vitaident_kernel_stubs vitaident_kernel ${CMAKE_SOURCE_DIR}/plugin/kernel_exports.yml KERNEL)

add_executable(vitaident_user
  plugin/user.c
)

set_target_properties(vitaident_user
  PROPERTIES LINK_FLAGS
  -nostartfiles
)

target_link_libraries(vitaident_user
  taihen_stub
  vitaident_kernel_stub
)

vita_create_self(vitaident_user.suprx vitaident_user
  CONFIG ${CMAKE_SOURCE_DIR}/plugin/user_exports.yml
  UNSAFE
)

vita_create_stubs(vitaident_user_stubs vitaident_user ${CMAKE_SOURCE_DIR}/plugin/user_exports.yml)

add_dependencies(vitaident_user vitaident_kernel_stubs)
add_dependencies(${PROJECT_NAME} vitaident_kernel.skprx)
add_dependencies(${PROJECT_NAME} vitaident_user_stubs)
add_dependencies(${PROJECT_NAME} vitaident_user.suprx)

vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE ${CMAKE_BINARY_DIR}/vitaident_kernel.skprx vitaident_kernel.skprx
  FILE ${CMAKE_BINARY_DIR}/vitaident_user.suprx vitaident_user.suprx
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE res/drive.png res/drive.png
  FILE res/Ubuntu-R.ttf res/Ubuntu-R.ttf
)
