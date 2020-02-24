cmake_minimum_required(VERSION 3.8)
project(supersm)

set(CMAKE_CXX_STANDARD 11)
add_executable(supersm
        src/main.cpp
        src/common.h
        src/file.h)

set(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost COMPONENTS program_options filesystem REQUIRED)
TARGET_LINK_LIBRARIES(supersm Boost::program_options Boost::filesystem)
IF (UNIX AND NOT APPLE)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
ENDIF ()
