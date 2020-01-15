cmake_minimum_required(VERSION 3.8)
project(SuperSM)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_C_COMPILER "/usr/bin/clang")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_executable(SuperSM
        src/main.cpp
        src/common.h
        src/file.h)

set(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
TARGET_LINK_LIBRARIES(SuperSM Boost::program_options)
set(CMAKE_EXE_LINKER_FLAGS "-static")
