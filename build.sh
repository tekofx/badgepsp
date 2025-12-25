#!/bin/bash


build() {
    rm -dfr build/
    mkdir build
    cp -r assets/ build/
    cd build
    psp-cmake $FLAGS  ..
    make
}

release(){
    cd ..
    rm -dfr BadgePSP
    mkdir BadgePSP
    cp build/EBOOT.PBP BadgePSP/
    cp -r assets/ BadgePSP/
}

if [ "$1" == "dev" ]; then
    FLAGS="-DBUILD_PRX=1"
    build
elif [ "$1" == "release" ]; then
    FLAGS="-DBUILD_PRX=1 -DENC_PRX=1"
    build
    release
else
    echo "Usage: $0 [dev|release]"
    exit 1
fi
