#!/bin/sh

cd build
cmake ..
make

cd ../bin
filename="${1##*/}"
./$filename
