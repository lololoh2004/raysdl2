#include "rsdl.h"

// EXAMPLE OF USING LIB
int main(){
    initWindow(640, 480, "DEBUG_TEST.XE");
    setTargetFPS(144);

    while (!windowShouldClose()){
        beginDraw();
            clearBG(COL_DARKGRAY);
        endDraw();
    }
    closeWindow();

    // Rickroll
    // openURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    return 0;
}