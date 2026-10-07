#pragma once

#include "rsdl/common/export_macro.h"
#include "rsdl/common/structs.h"

// Getters
EXPORT_MACRO struct SDL_GPUCommandBuffer* getCurCmdBuffer();
EXPORT_MACRO struct SDL_GPURenderPass*    getCurRenderPass();

// Load cmds.
EXPORT_MACRO shader loadShader(const char* vertFile, const char* fragFile);

// State
EXPORT_MACRO void initDraw();
EXPORT_MACRO void beginDraw();
EXPORT_MACRO void endDraw();

// Small commands
EXPORT_MACRO void setBgColor(clr bgColor);
// Primitives
EXPORT_MACRO void drawRectangle(int posX, int posY, int width, int height, clr color);
EXPORT_MACRO void drawCircle   (int centerX, int centerY, float radius, clr color);