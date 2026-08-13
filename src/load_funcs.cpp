#include "rsdl.hpp"
#include "SDL3/SDL_gpu.h"
#include "SDL3/SDL_iostream.h"

namespace rsdl{

void* loadSingleShader(const char* file, size_t& outSize){
    return SDL_LoadFile(file, &outSize);
}
Shader loadShader(const char* vertFile, const char* fragFile){
    size_t vsSize = 0;
    auto vsContent = loadSingleShader(vertFile, vsSize);
    // i will use default shader here
    if(!vsContent) {
        log("Fragment shader not found, default will be used", LogLvl::Warn);
        //loadDefaultShader
    }
    SDL_GPUShaderCreateInfo vsInfo = {
        .code_size = vsSize,
        .code = static_cast<const Uint8*>(vsContent),
        .entrypoint = "main",
        .format = SDL_GPU_SHADERFORMAT_SPIRV,
        .stage = SDL_GPU_SHADERSTAGE_VERTEX
    };
    SDL_GPUShader* vShader = SDL_CreateGPUShader(gpuDevice, &vsInfo);

    size_t fsSize = 0;
    auto fsContent = loadSingleShader(fragFile, fsSize);
    if(!fsContent) {
        log("No fragment shader found", LogLvl::Err);
        return {};
    }
    SDL_GPUShaderCreateInfo fsInfo = {
        .code_size = fsSize,
        .code = static_cast<const Uint8*>(fsContent),
        .entrypoint = "main",
        .format = SDL_GPU_SHADERFORMAT_SPIRV,
        .stage = SDL_GPU_SHADERSTAGE_FRAGMENT
    };
    SDL_GPUShader* fShader = SDL_CreateGPUShader(gpuDevice, &fsInfo);

    Shader final_shader = {vShader, fShader};
    SDL_free(vsContent);
    SDL_free(fsContent);
    return final_shader;
}

}