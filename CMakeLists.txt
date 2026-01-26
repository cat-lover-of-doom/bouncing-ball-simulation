cmake_minimum_required(VERSION 3.15)
project(raylib_app C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES
    src/main.c
)
add_executable(raylib_app ${SOURCES})

find_package(raylib REQUIRED)
target_link_libraries(raylib_app raylib)

if(APPLE)
    target_link_libraries(raylib_app "-framework CoreVideo" "-framework IOKit" "-framework Cocoa" "-framework GLUT" "-framework OpenGL")
endif()
