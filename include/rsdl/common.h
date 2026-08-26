#pragma once
#include <stddef.h>

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


extern struct SDL_Window*    window;
extern struct SDL_GPUDevice* gpuDevice;

struct SDL_GPUCommandBuffer;
struct SDL_GPURenderPass;
struct SDL_GPUTexture;
union  SDL_Event;
struct SDL_GPUShader;

typedef struct Shader {
    SDL_GPUShader* vert;
    SDL_GPUShader* frag;
} Shader;
typedef struct Color{
    unsigned char r, g, b, a;
} Color;
typedef struct Vertex{
    float x,y,z;
    float u, v;
    Color color;
} Vertex;

#define COL_DARKGRAY (Color){ 33, 37, 41, 255 }
#define COL_WHITE    (Color){ 245, 245, 245, 255 }
#define COL_RED      (Color){ 230, 41, 55, 255 }
#define COL_BLANK    (Color){ 0, 0, 0, 0 }

enum CfgFlags{
    FLAG_VSYNC_HINT         = 1 << 0,
    FLAG_WINDOW_RESIZABLE   = 1 << 1,
};