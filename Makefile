# ============================================
# Toolchain Configuration 
# ============================================
CC = /opt/homebrew/opt/llvm/bin/clang
TOOLCHAIN = $(HOME)/arm-cross/aarch64-toolchain
SYSROOT = $(TOOLCHAIN)/aarch64-none-linux-gnu/libc

TARGET_FLAGS = --target=aarch64-linux-gnu \
               --sysroot=$(SYSROOT) \
               --gcc-toolchain=$(TOOLCHAIN) \
               -fuse-ld=lld

CFLAGS = $(TARGET_FLAGS) -O3 -flto -Wall -static -g
CFLAGS += -march=armv8-a+sve2 -fno-vectorize -fno-slp-vectorize #-msve-vector-bits=256

# ============================================
# Flexible Source Configuration
# ============================================

# Strategy 1: Auto-include entire directories
AUTO_SRC_DIRS = .

# Strategy 2: Manually cherry-pick specific files
MANUAL_SRCS = 

# ============================================
# Flexible Include Path Configuration  
# ============================================

# Strategy 1: Auto-add directories containing source files (recommended)
# This automatically finds dirs with .c files, avoiding manual sync
AUTO_INC_DIRS = $(sort $(dir $(SRCS)))

# Strategy 2: Manually add specific include-only directories (no source files there)
# Examples: dedicated include/, third-party libs, architecture headers
MANUAL_INC_DIRS = 

# ============================================
# Source & Include Aggregation (do not modify below)
# ============================================

# Source aggregation
AUTO_SRCS = $(foreach dir,$(AUTO_SRC_DIRS),$(wildcard $(dir)/*.c))
SRCS = $(AUTO_SRCS) $(MANUAL_SRCS)
OBJS = $(patsubst %.c,build/%.o,$(SRCS))

# Include path aggregation
INC_DIRS = $(sort $(AUTO_INC_DIRS) $(MANUAL_INC_DIRS))
CFLAGS += $(addprefix -I,$(INC_DIRS))

# ============================================
# Target Configuration
# ============================================
TARGET = test

.PHONY: all clean pack dirs

# ============================================
# Build Rules
# ============================================

all: dirs $(TARGET) pack
	@echo "Build complete. Ready for debugging."

BUILD_DIRS = $(addprefix build/,$(sort $(dir $(SRCS))))

dirs:
	@mkdir -p $(BUILD_DIRS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	file $(TARGET)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

pack: $(TARGET)
	@cp $(TARGET) initrd/
	@cd initrd && find . | cpio -o -H newc 2>/dev/null | gzip -9 > ../initramfs.cpio.gz && cd ..
	@echo "Initramfs updated with latest binary"

clean:
	@rm -rf build/ $(TARGET)
	@echo "Clean complete."