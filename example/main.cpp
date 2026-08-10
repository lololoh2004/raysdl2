#include "rsdl.hpp"
#include "imgui/imgui.h"

#include <string>

// EXAMPLE OF USING LIB
int main(){
    rsdl::initWindow(640, 480, "DEBUG_TEST.XE");
    rsdl::setTargetFPS(60);

    rsdl::imgui::setup(true);

    while (!rsdl::windowShouldClose()){
        // std::string dt_str = std::to_string(rsdl::getRandVal(1,6));
        // rsdl::log(dt_str.c_str(), rsdl::LogLvl::Info);
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