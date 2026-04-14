UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    CC = gcc
    ASMC = nasm
    LD = ld
    CAT = cat
    OBJCPY = objcopy
    DD = dd
    LDFLAGS = -m elf_i386 -T linker.ld
endif

BUILDDIR := bin
OBJDIR := obj

CFLAGS = -Wall -m32 -ffreestanding -fno-pic -fno-pie
ASMFLAGS = -f elf32

BOOTLOADER = src/bootloader.s
LINKER_SCRIPT = linker.ld

C_SOURCES := $(wildcard src/*.c)
ASM_SOURCES := $(filter-out $(BOOTLOADER), $(wildcard src/*.s))

C_OBJECTS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(C_SOURCES))
ASM_OBJECTS := $(patsubst src/%.s,$(OBJDIR)/%.o,$(ASM_SOURCES))

KERNEL_TMP := $(BUILDDIR)/kernel.tmp
KERNEL_BIN := $(BUILDDIR)/kernel.bin

BOOTLOADER_BIN := $(BUILDDIR)/bootloader.bin
OS_IMAGE := $(BUILDDIR)/TheOS.img

all: $(OS_IMAGE)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Bootloader (RAW binary)
$(BOOTLOADER_BIN): $(BOOTLOADER) | $(BUILDDIR)
	nasm -f bin $< -o $@

# C objects
$(OBJDIR)/%.o: src/%.c | $(BUILDDIR) $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ASM objects (kernel only)
$(OBJDIR)/%.o: src/%.s | $(BUILDDIR) $(OBJDIR)
	$(ASMC) $(ASMFLAGS) $< -o $@

# Link kernel
$(KERNEL_TMP): $(C_OBJECTS) $(ASM_OBJECTS) | $(BUILDDIR)
	$(LD) $(LDFLAGS) -o $@ $^

# Kernel binary
$(KERNEL_BIN): $(KERNEL_TMP) | $(BUILDDIR)
	$(OBJCPY) -O binary $< $@

# Disk image (bootloader + kernel)
$(OS_IMAGE): $(BOOTLOADER_BIN) $(KERNEL_BIN) | $(BUILDDIR)
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$(BOOTLOADER_BIN) of=$@ bs=512 conv=notrunc
	dd if=$(KERNEL_BIN) of=$@ bs=512 seek=1 conv=notrunc

clean:
	rm -rf $(BUILDDIR) $(OBJDIR)

run: $(OS_IMAGE)
	qemu-system-i386 -drive file=$(OS_IMAGE),format=raw -serial stdio
