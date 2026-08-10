#pragma once
#include <cstdint>

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


namespace rsdl{

struct Color{
    unsigned char r, g, b, a;
};
enum class LogLvl{
    Info,
    Warn,
    Err
};
enum CfgFlags{
    FLAG_VSYNC_HINT         = 1 << 0,
    FLAG_WINDOW_RESIZABLE   = 1 << 1,
};


using LogHook = void (*)(const char*, LogLvl);


inline constexpr Color DARKGRAY = { 33, 37, 41, 255 };
inline constexpr Color WHITE    = { 245, 245, 245, 255 };
inline constexpr Color RED      = { 230, 41, 55, 255 };
inline constexpr Color BLANK    = { 0, 0, 0, 0 };


WRAPPER void setLogHook(LogHook hook);
WRAPPER void log(const char* msg, LogLvl lvl);

WRAPPER void initWindow(int width, int height, const char *title);

WRAPPER bool windowShouldClose();
WRAPPER void closeWindow();
WRAPPER void exit();

WRAPPER void openURL(const char* url);

WRAPPER void   setTargetFPS(int fps);
WRAPPER void   setCfgFlags(unsigned int flags);
WRAPPER void   setRandomSeed(unsigned int inSeed);

WRAPPER void hideCursor();
WRAPPER void showCursor();
WRAPPER void disableCursor();

WRAPPER float  getDeltaTime();
WRAPPER double getTime();
WRAPPER int    getFPS();
WRAPPER int    getRandVal(int min, int max);
WRAPPER unsigned int getCfgFlags();

WRAPPER SDL_GPUCommandBuffer* getCurCmdBuffer();
WRAPPER SDL_GPURenderPass*    getCurRenderPass();

WRAPPER bool IsCursorHidden();

WRAPPER void updateTimer();
WRAPPER void pollEvents();
WRAPPER void clearBG(Color c);
WRAPPER void beginDraw();
WRAPPER void endDraw();

WRAPPER void     fadeLambdaColor(Color& c, float alpha);
WRAPPER Color    fadeColor(Color c, float alpha);
WRAPPER uint32_t colorToInt(Color c);
WRAPPER Color    intToColor(uint32_t intC);

WRAPPER void drawRectangle(int posX, int posY, int width, int height, Color color);
WRAPPER void drawCircle   (int centerX, int centerY, float radius, Color color);


namespace imgui{
WRAPPER void setup(bool darkMode);
WRAPPER void pollEvents(SDL_Event& event);
WRAPPER void begin();
WRAPPER void end();
WRAPPER void doRenderPass(SDL_GPUTexture* swapchainTexture, SDL_GPUCommandBuffer* cmdBuffer);
WRAPPER void shutdown();
}



WRAPPER uint64_t getGarbage();

}
