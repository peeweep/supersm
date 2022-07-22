cmake_minimum_required(VERSION 3.8)
project(supersm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER clang++)
add_executable(supersm
        src/main.cpp
        src/options.h
        src/links.h)

FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
TARGET_LINK_LIBRARIES(supersm Boost::program_options stdc++fs)
INSTALL(TARGETS supersm
        RUNTIME DESTINATION bin)
