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

## To build:
#### - cmake .
#### - ninja