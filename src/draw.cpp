#include "include/render.h"
#include "include/imgui_bridge.h"
#include "include/window.h"

#include "SDL3/SDL_gpu.h"

namespace rsdl{

namespace{
SDL_GPUCommandBuffer* cmdBuffer = nullptr;
SDL_GPURenderPass* currentRenderPass = nullptr;
SDL_GPUTexture* currentSwapchainTexture = nullptr;

SDL_FColor clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

void beginDraw(){
    cmdBuffer = SDL_AcquireGPUCommandBuffer(gpuDevice);
    currentRenderPass = nullptr;
    currentSwapchainTexture = nullptr;
    if (cmdBuffer){
        SDL_WaitAndAcquireGPUSwapchainTexture(cmdBuffer, window, &currentSwapchainTexture, nullptr, nullptr);
    }
}
void clearBG(Color c){
    clearColor = {
        static_cast<float>(c.r) / 255.0f,
        static_cast<float>(c.g) / 255.0f,
        static_cast<float>(c.b) / 255.0f,
        static_cast<float>(c.a) / 255.0f
    };
}

void beginRenderPassInternal(){
    if (currentRenderPass ||!cmdBuffer || !currentSwapchainTexture) return;

    SDL_GPUColorTargetInfo colorInfo = {
        .texture = currentSwapchainTexture,
        .clear_color = clearColor,
        .load_op = SDL_GPU_LOADOP_CLEAR,
        .store_op = SDL_GPU_STOREOP_STORE,
    };
    currentRenderPass = SDL_BeginGPURenderPass(
        cmdBuffer,
        &colorInfo,
        1,
        nullptr
    );
}

void endDraw(){
    beginRenderPassInternal();

    if (currentRenderPass != nullptr){
        SDL_EndGPURenderPass(currentRenderPass);
        currentRenderPass = nullptr;
    }
    if (currentSwapchainTexture != nullptr && cmdBuffer) {
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
SDL_GPURenderPass*    getCurRenderPass(){
    beginRenderPassInternal();
    return currentRenderPass;
}

}