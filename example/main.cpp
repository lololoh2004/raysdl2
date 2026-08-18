#include "rsdl.hpp"
#include "imgui/imgui.h"

// EXAMPLE OF USING LIB
int main(){
    rsdl::initWindow(640, 480, "DEBUG_TEST.XE");
    rsdl::setTargetFPS(144);

    rsdl::imgui::setup(true);

    while (!rsdl::windowShouldClose()){
        rsdl::beginDraw();
            rsdl::clearBG(rsdl::DARKGRAY);
            rsdl::imgui::begin();
                ImGui::ShowDemoWindow();
            rsdl::imgui::end();
        rsdl::endDraw();
    }
    rsdl::imgui::shutdown();
    rsdl::closeWindow();

    // Rickroll
    // rsdl::openURL("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    return 0;
}