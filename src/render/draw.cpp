#include "../include/render.h"
#include "../include/imgui_bridge.h"
#include "../include/window.h"
#include "include/all_utils.h"

#include "SDL3/SDL_gpu.h"

namespace rsdl{
namespace{
SDL_GPUCommandBuffer* cmdBuffer = nullptr;
SDL_GPURenderPass* currentRenderPass = nullptr;
SDL_GPUTexture* currentSwapchainTexture = nullptr;
Shader defltShader = {};

SDL_GPUGraphicsPipeline* pipln;

SDL_FColor clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

void initDraw(){
    SDL_GPUColorTargetDescription colorDesc = {
        .format = SDL_GetGPUSwapchainTextureFormat(gpuDevice, window)
    };

    defltShader = loadShader("base_vs", "base_fs");
    SDL_GPUGraphicsPipelineCreateInfo piplnInfo ={
        .vertex_shader = defltShader.vert,
        .fragment_shader = defltShader.frag,
        .primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
        .target_info = {
            .color_target_descriptions = &colorDesc,
            .num_color_targets = 1,
        }
    };

    SDL_GPUVertexBufferDescription buffDesc = {
        .slot = 0,
        .pitch = sizeof(Vertex),
        .input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
        .instance_step_rate = 0,
    };

    SDL_GPUVertexAttribute attrs[3]{{
        .location = 0,
        .buffer_slot = 0,
        .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
        .offset = offsetof(Vertex, x)
    },{
        .location = 1,
        .buffer_slot = 0,
        .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
        .offset = offsetof(Vertex, u)
    },{
        .location = 2,
        .buffer_slot = 0,
        .format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
        .offset = offsetof(Vertex, color.r)
    }
    };

    piplnInfo.vertex_input_state = {
        .vertex_buffer_descriptions = &buffDesc,
        .num_vertex_buffers = 1,
        .vertex_attributes = attrs,
        .num_vertex_attributes = 3
    };

    pipln = SDL_CreateGPUGraphicsPipeline(gpuDevice, &piplnInfo);
    if (pipln == nullptr) {
        log("Poshel Nahui", LogLvl::Err);
    }
}

void closeDraw(){
    if (pipln){
        SDL_ReleaseGPUGraphicsPipeline(gpuDevice, pipln);
        pipln = nullptr;
    }
    if (defltShader.vert){
        SDL_ReleaseGPUShader(gpuDevice, defltShader.vert);
    }
    if (defltShader.frag){
        SDL_ReleaseGPUShader(gpuDevice, defltShader.frag);
    }
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
        closeDraw();
        exit();
    }
}

SDL_GPUCommandBuffer* getCurCmdBuffer()  { return cmdBuffer; }
SDL_GPURenderPass*    getCurRenderPass(){
    beginRenderPassInternal();
    return currentRenderPass;
}
}