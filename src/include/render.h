#pragma once

#include "common.h"

namespace rsdl{

// Getters
WRAPPER SDL_GPUCommandBuffer* getCurCmdBuffer();
WRAPPER SDL_GPURenderPass*    getCurRenderPass();

// Load cmds.
WRAPPER Shader loadShader(const char* vertFile, const char* fragFile);

// State
WRAPPER void initDraw();
WRAPPER void beginDraw();
WRAPPER void endDraw();

// Small commands
WRAPPER void clearBG(Color c);
// Primitives
WRAPPER void drawRectangle(int posX, int posY, int width, int height, Color color);
WRAPPER void drawCircle   (int centerX, int centerY, float radius, Color color);

}