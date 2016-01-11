#!/bin/sh

cd build
make

cd ../bin
filename="${1##*/}"
./$filename
