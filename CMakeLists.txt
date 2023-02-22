cmake_minimum_required(VERSION 3.8)
project(supersm)

set(CMAKE_CXX_STANDARD 11)
OPTION(STATIC_LINK "static link library (boost and libc)" FALSE)
add_executable(supersm
        src/main.cpp
        src/options.h
        src/links.h
)

IF(STATIC_LINK)
  SET(Boost_USE_STATIC_LIBS ON)
ENDIF()
FIND_PACKAGE(Boost COMPONENTS program_options filesystem REQUIRED)
TARGET_LINK_LIBRARIES(supersm Boost::program_options Boost::filesystem)
IF(STATIC_LINK AND NOT APPLE)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
ENDIF ()
INSTALL(TARGETS supersm
        RUNTIME DESTINATION bin)
