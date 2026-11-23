ifeq ($(strip $(DEVKITXENON)),)
$(error "DEVKITXENON is not set")
endif

PREFIX  := $(DEVKITXENON)/bin/xenon-
CC      := $(PREFIX)gcc
OBJCOPY := $(PREFIX)objcopy
STRIP   := $(PREFIX)strip
TARGET  := stepa_tutorial

MACHDEP := -DXENON -m32 -mpowerpc64 -mhard-float -mcpu=cell -mtune=cell -maltivec -fno-pic
CFLAGS  := -O2 $(MACHDEP) -I$(DEVKITXENON)/usr/include
LDFLAGS := $(MACHDEP) -n -T $(DEVKITXENON)/app.lds \
           -L$(DEVKITXENON)/usr/lib \
           -L$(DEVKITXENON)/xenon/lib/32 \
           -u read -u _start -u exc_base
LIBS    := -Wl,--start-group -lxenon -lm -lc -Wl,--end-group

all: $(TARGET).elf

$(TARGET).elf: main.c
	$(CC) $(CFLAGS) main.c $(LDFLAGS) $(LIBS) -o $(TARGET).raw
	$(OBJCOPY) -O elf32-powerpc --adjust-vma 0x80000000 $(TARGET).raw $@
	$(STRIP) $@
	rm -f $(TARGET).raw

clean:
	rm -f *.elf *.raw
