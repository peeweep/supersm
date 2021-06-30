cmake_minimum_required(VERSION 3.8)
project(supersm)

set(CMAKE_CXX_STANDARD 11)
add_executable(supersm
        src/main.cpp
        src/options.h
        src/links.h)

FIND_PACKAGE(Boost COMPONENTS program_options filesystem REQUIRED)
TARGET_LINK_LIBRARIES(supersm Boost::program_options Boost::filesystem)
INSTALL(TARGETS supersm
        RUNTIME DESTINATION bin)
