#!/bin/bash

cd $(dirname $0)

if [[ $OSTYPE == "darwin"* ]]; then
    exe="sdl_handmade"
else
    echo "UNSUPOORT PLATFORM $OSTYPE"
    exit
fi

cd data/ && ../build/$exe
