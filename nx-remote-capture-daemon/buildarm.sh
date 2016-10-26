#!/bin/sh

arm-linux-gnueabi-gcc -DDEBUG -O4 -Wall -lpthread -o nx-remote-capture-daemon nx_broadcast_receiver.c --sysroot=~/NX500/NX500_packages/standard-armv7l -Wl,-dynamic-linker,/lib/ld-2.13.so

