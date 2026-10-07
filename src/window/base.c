#include "rsdl/window.h"
#include "rsdl/log.h"
#include "rsdl/common/structs.h"

#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"


SDL_Window* g_window = NULL;
SDL_GPUDevice* g_gpuDevice = NULL;
static bool s_isWindow = false;

bool initWindow(int width, int height, const char* title){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        rsdl_logf("SDL root init. failed : %s", SDL_GetError());
        return false;
    }
    rsdl_log("SDL root initialized");

    g_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!g_window){
        rsdl_logf("Window creation failed : %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    rsdl_log("Window created");

    SDL_GPUShaderFormat formats = SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_DXIL;
    g_gpuDevice = SDL_CreateGPUDevice(formats, true, NULL);
    if (!g_gpuDevice){
        rsdl_logf("GPU device creation failed : %s", SDL_GetError());
        SDL_DestroyWindow(g_window);
        SDL_Quit();
        return false;
    }
    rsdl_log("GPU device created");

    if (!SDL_ClaimWindowForGPUDevice(g_gpuDevice, g_window)){
        rsdl_logf("Failed to bind GPU to window : %s", SDL_GetError());
    }
    rsdl_log("GPU bound to window");

    s_isWindow = true;
    return true;
}
void closeWindow(void){
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    rsdl_log("Window destroyed");
}

bool isWindowOpen(void){
    return s_isWindow;
}

void checkEvents(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            case SDL_EVENT_QUIT:
                s_isWindow = false; break;
            default: break;
        }
    }
}