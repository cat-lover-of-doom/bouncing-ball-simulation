#===============================================================================
# Raylearner - Physics Simulation with Raylib
#===============================================================================
# A real-time 2D physics simulation demonstrating fixed timestep integration,
# elastic collisions, and interactive controls.
#===============================================================================

cmake_minimum_required(VERSION 3.15)

project(raylib_app
    VERSION 1.0.0
    DESCRIPTION "Real-time 2D physics simulation with Raylib"
    LANGUAGES C
)

#===============================================================================
# C Standard and Compiler Configuration
#===============================================================================

# Use modern C23 standard for constexpr and other features
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Export compile commands for clangd and other tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#===============================================================================
# Build Type Configuration
#===============================================================================

# Default to Debug build if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug or Release)" FORCE)
endif()

# Compiler flags for all builds (strict warnings)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

# Debug build: symbols, no optimization
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")

# Release build: maximum optimization, disable assertions
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")

#===============================================================================
# Source Files
#===============================================================================

set(SOURCES
    src/main.c
)

#===============================================================================
# Executable Target
#===============================================================================

add_executable(${PROJECT_NAME} ${SOURCES})

#===============================================================================
# Dependencies
#===============================================================================

# Find and link Raylib library
find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# macOS-specific frameworks required by Raylib
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
    )
endif()

#===============================================================================
# Installation (Optional)
#===============================================================================

# Install the executable to the bin directory
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Install documentation
install(FILES README.md LICENSE
    DESTINATION share/doc/${PROJECT_NAME}
)

#===============================================================================
# Build Information
#===============================================================================

message(STATUS "==========================================================")
message(STATUS "Raylearner Physics Simulation - Build Configuration")
message(STATUS "==========================================================")
message(STATUS "Version:      ${PROJECT_VERSION}")
message(STATUS "Build Type:   ${CMAKE_BUILD_TYPE}")
message(STATUS "C Standard:   C${CMAKE_C_STANDARD}")
message(STATUS "C Compiler:   ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "C Flags:      ${CMAKE_C_FLAGS}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug Flags:  ${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release Flags: ${CMAKE_C_FLAGS_RELEASE}")
endif()
message(STATUS "==========================================================")
