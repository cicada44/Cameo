#!/bin/sh

cmake --preset release
cmake --build --preset release
./build/release/bin/cameo
