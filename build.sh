#!/bin/bash

if [[ $1 == "debug" ]];
then
    mkdir -p build
    cd build
    cmake -DCMAKE_BUILD_TYPE=DEBUG ..
    cmake --build . -- -j
elif [[ $1 == "rebuild" ]];
then
    rm -rf build
    $0
else
    mkdir -p build
    cd build
    cmake -DCMAKE_BUILD_TYPE=RELEASE ..
    cmake --build . -- -j
fi;
