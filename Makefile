CC ?= gcc
AS ?= as

QEMU ?= qemu-system-i386

ASFLAGS += --32
CFLAGS += -Wall -Wextra -ffreestanding -fno-stack-protector -mno-sse -mno-mmx -mno-3dnow -mno-80387 -m32
LDFLAGS += -nostdlib -T linker.ld -m32

QEMU_ARGS +=

OBJS = entry.o port.o interrupt_wrapper.o load_gdt.o load_idt.o start.o vga.o utils.o gdt.o idt.o isr.o keyboard.o pic.o game.o timer.o cmos.o
OUT = baresnake.bin
ISO = baresnake.iso

$(OUT): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@

.PHONY: clean run bochs

clean:
	rm -f $(OBJS) $(OUT) $(ISO)
	rm -rf isodir

run: $(OUT)
	$(QEMU) $(QEMU_ARGS) -kernel $(OUT)

$(ISO): $(OUT)
	mkdir -p isodir/boot/grub
	cp $(OUT) isodir/boot/$(OUT)
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue --product-name=baresnake -o $(ISO) isodir

bochs: $(ISO)
	bochs -q -f ./bochsrc

all: $(OUT)
