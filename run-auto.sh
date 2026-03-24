#!/bin/bash

cp test initrd/ 2>/dev/null || true
cd initrd && find . | cpio -o -H newc 2>/dev/null | gzip -9 > ../initramfs.cpio.gz && cd ..

echo "Starting QEMU (Auto-run mode)..."
echo "Program will execute and QEMU will exit automatically"
echo ""

qemu-system-aarch64 \
  -M virt \
  -cpu max,sve=on \
  -m 256 \
  -kernel vmlinuz \
  -initrd initramfs.cpio.gz \
  -append "console=ttyAMA0 rdinit=/init nokaslr" \
  -nographic \
  -no-reboot
