#pragma once

#ifndef WRAPPER
    #ifdef _WIN32
        #ifdef BUILD_RSDL_DLL
            #define WRAPPER __declspec(dllexport)
        #elif defined(USE_RSDL_DLL)
            #define WRAPPER __declspec(dllimport)
        #else
            #define WRAPPER
        #endif
    #else
        #define WRAPPER
    #endif
#endif


inline struct SDL_Window*    window     = nullptr;
inline struct SDL_GPUDevice* gpuDevice = nullptr;

struct SDL_GPUCommandBuffer;
struct SDL_GPURenderPass;
struct SDL_GPUTexture;
union SDL_Event;
struct SDL_GPUShader;


struct Shader{
    SDL_GPUShader* vert;
    SDL_GPUShader* frag;
};
struct Color{
    unsigned char r, g, b, a;
};
namespace rsdl{
inline constexpr Color DARKGRAY = { 33, 37, 41, 255 };
inline constexpr Color WHITE    = { 245, 245, 245, 255 };
inline constexpr Color RED      = { 230, 41, 55, 255 };
inline constexpr Color BLANK    = { 0, 0, 0, 0 };
}

enum CfgFlags{
    FLAG_VSYNC_HINT         = 1 << 0,
    FLAG_WINDOW_RESIZABLE   = 1 << 1,
};
namespace rsdl{
enum class LogLvl{
    Info,
    Warn,
    Err
};
using LogHook = void (*)(const char*, LogLvl);
}