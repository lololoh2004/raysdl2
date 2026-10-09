#include "rsdl_raylib_wrap.h"
#include <cstdio>

// EXAMPLE OF USING LIB
int main(){
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    // SETUP
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib-like example");
    SetTargetFPS(60);

    // TraceLog(LOG_INFO, "eee raylib print");
    // Vector2 pos = { 400.0f, 225.0f };

    // LOOP
    while (!WindowShouldClose()){
        // TIME CHECK
        float dt = GetFrameTime();
        // double time = GetTime();
        // int fps = GetFPS();
        //
        // int width = GetScreenWidth();
        // int height = GetScreenHeight();

        // WINDOW RESIZE CHECK
        // if (IsWindowResized()) {
        //     TraceLog(LOG_WARNING, TextFormat("Window has changed !! New size : %dx%d", width, height));
        // }

        // INPUT ( KEYBOARD )
        // if (IsKeyPressed(KEY_SPACE)) {
        //     TraceLog(LOG_INFO, "SPACE key is holding");
        // }
        // if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        //     pos.y -= 100.0f * dt;
        // }
        // if (IsKeyReleased(KEY_ESCAPE)) {
        //     TraceLog(LOG_INFO, "ESC key detected");
        // }

        // INPUT ( MOUSE )
        // Vector2 mousePos = GetMousePosition();
        // float wheelMove = GetMouseWheelMove();
        // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        //     TraceLog(LOG_INFO, TextFormat("Mouse click in : X: %.1f, Y: %.1f", mousePos.x, mousePos.y));
        // }
        // if (wheelMove != 0.0f) {
        //     TraceLog(LOG_INFO, TextFormat("Mouse wheel has rotated : %.1f", wheelMove));
        // }

        // RANDOM
        // int randomTicket = GetRandomValue(1, 100);
        // TraceLog(LOG_DEBUG, TextFormat("Random value : %d", randomTicket));

        BeginDrawing();
        // printf(" - dt : %f\n", getDeltaFloat());
        ClearBackground(RAYWHITE);
        //     DrawRectangle(350, 175, 100, 100, RED);
        EndDrawing();
    }

    // CLOSE
    CloseWindow();

    // Rickroll
    // openURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    return 0;
}