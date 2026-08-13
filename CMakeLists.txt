cmake_minimum_required(VERSION 4.1)
project(raysdl2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")

option(IMGUI_RSDL_BACKEND "Build rsdl framework with Dear ImGui support" ON)

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
        src/rsdl.hpp
        src/window.cpp
        src/draw.cpp
        src/log.cpp
        src/math.cpp
        src/utils.cpp
        src/color.cpp
        # imgui (bridge and backend)
        src/imgui/bridge.cpp
        src/imgui/imgui_impl_sdl3.cpp
        src/imgui/imgui_impl_sdlgpu3.cpp
        # imgui
        src/imgui/imgui.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imgui_tables.cpp
        src/imgui/imgui_demo.cpp
        src/load_funcs.cpp
)

add_library(${LIB_NAME} STATIC
    ${RSDL_BASE}
)

target_include_directories(${LIB_NAME} PUBLIC src)
target_link_libraries(${LIB_NAME} PUBLIC
        SDL3-shared
        "-lstdc++exp"
)


add_executable(example example/main.cpp)
target_link_libraries(example PRIVATE ${LIB_NAME})