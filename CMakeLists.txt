cmake_minimum_required(VERSION 4.1)
project(raysdl2 C CXX)
include(FetchContent)

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

set(SDL3_DIR "${CMAKE_SOURCE_DIR}/_lib/SDL3")
if(NOT EXISTS "${SDL3_DIR}/CMakeLists.txt")
    FetchContent_Declare(
            SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG main
            SOURCE_DIR "${SDL3_DIR}"
    )
else()
    FetchContent_Declare(
            SDL3
            SOURCE_DIR "${SDL3_DIR}"
            DOWNLOAD_COMMAND ""
            UPDATE_COMMAND ""
    )
endif()
FetchContent_MakeAvailable(SDL3)


# ==== ImGUI lib ====
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/_lib/imgui")
if(NOT EXISTS "${IMGUI_DIR}/CMakeLists.txt")
    FetchContent_Declare(
            imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui.git
            GIT_TAG        docking
            SOURCE_DIR     "${IMGUI_DIR}"
    )
else()
    FetchContent_Declare(
            imgui
            SOURCE_DIR       "${IMGUI_DIR}"
            DOWNLOAD_COMMAND ""
            UPDATE_COMMAND   ""
    )
endif()
FetchContent_MakeAvailable(imgui)

set(IMGUI_INCLUDE_DIRS
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)


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
    ${RSDL_BASE})

target_include_directories(${LIB_NAME} PUBLIC
        src
        include
)
target_link_libraries(${LIB_NAME} PUBLIC
        SDL3-shared)


# ==== Imgui Bridge (WRANING ITS ON CXX NOT C) ====
add_library(imgui_bridge STATIC
        # My bridge
        _imgui_bridge/rsdl_imgui_bridge.cpp
        _imgui_bridge/rsdl_imgui_bridge.h

        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp

        ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdlgpu3.cpp
)
target_include_directories(imgui_bridge PRIVATE
        ${IMGUI_INCLUDE_DIRS}
)
target_link_libraries(imgui_bridge PUBLIC
        ${LIB_NAME}
)



# ==== Example ====
add_executable(example _example/src/main.cpp)
#target_link_libraries(example PRIVATE ${LIB_NAME})
target_link_libraries(example PRIVATE imgui_bridge)