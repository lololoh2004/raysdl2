#pragma once


extern struct SDL_Window*    g_window;
extern struct SDL_GPUDevice* g_gpuDevice;


struct SDL_GPUCommandBuffer;
struct SDL_GPURenderPass;
struct SDL_GPUTexture;
union  SDL_Event;
struct SDL_GPUShader;


typedef struct Shader {
    struct SDL_GPUShader* vert;
    struct SDL_GPUShader* frag;
} Shader;
typedef struct Color{
    unsigned char r, g, b, a;
} Color;
typedef struct Vertex{
    float x,y,z;
    float u, v;
    Color color;
} Vertex;