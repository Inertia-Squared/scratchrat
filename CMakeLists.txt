cmake_minimum_required(VERSION 3.18)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

project(scratchrat C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

add_subdirectory(clip)
find_package(raylib REQUIRED)

add_executable(scratchrat scratchrat.c clip_wrapper.cpp)

# --- THE MAGIC PART ---

# Base flags for ALL builds (Warnings, etc)
target_compile_options(scratchrat PRIVATE -pedantic -W -Wall -Wextra)

# Specific flags for RelWithDebInfo ONLY (Optimized + Profilable)
# We add -fno-omit-frame-pointer ONLY when build type is RelWithDebInfo
target_compile_options(scratchrat PRIVATE
        $<$<CONFIG:RelWithDebInfo>:-fno-omit-frame-pointer>
)

# Note:
# - Debug automatically adds -O0 -g
# - Release automatically adds -O3 (and omits frame pointers, breaking perf)
# - RelWithDebInfo automatically adds -O2 -g
target_link_libraries(scratchrat PRIVATE raylib m pthread dl rt X11 clip)
target_include_directories(scratchrat PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/clip ${CMAKE_CURRENT_SOURCE_DIR})