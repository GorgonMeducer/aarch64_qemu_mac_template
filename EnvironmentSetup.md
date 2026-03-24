
# AArch64 Linux Development Environment on Apple Silicon (macOS)

A step-by-step guide to setting up a cross-compilation and QEMU emulation environment for SVE/SVE2 development on macOS.

## Prerequisites

- macOS running on Apple Silicon (M1/M2/M3)
- Homebrew package manager
- Internet connection for downloading toolchains and images

## Step 1: Install Base Tools

Install LLVM (cross-compiler), LLD (linker), and QEMU (emulator) via Homebrew.

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install LLVM toolchain and QEMU
brew install llvm lld qemu
```

Verify installations:
```bash
/opt/homebrew/opt/llvm/bin/clang --version  # Should show Homebrew clang version 22.x
qemu-system-aarch64 --version              # Should show QEMU version 9.x
```

## Step 2: Setup Cross-Compilation Toolchain

Download the Arm GNU Toolchain. We use it for the Linux sysroot (C library headers and startup files), not for the compiler itself.

```bash
mkdir -p ~/arm-cross && cd ~/arm-cross

# Download the x86_64-hosted toolchain (we only need its sysroot and libgcc)
wget https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz

tar -xf arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz
mv arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu aarch64-toolchain
```

**Key paths to remember:**
- **Sysroot**: `~/arm-cross/aarch64-toolchain/aarch64-none-linux-gnu/libc` (contains C library headers and libs)
- **GCC Toolchain**: `~/arm-cross/aarch64-toolchain` (contains libgcc and CRT files needed by Clang)

## Step 3: Project Configuration and Build

### Directory Structure
Create your project directory:
```bash
mkdir -p ~/sve2-dev/hello-world
cd ~/sve2-dev/hello-world
```

Create a `Makefile` with the following content. This configures Clang to cross-compile for AArch64 Linux using the sysroot from Step 2.

```makefile
# Compiler configuration
CC = /opt/homebrew/opt/llvm/bin/clang
TOOLCHAIN = /Users/gabriel/arm-cross/aarch64-toolchain
SYSROOT = $(TOOLCHAIN)/aarch64-none-linux-gnu/libc

# Target and linker flags
TARGET_FLAGS = --target=aarch64-linux-gnu \
               --sysroot=$(SYSROOT) \
               --gcc-toolchain=$(TOOLCHAIN) \
               -fuse-ld=lld

# Static linking avoids dynamic library path issues in QEMU
CFLAGS = $(TARGET_FLAGS) -O2 -Wall -static

TARGET = hello

.PHONY: all clean

all: $(TARGET)

$(TARGET): hello.c
	$(CC) $(CFLAGS) -o $@ $<
	file $(TARGET)  # Verify output is ARM64 executable

clean:
	rm -f $(TARGET)
```

Create a sample `hello.c`:
```c
#include <stdio.h>

int main(void) {
    printf("Hello from AArch64 Linux!\n");
    return 0;
}
```

Compile:
```bash
make
```

Expected output from `file hello`:
```
hello: ELF 64-bit LSB executable, ARM aarch64, version 1 (GNU/Linux), statically linked
```

## Step 4: QEMU System Setup

### 4.1 Download System Images

We need a Linux kernel and a minimal root filesystem.

```bash
cd ~/sve2-dev/hello-world

# Ubuntu Cloud kernel (supports SVE)
wget https://cloud-images.ubuntu.com/jammy/current/unpacked/jammy-server-cloudimg-arm64-vmlinuz-generic
mv jammy-server-cloudimg-arm64-vmlinuz-generic vmlinuz

# Alpine mini rootfs (contains BusyBox and musl libc)
wget https://dl-cdn.alpinelinux.org/alpine/v3.19/releases/aarch64/alpine-minirootfs-3.19.0-aarch64.tar.gz
```

### 4.2 Build Initramfs

The initramfs is a compressed archive containing the root filesystem that Linux mounts at boot.

```bash
# Extract Alpine as base
rm -rf initrd
mkdir initrd
tar -xzf alpine-minirootfs-3.19.0-aarch64.tar.gz -C initrd

