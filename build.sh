#!/bin/bash

rm -dfr build/
mkdir build
cd build
psp-cmake -DBUILD_PRX=1 -DENC_PRX=1  ..
make
