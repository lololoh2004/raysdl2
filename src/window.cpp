#include "rsdl.hpp"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"

namespace rsdl{

namespace{
bool running = false;

uint64_t last_time = 0;
float delta  = 0.0f;
unsigned int target_fps = 30;

unsigned int saved_flags = FLAG_WINDOW_RESIZABLE;
}


void initWindow(int width, int height, const char *title){
    log("Hello World!(print);", LogLvl::Info);
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        title,
        width, height,
        SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    if (!window){
        log(SDL_GetError(), LogLvl::Err);
        return;
    }
    gpuDevice = SDL_CreateGPUDevice(
        SDL_GPU_SHADERFORMAT_SPIRV,
        true,
        nullptr);
    if (!gpuDevice){
        log(SDL_GetError(), LogLvl::Err);
        return;
    }
    SDL_ClaimWindowForGPUDevice(gpuDevice, window);
    setCfgFlags(saved_flags);

    last_time = SDL_GetPerformanceCounter();
    running = true;
}

void pollEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        imgui::pollEvents(event);
        if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            running = false;
    }
}

void setCfgFlags(unsigned int flags){
    saved_flags = flags;

    if (!window) return;
    if (flags & FLAG_VSYNC_HINT)
        SDL_SetGPUSwapchainParameters(gpuDevice, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC);
    else
        SDL_SetGPUSwapchainParameters(gpuDevice, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_IMMEDIATE);

    if (flags & FLAG_WINDOW_RESIZABLE)
        SDL_SetWindowResizable(window, true);
    else
        SDL_SetWindowResizable(window, false);
}
unsigned int getCfgFlags(){
    return saved_flags;
}

void updateTimer(){
    uint64_t current_time = SDL_GetPerformanceCounter();
    if (target_fps > 0){
        float target_frame_time = 1.0f / target_fps;
        float real_delta = static_cast<float>(current_time - last_time) / static_cast<float>(SDL_GetPerformanceFrequency());

        if (real_delta < target_frame_time){
            float time_to_wait = (target_frame_time - real_delta) * 1000.0f;
            SDL_Delay(static_cast<uint32_t>(time_to_wait));
        }
        current_time = SDL_GetPerformanceCounter();
    }

    delta = static_cast<float>(current_time - last_time) / static_cast<float>(SDL_GetPerformanceFrequency());
    last_time = current_time;
}
float getDeltaTime(){ return delta; }
int getFPS(){
    return delta > 0.000001f ? static_cast<int>(1.0f / delta) : 9999;
}
void setTargetFPS(int fps){
    target_fps = fps;
}
double getTime() { return static_cast<double>(SDL_GetTicks()) / 1000.0; }

void hideCursor() { SDL_HideCursor(); }
void showCursor() { SDL_ShowCursor(); }
void disableCursor(){
    if (window)
        SDL_SetWindowRelativeMouseMode(window, true);
}
bool IsCursorHidden(){ return !SDL_CursorVisible(); }

bool windowShouldClose(){
    updateTimer();
    pollEvents();
    return !running;
}
void closeWindow() { running = false; }
void exit(){
    imgui::shutdown();

    if (gpuDevice){
        SDL_DestroyGPUDevice(gpuDevice);
        gpuDevice = nullptr;
    }
    if (window){
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

}
