cmake_minimum_required(VERSION 3.17)
project(learn_wasm_fbs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules)

### Packages
#
#find_package(FlatBuffers MODULE REQUIRED)
#include_directories(${FLATBUFFERS_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/third_party_headers)
include_directories(${CMAKE_CURRENT_LIST_DIR})

### Generate FlatBuffers header

# Using execute_process (Generated at configure time)
execute_process(COMMAND ${CMAKE_CURRENT_LIST_DIR}/flatbuffers/gen.sh)

# To generate at build time, use FLATBUFFERS_GENERATE_C_HEADERS function in FindFlatBuffers.cmake instead.

### Global configurations

include_directories(flatbuffers/generated)

### Targets

add_subdirectory(game)
add_subdirectory(game-facade)