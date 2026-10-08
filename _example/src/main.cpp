#include "rsdl_raylib_wrap.h"
#include <cstdio>

// EXAMPLE OF USING LIB
int main(){
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib example - draw square");
    SetTargetFPS(60);
    //
    while (!WindowShouldClose()){
        BeginDrawing();
        // printf(" - dt : %f\n", getDeltaFloat());
        ClearBackground(RAYWHITE);
        //     DrawRectangle(350, 175, 100, 100, RED);
        EndDrawing();
    }
    //
    CloseWindow();

    // Rickroll
    // openURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    return 0;
}