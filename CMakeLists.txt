cmake_minimum_required(VERSION 3.27)

set(
    TARGET
    project
)

project(${TARGET} C)

set(
    SOURCES
    src/main.c
)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Werror")

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g -Werror -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
add_executable(${TARGET} ${SOURCES})
set(CMAKE_C_STANDARD 17)