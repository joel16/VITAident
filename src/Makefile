TARGET := VITAident
TITLE_ID := VID000016
SOURCES := src

OBJS = app.o font.o fs.o graphics.o kernel.o main.o net.o power.o screenshot.o utils.o \

PREFIX   = arm-vita-eabi
CC       = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS   = -Wl,-q -Wall -Werror -O3
CXXFLAGS = $(CFLAGS) -std=c++11 -fno-rtti -fno-exceptions
ASFLAGS  = $(CFLAGS)

LIBDIR = 
LDFLAGS = 
LIBS := -lSceAppMgr_stub -lSceAppUtil_stub -lSceCtrl_stub -lSceDisplay_stub -lSceLibKernel_stub \
		-lSceNet_stub -lSceNetCtl_stub -lScePower_stub -lSceSysmodule_stub -lSceVshBridge_stub \
		-lSceUdcd_stub -lSceUsbstorVStorDriver_stub

all: $(TARGET).vpk

%.vpk: eboot.bin
	vita-mksfoex -d PARENTAL_LEVEL=1 -s APP_VER=00.70 -s TITLE_ID=$(TITLE_ID) "$(TARGET)" param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin \
		--add ../sce_sys/icon0.png=sce_sys/icon0.png \
		--add ../sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png \
		--add ../sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png \
		--add ../sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml \
	$(TARGET).vpk
	
eboot.bin: $(TARGET).velf
	vita-make-fself -c $< $@

%.velf: %.elf
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o: %.png
	$(PREFIX)-ld -r -b binary -o $@ $^
%.o: %.txt
	$(PREFIX)-ld -r -b binary -o $@ $^

clean:
	@rm -rf $(TARGET).vpk $(TARGET).velf $(TARGET).elf $(OBJS) \
		eboot.bin param.sfo
