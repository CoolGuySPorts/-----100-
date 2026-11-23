# Build for libxenon (Docker image free60/libxenon or local toolchain).
# Output: stepa_tutorial.elf  (Aurora and XeLL load .elf directly)
# If this fails, compare with the Makefile in libxenon's examples folder.
ifeq ($(strip $(DEVKITXENON)),)
$(error "DEVKITXENON is not set")
endif

PREFIX  := $(DEVKITXENON)/bin/xenon-
CC      := $(PREFIX)gcc
TARGET  := stepa_tutorial

CFLAGS  := -O2 -I$(DEVKITXENON)/usr/include -m32 -mpowerpc64
LDFLAGS := -n -T $(DEVKITXENON)/app.lds -L$(DEVKITXENON)/usr/lib
LIBS    := -lxenon -lm

all: $(TARGET).elf

$(TARGET).elf: main.c
	$(CC) $(CFLAGS) main.c $(LDFLAGS) $(LIBS) -o $@

clean:
	rm -f *.elf
