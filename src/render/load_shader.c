#include "rsdl/log.h"
#include "rsdl/render.h"
#include "SDL3/SDL_gpu.h"
#include "rsdl/common/default_shaders_content.h"

#define FS_ENTRY_POINT "FSMain"
#define VS_ENTRY_POINT "VSMain"


typedef struct SDLShaderWrapper {
    SDL_GPUShaderStage stage;
    const char*    content;
    size_t         size;
    SDL_GPUShader* sdlShader;
} SDLShaderWrapper;


static void processShader(SDLShaderWrapper* shaderWrap){
    const char* entryPoint =
         shaderWrap->stage == SDL_GPU_SHADERSTAGE_VERTEX
         ? VS_ENTRY_POINT
         : FS_ENTRY_POINT;
    SDL_GPUShaderCreateInfo shInfo = {
        .code_size = shaderWrap->size,
        .code = (const Uint8*) shaderWrap->content,
        .entrypoint = entryPoint,
        .stage = shaderWrap->stage,

        .format = SDL_GetGPUShaderFormats(g_gpuDevice),

        .num_samplers = 0,
        .num_storage_buffers = 0,
        .num_storage_textures = 0,
        .num_uniform_buffers = 0
    };
    shaderWrap->sdlShader = SDL_CreateGPUShader(g_gpuDevice, &shInfo);
    if (shaderWrap->sdlShader == NULL) {
        rsdl_logf(
            "Shader compilation failed. Details : \n - SDL_Error : %s",
            SDL_GetError()
        );
    }
}

shader loadShadersStr(const char* vertStr, size_t vertSize, const char* fragStr, size_t fragSize){
    const char* finalVertStr = vertStr
        ? vertStr
        : DEFAULT_VERT_SHADER;

    SDLShaderWrapper vertShader = {
        .stage = SDL_GPU_SHADERSTAGE_VERTEX,
        .content = finalVertStr,
        .size = vertStr
            ? vertSize
            : SDL_strlen(DEFAULT_VERT_SHADER),
    };
    processShader(&vertShader);

    const char* finalFragStr = fragStr ? fragStr : DEFAULT_FRAG_SHADER;
    SDLShaderWrapper fragShader = {
        .stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
        .content = finalFragStr,
        .size = fragStr
            ? fragSize
            : SDL_strlen(DEFAULT_FRAG_SHADER),
    };
    processShader(&fragShader);

    return (shader){ vertShader.sdlShader, fragShader.sdlShader };
}

bool loadShadersPath(const char* vertFilePath, const char* fragFilePath, shader* outShader){
    size_t vertSize = 0;
    char* vertContent = SDL_LoadFile(vertFilePath, &vertSize);
    if (!vertContent && vertFilePath) {
        rsdl_logf("Cant read VERTEX shader file. Details : \n - %s", vertFilePath);
        return false;
    }

    size_t fragSize = 0;
    char* fragContent = SDL_LoadFile(fragFilePath, &fragSize);
    if (!fragContent && fragFilePath) {
        rsdl_logf("Cant read FRAGMENT shader file. Details : \n - path : %s", fragFilePath);
        SDL_free(vertContent);
        return false;
    }

    *outShader = loadShadersStr(vertContent, vertSize, fragContent, fragSize);

    SDL_free(vertContent);
    SDL_free(fragContent);

    return true;
}

void destroyShaders(shader* inShader){
    if (inShader == NULL) return;

    if (inShader->vert != NULL){
        SDL_ReleaseGPUShader(g_gpuDevice, inShader->vert);
        inShader->vert = NULL;
    }
    if (inShader->frag != NULL){
        SDL_ReleaseGPUShader(g_gpuDevice, inShader->frag);
        inShader->frag = NULL;
    }
}