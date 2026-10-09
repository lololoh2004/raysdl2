#include "rsdl/log.h"
#include "rsdl/render.h"
#include "SDL3/SDL_gpu.h"


static void setupShaderInfo(){

}

static void setupSingleShader(
    const char* path,
    const char* entryPoint,
    SDL_GPUShaderStage shaderStage)
{
    size_t codeSize = 0;
    void* codeContent = SDL_LoadFile(path, &codeSize);

    if (codeContent == NULL){
        rsdl_logf("Shader loading failed\n - Shader path : %s\n - SDL3 GPU error : %s", path, SDL_GetError());
        return;
    }

    SDL_GPUShaderCreateInfo shInfo = {
        .code_size = codeSize,
        .code = codeContent,
        .entrypoint = entryPoint,
        .stage = shaderStage,

        .format = SDL_GetGPUShaderFormats(g_gpuDevice),

        .num_samplers = 0,
        .num_storage_buffers = 0,
        .num_storage_textures = 0,
        .num_uniform_buffers = 0
    };

    SDL_CreateGPUShader(g_gpuDevice, &shInfo);
}

shader loadShader(const char* vertFile, const char* fragFile){
    SDL_GPUShader* vsShader;
    SDL_GPUShader* fsShader;



    SDL_GPUShaderCreateInfo* shInfo = {

    };


    SDL_CreateGPUShader(g_gpuDevice, shInfo);
}