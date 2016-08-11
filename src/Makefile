TARGET	:= VITAident
TITLE	:= VID000016

OBJS =	main.o

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS  = -Wl,-q -Wall -O3
CXXFLAGS  = $(CFLAGS) -fno-exceptions -std=gnu++11
ASFLAGS = $(CFLAGS)


LIBDIR =
LDFLAGS = 
LIBS = -lSceKernel_stub -lScePower_stub

eboot.bin: $(TARGET).velf
	vita-make-fself $< $@

%.velf: %.elf
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o: %.png
	$(PREFIX)-ld -r -b binary -o $@ $^

clean:
	@rm -rf $(TARGET).velf $(TARGET).elf $(OBJS)

vpk: $(TARGET).velf
	vita-make-fself $< eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLE) "$(TARGET)" param.sfo
	cp -f param.sfo ../sce_sys/param.sfo
	
	#------------ Comment this if you don't have 7zip ------------------
	7z a -tzip $(TARGET).vpk -r ../sce_sys/* eboot.bin 
	#-------------------------------------------------------------------
