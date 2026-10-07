#include "rsdl/window.h"
#include "rsdl/log.h"
#include "rsdl/common/structs.h"

#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"


SDL_Window* g_window = NULL;

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
    SDL_GPUDevice* gpu_device = SDL_CreateGPUDevice(formats, true, NULL);
    if (!gpu_device){
        rsdl_logf("GPU device creation failed : %s", SDL_GetError());
        SDL_DestroyWindow(g_window);
        SDL_Quit();
        return false;
    }
    rsdl_log("GPU device created");

    if (!SDL_ClaimWindowForGPUDevice(gpu_device, g_window)){
        rsdl_logf("Failed to bind GPU to window : %s", SDL_GetError());
    }
    rsdl_log("GPU bound to window");

    return true;
}
void closeWindow(void){
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    rsdl_log("Window destroyed");
}