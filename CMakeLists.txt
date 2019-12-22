cmake_minimum_required(VERSION 3.5)
project(SuperSM)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_C_COMPILER "/usr/bin/clang")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_executable(SuperSM
        src/main.cpp
        src/common.h
        src/file.h)

# boost/program_options
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(SuperSM ${Boost_LIBRARIES})
