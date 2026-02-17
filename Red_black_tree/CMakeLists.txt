cmake_minimum_required(VERSION 3.16)
project(Red_black_tree C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit tests" OFF)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
option(ENABLE_SANITIZERS "Enable AddressSanitizer + UndefinedBehaviorSanitizer" OFF)
option(ENABLE_OPTIMIZATIONS "Enable -O2 optimizations" ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-std=c2x -Wall -Wextra -Wpedantic -g -O0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-std=c2x -Wall -Wextra -O2 -DNDEBUG)
endif()

if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

if(ENABLE_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(${PROJECT_NAME} main.c ${SOURCES})

if(BUILD_TESTS)
    enable_testing()
    find_package(CUnit REQUIRED)
    add_subdirectory(tests)
endif()

