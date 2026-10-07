#pragma once


extern struct SDL_Window*    g_window;
extern struct SDL_GPUDevice* g_gpuDevice;


struct SDL_GPUCommandBuffer;
struct SDL_GPURenderPass;
struct SDL_GPUTexture;
union  SDL_Event;
struct SDL_GPUShader;


typedef struct shader {
    struct SDL_GPUShader* vert;
    struct SDL_GPUShader* frag;
} shader;
typedef struct Color{
    unsigned char r, g, b, a;
} clr;
typedef struct vert{
    float x,y,z;
    float u, v;
    clr color;
} vert;