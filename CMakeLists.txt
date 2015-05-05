cmake_minimum_required(VERSION 3.0)

project(wandler)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(Qt4 REQUIRED)
#find_package(FFmpeg REQUIRED)
if(WIN32)
    set(FFMPEG_EXE_NAME ffmpeg.exe)
else(WIN32)
    set(FFMPEG_EXE_NAME ffmpeg)
endif(WIN32)

find_program (FFMPEG_EXE ${FFMPEG_EXE_NAME})
if(FFMPEG_EXE)
    message(STATUS "Found FFmpeg: ${FFMPEG_EXE}")
    add_definitions(-DFFMPEG_EXE=${FFMPEG_EXE})
else(FFMPEG_EXE)
    message(STATUS "Could not find FFmpeg. Using shipped version!")
    add_definitions(-DFFMPEG_EXE=../contrib/${FFMPEG_EXE_NAME})
endif(FFMPEG_EXE)

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)
