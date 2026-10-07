#include "rsdl/render.h"
#include "rsdl/common/structs.h"
#include "rsdl/common/color_presets.h"
#include "SDL3/SDL_gpu.h"


static SDL_GPUCommandBuffer* s_cmdBuffer        = NULL;
static SDL_GPUTexture*       s_swapchainTexture = NULL;
static SDL_GPURenderPass*    renderPass         = NULL;

static clr s_bgColor = CLR_DARKGRAY;

void draw();


void beginDraw(){
    s_cmdBuffer = SDL_AcquireGPUCommandBuffer(g_gpuDevice);
    s_swapchainTexture = NULL;
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(
        s_cmdBuffer, g_window, &s_swapchainTexture,
        NULL, NULL)){
        //nah
    }
    draw();
}

void setBgColor(clr bgColor){
    s_bgColor = bgColor;
}

void draw(){
    if (!s_swapchainTexture) return;

    SDL_FColor fColor = {
        (float)s_bgColor.r / 255.0f,
        (float)s_bgColor.g / 255.0f,
        (float)s_bgColor.b / 255.0f,
        (float)s_bgColor.a / 255.0f,
    };
    SDL_GPUColorTargetInfo clrTargetInfo = {
        .texture = s_swapchainTexture,
        .clear_color = fColor,
        .load_op = SDL_GPU_LOADOP_CLEAR,
        .store_op = SDL_GPU_STOREOP_STORE,
        .cycle = false
    };

    renderPass = SDL_BeginGPURenderPass(
        s_cmdBuffer, &clrTargetInfo, 1, NULL);
}

void endDraw(){
    if (renderPass){
        SDL_EndGPURenderPass(renderPass);
        renderPass = NULL;
    }
    SDL_SubmitGPUCommandBuffer(s_cmdBuffer);
}