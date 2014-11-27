#!/bin/bash

./put_boot.py ../src-git/boot.bin hd_H16_S63_C200.img
./put_secboot.py ../src-git/secboot.bin hd_H16_S63_C200.img
bochs

