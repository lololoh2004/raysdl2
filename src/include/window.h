#pragma once

#include "common.h"

namespace rsdl{

// Init
WRAPPER void initWindow(int width, int height, const char *title);

// Close funcs.
WRAPPER bool windowShouldClose();
WRAPPER void closeWindow();
WRAPPER void exit();

// Time funcs.
WRAPPER float  getDeltaTime();
WRAPPER double getTime();
WRAPPER int    getFPS();

// Update funcs.
WRAPPER void updateTimer();
WRAPPER void pollEvents();

// Cursor cfg
WRAPPER bool IsCursorHidden();
WRAPPER void hideCursor();
WRAPPER void showCursor();
WRAPPER void disableCursor();
}