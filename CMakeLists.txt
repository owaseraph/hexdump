cmake_minimum_required(VERSION 3.16)
project(hexdump VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Sources
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.c)

add_executable(hexdump ${SOURCES})
target_include_directories(hexdump PRIVATE ${INC_DIR})
