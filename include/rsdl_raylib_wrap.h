#pragma once

#include "rsdl.h"


inline void InitWindow(int width, int height, const char* title) {
    initWindow(width, height, title);
}
inline void CloseWindow() {
    closeWindow();
}