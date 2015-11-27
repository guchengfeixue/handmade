#!/bin/sh

mkdir ../build
pushd ../build
gcc -g -Wall -Wno-unused-variable -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -DHANDMADE_WIN32=1 -g -std=c++11 ../code/handmade.cpp -o handmade.dll -shared
gcc -g -Wall -Wno-unused-variable -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -DHANDMADE_WIN32=1 -g -std=c++11 ../code/win32_handmade.cpp -o handmade.exe -luser32 -lgdi32 -lwinmm
popd
