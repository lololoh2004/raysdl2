#include <stdio.h>
#include <stddef.h>

#include "rsdl/render.h"
#include "rsdl/window.h"

#include "SDL3/SDL_gpu.h"


static SDL_GPUCommandBuffer* cmdBuffer = NULL;
static SDL_GPURenderPass* currentRenderPass = NULL;
static SDL_GPUTexture* currentSwapchainTexture = NULL;
static Shader defltShader = {};
static SDL_GPUGraphicsPipeline* pipln;
static SDL_FColor clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };


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

    SDL_GPUVertexAttribute attrs[3] = {{
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

    piplnInfo.vertex_input_state = (SDL_GPUVertexInputState){
        .vertex_buffer_descriptions = &buffDesc,
        .num_vertex_buffers = 1,
        .vertex_attributes = attrs,
        .num_vertex_attributes = 3
    };

    pipln = SDL_CreateGPUGraphicsPipeline(gpuDevice, &piplnInfo);
    if (pipln == NULL) {
        printf("SDL_CreateGPUGraphicsPipeline failed: %s\n", SDL_GetError());
    }
}

void closeDraw(){
    if (pipln){
        SDL_ReleaseGPUGraphicsPipeline(gpuDevice, pipln);
        pipln = NULL;
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
    currentRenderPass = NULL;
    currentSwapchainTexture = NULL;
    if (cmdBuffer)
        SDL_WaitAndAcquireGPUSwapchainTexture(
            cmdBuffer,
            window,
            &currentSwapchainTexture,
            NULL,
            NULL);
}
void clearBG(Color c){
    clearColor = (SDL_FColor){
        (float)c.r / 255.0f,
        (float)c.g / 255.0f,
        (float)c.b / 255.0f,
        (float)c.a / 255.0f
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
        NULL
    );
}

void endDraw(){
    beginRenderPassInternal();

    if (currentRenderPass != NULL){
        SDL_EndGPURenderPass(currentRenderPass);
        currentRenderPass = NULL;
    }
    if (cmdBuffer){
        SDL_SubmitGPUCommandBuffer(cmdBuffer);
        cmdBuffer = NULL;
        currentSwapchainTexture = NULL;
    }
    if (windowShouldClose()){
        if (gpuDevice) SDL_WaitForGPUIdle(gpuDevice);
        closeDraw();
        rsdlExit();
    }
}

SDL_GPUCommandBuffer* getCurCmdBuffer()  { return cmdBuffer; }
SDL_GPURenderPass*    getCurRenderPass(){
    beginRenderPassInternal();
    return currentRenderPass;
}