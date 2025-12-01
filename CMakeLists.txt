cmake_minimum_required(VERSION 3.10)
project(AoC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
endforeach()
