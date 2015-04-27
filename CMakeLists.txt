cmake_minimum_required(VERSION 3.0)

project(converter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(Qt4 REQUIRED)
#find_package(FFmpeg REQUIRED)
if(WIN32)
    set(FFMPEG_EXE_NAME ffmpeg.exe)
else(WIN32)
    set(FFMPEG_EXE_NAME ffmpeg)
endif(WIN32)

find_program (FFMPEG_EXE ${FFMPEG_EXE_NAME} HINTS "${CMAKE_SOURCE_DIR}/contrib" REQUIRED)
if(NOT FFMPEG_EXE EQUAL FFMPEG-NOTFOUND)
    message(STATUS "Found FFmpeg: ${FFMPEG_EXE}")
    add_definitions(-DFFMPEG_EXE=${FFMPEG_EXE})
else(NOT FFMPEG_EXE EQUAL FFMPEG-NOTFOUND)
    message(FATAL_ERROR "Could not find FFmpeg!")
endif(NOT FFMPEG_EXE EQUAL FFMPEG-NOTFOUND)

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)
