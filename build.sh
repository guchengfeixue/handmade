#!/bin/bash

cd $(dirname $0)

if [[ $OSTYPE == "darwin"* ]]; then
    source ./build-sdl.sh
else
    echo "UNSUPOORT PLATFORM $OSTYPE"
    exit
fi
