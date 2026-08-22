#include "include/render.h"

#include <string>

#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_iostream.h"

namespace rsdl{

void* readShaderFile(const char* shaderFile, size_t& shaderFileSize){
    std::string fullPath = "./resources/shaders/" + std::string(shaderFile) + ".spv";
    return SDL_LoadFile(fullPath.c_str(), &shaderFileSize);
}
SDL_GPUShader* createSingleGPUShader(const void* contentPtr, size_t fileSize, SDL_GPUShaderStage stage){
    SDL_GPUShaderCreateInfo shaderInfo = {
        .code_size = fileSize,
        .code = static_cast<const Uint8*>(contentPtr),
        .entrypoint = "main",
        .format = SDL_GPU_SHADERFORMAT_SPIRV,
        .stage = stage,
        .num_samplers = 0,
        .num_storage_textures = 0,
        .num_storage_buffers = 0,
        .num_uniform_buffers = 0,
        .props = 0,
    };
    return SDL_CreateGPUShader(gpuDevice, &shaderInfo);
}

Shader loadShader(const char* vertFile, const char* fragFile){
    if (gpuDevice == nullptr) return {};

    // === VERTICAL SHADER ===
    size_t vsFileSize = 0;
    auto vsContentPtr = readShaderFile(vertFile, vsFileSize);
    if(vsContentPtr == nullptr) {
        return {};
    }

    SDL_GPUShader* vertShader = createSingleGPUShader(vsContentPtr, vsFileSize, SDL_GPU_SHADERSTAGE_VERTEX);
    if(vertShader == nullptr) return{};

    // === FRAGMENT SHADER ===
    size_t fsFileSize = 0;
    auto fsContentPtr = readShaderFile(fragFile, fsFileSize);
    if(fsContentPtr == nullptr) {
        SDL_free(vsContentPtr);
        SDL_ReleaseGPUShader(gpuDevice, vertShader);
        return {};
    }

    SDL_GPUShader* fragShader = createSingleGPUShader(fsContentPtr, fsFileSize, SDL_GPU_SHADERSTAGE_FRAGMENT);

    SDL_free(vsContentPtr);
    SDL_free(fsContentPtr);

    if(fragShader == nullptr){
        SDL_ReleaseGPUShader(gpuDevice, vertShader);
        return{};
    }

    return Shader{ vertShader, fragShader };
}

}
