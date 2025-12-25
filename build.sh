#!/bin/bash

rm -dfr build/
mkdir build
cp image.png build/
cp font.ttf build/
cd build
psp-cmake -DBUILD_PRX=1 -DENC_PRX=1  ..
make
