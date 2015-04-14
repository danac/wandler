cmake_minimum_required(VERSION 3.0)

project(converter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(Qt4 REQUIRED)
find_package(FFmpeg REQUIRED)

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)
