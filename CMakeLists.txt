cmake_minimum_required(VERSION 4.1)
project(raysdl2 C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")

set(LIB_NAME "rsdl")


# ==== SDL DLL ====
set(SDL_SHARED  ON  CACHE BOOL "Build shared SDL library" FORCE)
set(SDL_STATIC  OFF CACHE BOOL "Build static SDL library" FORCE)
set(SDL_TESTS   OFF CACHE BOOL "Disable SDL tests"        FORCE)

add_subdirectory(lib/SDL3)


set(SDLSHADERCROSS_CLI      OFF CACHE BOOL "Disable shadercross CLI tool" FORCE)
set(SDLSHADERCROSS_VENDORED ON  CACHE BOOL "Use vendored dependencies"    FORCE)
set(SDLSHADERCROSS_DXC      OFF CACHE BOOL "Disable DXC support"          FORCE)

add_subdirectory(lib/SDL3_shadercross)


# ==== RaylibSDL ====
set(RSDL_BASE
        # Base
        include/rsdl.h
        src/render/draw.c
        src/render/loaders.c
        include/rsdl/window.h
        src/window/base.c
        include/rsdl_raylib_wrap.h
        include/rsdl/common/structs.h
        include/rsdl/common/enums.h
        include/rsdl/common/export_macro.h
        include/rsdl/log.h
        src/log.c
        src/window/time.cpp
        # UNSORTED
)

add_library(${LIB_NAME} STATIC
    ${RSDL_BASE})

target_include_directories(${LIB_NAME} PUBLIC
        src
        include
)
target_link_libraries(${LIB_NAME} PUBLIC
        SDL3::SDL3-shared
        SDL3_shadercross::SDL3_shadercross
)



# ==== Example ====
add_executable(example _example/src/main.cpp)
target_link_libraries(example PRIVATE rsdl)