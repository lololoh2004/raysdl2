#include "rsdl.hpp"
#include "SDL3/SDL_gpu.h"

namespace rsdl{

namespace{
SDL_GPUCommandBuffer* cmdBuffer = nullptr;
SDL_GPURenderPass* currentRenderPass = nullptr;
SDL_GPUTexture* currentSwapchainTexture = nullptr;
}

void beginDraw(){
    cmdBuffer = SDL_AcquireGPUCommandBuffer(gpuDevice);
    currentRenderPass = nullptr;
}
void clearBG(Color c){
    if (!cmdBuffer) return;

    // Uint32 width, height;
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdBuffer, window, &currentSwapchainTexture,
        nullptr, nullptr)) return;

    SDL_GPUColorTargetInfo colorInfo{};
    colorInfo.clear_color = {
        static_cast<float>(c.r) / 255.0f,
        static_cast<float>(c.g) / 255.0f,
        static_cast<float>(c.b) / 255.0f,
        static_cast<float>(c.a) / 255.0f
    };
    colorInfo.load_op = SDL_GPU_LOADOP_CLEAR;
    colorInfo.store_op = SDL_GPU_STOREOP_STORE;
    colorInfo.texture = currentSwapchainTexture;

    currentRenderPass = SDL_BeginGPURenderPass(
        cmdBuffer, &colorInfo,
        1, nullptr);
}
void drawRectangle(int posX, int posY, int width, int height, Color color){
    if (!cmdBuffer) return;
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmdBuffer, window, &currentSwapchainTexture,
        nullptr, nullptr)) return;

    SDL_GPUColorTargetInfo colorInfo{};
    colorInfo.clear_color = {
        static_cast<float>(color.r) / 255.0f,
        static_cast<float>(color.g) / 255.0f,
        static_cast<float>(color.b) / 255.0f,
    };
    colorInfo.load_op = SDL_GPU_LOADOP_LOAD;
    colorInfo.store_op = SDL_GPU_STOREOP_STORE;

    //
}
void endDraw(){
    if (currentRenderPass != nullptr){
        SDL_EndGPURenderPass(currentRenderPass);
        currentRenderPass = nullptr;
    }
    if (currentSwapchainTexture != nullptr) {
        //imgui::doRenderPass(cmdBuffer, currentSwapchainTexture);
        imgui::doRenderPass(currentSwapchainTexture, cmdBuffer);
    }
    if (cmdBuffer){
        SDL_SubmitGPUCommandBuffer(cmdBuffer);
        cmdBuffer = nullptr;
        currentSwapchainTexture = nullptr;
    }
    if (windowShouldClose()){
        if (gpuDevice) SDL_WaitForGPUIdle(gpuDevice);
        exit();
    }
}

SDL_GPUCommandBuffer* getCurCmdBuffer()  { return cmdBuffer; }
SDL_GPURenderPass*    getCurRenderPass() { return currentRenderPass; }

}