#!/bin/sh

echo "// Auto generated by build.sh" > version.h
echo "#ifndef VERSION" >> version.h
echo "#define VERSION \"$(cat ../version)\"" >> version.h
echo "#endif" >> version.h

gcc -o remote-capture-linux receiver_linux.c -lpthread

