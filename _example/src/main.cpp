#include <cstdio>
#include "rsdl.h"
#include "rsdl_raylib_wrap.h"

// EXAMPLE OF USING LIB
int main(){
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib example - draw square");
    // SetTargetFPS(60);
    //
    // while (!WindowShouldClose()){
    //     BeginDrawing();
    //
    //     ClearBackground(RAYWHITE);
    //     DrawRectangle(350, 175, 100, 100, RED);
    //
    //     EndDrawing();
    // }
    //
    CloseWindow();

    // Rickroll
    // openURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    return 0;
}