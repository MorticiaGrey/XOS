#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/xos.kernel isodir/boot/xos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "xos" {
	multiboot /boot/xos.kernel
}
EOF
grub-mkrescue -o xos.iso isodir
