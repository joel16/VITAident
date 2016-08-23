ARCH ?= arm-vita-eabi
AS = $(ARCH)-as
AR = $(ARCH)-ar
RANLIB = $(ARCH)-ranlib

TARGETS = libSceVshBridge_stub.a

SceVshBridge_OBJS = SceVshBridge_SceVshBridge__vshSblAimgrGetConsoleId.o
SceKernel_OBJS =
ALL_OBJS=

all: $(TARGETS)

define LIBRARY_template
 $(1): $$($(1:lib%_stub.a=%)_OBJS)
 ALL_OBJS += $$($(1:lib%_stub.a=%)_OBJS)
endef

$(foreach library,$(TARGETS),$(eval $(call LIBRARY_template,$(library))))

all: $(TARGETS)

clean:

	rm -f $(TARGETS) $(ALL_OBJS)

$(TARGETS):
	$(AR) cru $@ $?
	$(RANLIB) $@

%.o: %.S
	$(AS) $< -o $@
