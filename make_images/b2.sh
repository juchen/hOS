#!/bin/bash

objcopy -R .note.gnu.build-id -R .eh_frame -O binary ../out/boot.elf boot.bin
objcopy -O binary ../out/secboot.elf secboot.bin

./put_boot.py ./boot.bin hd_H16_S63_C200.img
./put_secboot.py ./secboot.bin hd_H16_S63_C200.img