# Copy your application
cp hello initrd/

# Create init script (replaces default init)
cat > initrd/init << 'EOF'
#!/bin/sh
mount -t proc proc /proc
mount -t sysfs sys /sys
mount -t devtmpfs dev /dev 2>/dev/null || true

echo "=========== Starting Hello World ============"
/hello

echo "=========== Program Finished, Entering Shell ========="
exec /bin/sh
EOF
chmod +x initrd/init

# Package into cpio.gz
cd initrd
find . | cpio -o -H newc | gzip -9 > ../initramfs.cpio.gz
cd ..
```

### 4.3 Run QEMU

Launch the virtual machine with your kernel and initramfs.

```bash
qemu-system-aarch64 \
  -M virt \
  -cpu max,sve=on \
  -m 256 \
  -kernel vmlinuz \
  -initrd initramfs.cpio.gz \
  -append "console=ttyAMA0 rdinit=/init" \
  -nographic
```

**Parameter explanation:**
- `-M virt`: ARM Virt platform (generic virtual board)
- `-cpu max,sve=on`: Enable maximum CPU features and SVE support
- `-m 256`: Allocate 256MB RAM
- `-append "rdinit=/init"`: Run our init script as the first process
- `-nographic`: Serial output to terminal (no GUI window)

### 4.4 Exit QEMU

**Do not type `exit` in the shell** (this kills init and causes a kernel panic). Instead, use the QEMU escape sequence:

Press `Ctrl+A` then `X` (release Ctrl before pressing X).

Alternatively, from another terminal:
```bash
pkill qemu-system-aarch64
```

## Step 5: VSCode Integration (Optional)

### Install C/C++ Extension
Install the **Microsoft C/C++** extension (ID: `ms-vscode.cpptools`) from the Extensions marketplace.

### Configure IntelliSense
Create `.vscode/c_cpp_properties.json` to enable code completion and navigation for AArch64 Linux headers:

```json
{
    "configurations": [
        {
            "name": "AArch64 Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/Users/gabriel/arm-cross/aarch64-toolchain/aarch64-none-linux-gnu/libc/usr/include/**",
                "/Users/gabriel/arm-cross/aarch64-toolchain/aarch64-none-linux-gnu/libc/usr/include/aarch64-linux-gnu/**"
            ],
            "defines": [
                "__aarch64__",
                "__linux__",
                "__SVE__"
            ],
            "compilerPath": "/opt/homebrew/opt/llvm/bin/clang",
            "cStandard": "c11",
            "intelliSenseMode": "linux-clang-arm64"
        }
    ],
    "version": 4
}
```

## Development Workflow Summary

**Daily development loop:**
1. **Edit**: Modify source code in VSCode
2. **Build**: Run `make` to generate ARM64 static binary
3. **Update**: Copy binary to initrd and repack initramfs:
   ```bash
   cp hello initrd/
   cd initrd && find . | cpio -o -H newc | gzip -9 > ../initramfs.cpio.gz && cd ..
   ```
4. **Test**: Run the QEMU command from Step 4.3
5. **Debug**: (Optional) Configure GDB remote debugging for step-through debugging

## Key Success Factors

1. **Use `--gcc-toolchain`**: This allows Clang to find `crtbeginT.o` and `libgcc` from the Arm toolchain
2. **Static linking (`-static`)**: Avoids dynamic library path issues when running in the minimal initramfs
3. **Ubuntu Cloud kernel + Alpine initramfs**: A stable combination that boots quickly and supports SVE
4. **Enable `sve=on`**: Essential for SVE/SVE2 instruction support in QEMU
5. **Proper exit method**: Use `Ctrl+A X` instead of typing `exit` in the initramfs shell
