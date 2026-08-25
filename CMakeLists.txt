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
include(FetchContent)
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
)
set(SDL_SHARED ON  CACHE BOOL "Build shared SDL library" FORCE)
set(SDL_STATIC OFF CACHE BOOL "Build static SDL library" FORCE)
set(SDL_TESTS  OFF CACHE BOOL "Disable SDL tests"        FORCE)
FetchContent_MakeAvailable(SDL3)


# ==== RaylibSDL ====
set(RSDL_BASE
        # Base
        include/rsdl.h
        src/window.c
        src/render/draw.c
        src/render/loaders.c
        src/math.c
        src/utils.c
        src/color.c
)

add_library(${LIB_NAME} STATIC
    ${RSDL_BASE}
)

target_include_directories(${LIB_NAME} PUBLIC
        src
        include
)
target_link_libraries(${LIB_NAME} PUBLIC
        SDL3-shared
)


add_executable(example example/main.cpp)
target_link_libraries(example PRIVATE ${LIB_NAME})