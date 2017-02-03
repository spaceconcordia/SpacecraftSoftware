#!/bin/bash
# Starts the Qemu emulator.

cd ~/buildroot-qemu

QEMU_AUDIO_DRV=none qemu-system-arm \
	-M versatilepb \
	-m 256M \
	-kernel images/zImage \
	-dtb images/versatile-pb.dtb \
	-drive file=images/rootfs.ext2,if=scsi,format=raw \
	-nographic \
	-append "root=/dev/sda console=ttyAMA0,115200" \
	-net nic,model=rtl8139 \
	-net user
