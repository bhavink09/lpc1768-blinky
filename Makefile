#Copyright (c) 2008-2010 Jakub Piotr Cłapa
# This program is released under the new BSD license.
ARCH = arm-none-eabi

# Replace space in path with \
# We replace that back once addprefix is done below

#CUR_DIR_TMP = $(shell pwd)
#space := 
#space += 
#CUR_DIR = $(subst $(space),\,$(CUR_DIR_TMP))

# Tool definitions
CC      = $(ARCH)-gcc
LD      = $(ARCH)-gcc
AR      = $(ARCH)-ar
AS      = $(ARCH)-as
CP      = $(ARCH)-objcopy
OD	= $(ARCH)-objdump
SIZE	= $(ARCH)-size
RM	= rm

# Flags
INC_DIR  = "CMSIS" "inc" "inc/freertos"
COREFLAGS = -mthumb -mcpu=cortex-m3 --specs=nosys.specs
CFLAGS_1  = $(COREFLAGS)
CFLAGS_1  += -W -Wall -O0 -fgnu89-inline -g
CFLAGS_1  += -ffunction-sections -fdata-sections
CFLAGS_1  += $(addprefix -I, $(INC_DIR))

# Replace \ back to spaces now
CFLAGS  = $(subst \,$(space),$(CFLAGS_1))

ASFLAGS  = $(COREFLAGS)
LDFLAGS  = $(COREFLAGS) #--gc-sections
CPFLAGS  =
ODFLAGS  = -x --syms
PRFLAGS ?=

# Source files
LINKER_SCRIPT = LPC1768-flash.ld
CSRCS  = $(wildcard src/*.c)
CSRCS += $(wildcard src/drivers/*.c)
CSRCS += $(wildcard src/utils/*.c)
CSRCS += $(wildcard src/network/*.c)
CSRCS += $(wildcard src/freertos/*.c)
CSRCS += $(wildcard src/main/*.c)
CSRCS += $(wildcard src/app/*.c)
CSRCS += $(wildcard CMSIS/*.c)
ASRCS  = 

OBJDIR := install
OBJS   = $(CSRCS:%.c=install/%.o) $(ASRCS:%.s=install/%.o)


.PHONY: all size clean nuke dirs

all: dirs $(OBJDIR)/main.hex

size: $(OBJDIR)/main.elf
	@$(SIZE) $<

$(OBJDIR)/main.hex: $(OBJDIR)/main.elf
	$(CP) $(CPFLAGS) -O ihex $< $@;
	@rm -rf *.d
	@rm -rf CMSIS/*.d
	@rm -rf lib/*.d
	@rm -rf uIP/*.d

$(OBJDIR)/main.elf: $(LINKER_SCRIPT) $(OBJS)
	$(LD) $(LDFLAGS) -T $^ -o $@;
	$(OD) $(ODFLAGS) $@ > $(@:.elf=.dump)
	@$(SIZE) $@;

$(OBJDIR)/%.o: %.c
#	@echo "$(CUR_DIR)"
	@$(CC) $(CFLAGS) -MM $< -MF $(OBJDIR)/$*.d -MP
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

dirs: $(OBJDIR)

$(OBJDIR):
	@mkdir -p install/src/drivers
	@mkdir -p install/src/utils
	@mkdir -p install/src/network
	@mkdir -p install/src/main
	@mkdir -p install/src/freertos
	@mkdir -p install/src/app
	@mkdir -p install/CMSIS

clean:
	@-rm -rf install
	@-\
for D in "." "**"; do \
  rm -f $$D/*.o $$D/*.d $$D/*.lst $$D/*.dump $$D/*.map; \
done

-include $(CSRCS:.c=.d)
