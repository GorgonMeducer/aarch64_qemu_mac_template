CC = /opt/homebrew/opt/llvm/bin/clang
TOOLCHAIN = $(HOME)/arm-cross/aarch64-toolchain
SYSROOT = $(TOOLCHAIN)/aarch64-none-linux-gnu/libc

TARGET_FLAGS = --target=aarch64-linux-gnu \
               --sysroot=$(SYSROOT) \
               --gcc-toolchain=$(TOOLCHAIN) \
               -fuse-ld=lld

CFLAGS = $(TARGET_FLAGS) -O3 -flto -Wall -static -g

CFLAGS  += -march=armv8-a+sve2 -fno-vectorize -fno-slp-vectorize -msve-vector-bits=256

TARGET = test

.PHONY: all clean pack

all: $(TARGET) pack
	@echo "Build complete. Ready for debugging."

$(TARGET): test_entry.c
	$(CC) $(CFLAGS) -o $@ $<
	file $(TARGET)

pack:
	@cp $(TARGET) initrd/
	@cd initrd && find . | cpio -o -H newc 2>/dev/null | gzip -9 > ../initramfs.cpio.gz && cd ..
	@echo "Initramfs updated with latest binary"

clean:
	@rm -f $(TARGET)
	@echo "Clean complete."