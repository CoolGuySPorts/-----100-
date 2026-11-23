ifeq ($(strip $(DEVKITXENON)),)
$(error "DEVKITXENON is not set")
endif

PREFIX  := $(DEVKITXENON)/bin/xenon-
CC      := $(PREFIX)gcc
TARGET  := stepa_tutorial

CFLAGS  := -O2 -I$(DEVKITXENON)/usr/include -m64 -mcpu=cell -mtune=cell -fno-pic -fno-common -maltivec
LDFLAGS := -m64 -n -T $(DEVKITXENON)/app.lds -L$(DEVKITXENON)/usr/lib -L$(DEVKITXENON)/xenon/lib
LIBS    := -lxenon -lm

all: $(TARGET).elf

$(TARGET).elf: main.c
	$(CC) $(CFLAGS) main.c $(LDFLAGS) $(LIBS) -o $@

clean:
	rm -f *.elf
