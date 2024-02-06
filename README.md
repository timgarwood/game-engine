# Development environment installation instructions

## Install MSYS2
https://www.msys2.org/

use the UCRT version of mingw for everything

## Install the UCRT mingw toolchain
#### pacman -S mingw-w64-ucrt-x86_64-toolchain

## Install cmake
#### pacman -S mingw-w64-ucrt-x86_64-cmake

## Install SDL2
#### pacman -S mingw-w64-ucrt-x86_64-SDL2

## Install json cpp
#### pacman -S mingw-w64-ucrt-x86_64-jsoncpp

## Install stb
#### pacman -S mingw-w64-ucrt-x86_64-stb

## Install bullet (physics)
#### pacman -S mingw-w64-ucrt-x86_64-bullet

## To build:
#### - cmake .
#### - ninja -v