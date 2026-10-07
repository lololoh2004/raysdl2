#pragma once

#include "rsdl.h"

#define RAYWHITE CLR_WHITE


inline void InitWindow(int width, int height, const char* title) {
    initWindow(width, height, title);
}
inline void CloseWindow() {
    closeWindow();
}
inline bool WindowShouldClose(){
    checkEvents();
    return !isWindowOpen();
}
inline void BeginDrawing(){
    beginDraw();
}
inline void ClearBackground(clr bgClr){
    setBgColor(bgClr);
}
inline void EndDrawing(){
    endDraw();
}