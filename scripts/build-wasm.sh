#!/usr/bin/env bash
set -e

BASE_DIR=`cd $(dirname ${BASH_SOURCE[0]}) && pwd`
OUT_DIR="$BASE_DIR"/../out/wasm

mkdir -p "$OUT_DIR"
cd "$OUT_DIR"
cmake -DCMAKE_TOOLCHAIN_FILE="$EMSDK"/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake \
     -DCMAKE_BUILD_TYPE=Debug \
     -G "Unix Makefiles" \
     "$BASE_DIR"/..
cmake --build . --target game
cd -