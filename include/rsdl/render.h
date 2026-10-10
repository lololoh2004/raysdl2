#pragma once

#include "rsdl/common/export_macro.h"
#include "rsdl/common/structs.h"
#include <stddef.h>
#include <stdbool.h>


EXPORT_MACRO void initDraw(void);
EXPORT_MACRO void beginDraw(void);
EXPORT_MACRO void endDraw(void);

EXPORT_MACRO void setBgColor(clr bgColor);
EXPORT_MACRO void drawRectangle(int posX, int posY, int width, int height, clr color);
EXPORT_MACRO void drawCircle   (int centerX, int centerY, float radius, clr color);


EXPORT_MACRO shader loadShadersStr(const char* vertStr, size_t vertSize, const char* fragStr, size_t fragSize);
EXPORT_MACRO bool loadShadersPath(const char* vertFilePath, const char* fragFilePath, shader* outShader);
