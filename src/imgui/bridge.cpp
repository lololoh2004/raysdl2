#include "rsdl.hpp"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlgpu3.h"

namespace rsdl::imgui{

void setup(bool darkMode){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplSDL3_InitForSDLGPU(window);
    ImGui_ImplSDLGPU3_InitInfo init_info = {};
    init_info.Device = gpuDevice;
    init_info.ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(gpuDevice, window);

    ImGui_ImplSDLGPU3_Init(&init_info);
}
void pollEvents(SDL_Event& event){
    ImGui_ImplSDL3_ProcessEvent(&event);
}
void begin(){
    ImGui_ImplSDLGPU3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}
void end(){
    ImGui::Render();
}
void doRenderPass(SDL_GPUTexture* swapchainTexture, SDL_GPUCommandBuffer* cmdBuffer){
    ImDrawData* drawData = ImGui::GetDrawData();

    if (drawData != nullptr && cmdBuffer != nullptr){
        ImGui_ImplSDLGPU3_PrepareDrawData(drawData, cmdBuffer);

        if (swapchainTexture){
            SDL_GPUColorTargetInfo colorInfo{};
            colorInfo.texture = swapchainTexture;
            colorInfo.load_op = SDL_GPU_LOADOP_LOAD;
            colorInfo.store_op = SDL_GPU_STOREOP_STORE;

            SDL_GPURenderPass* imguiPass = SDL_BeginGPURenderPass(
                cmdBuffer,
                &colorInfo,
                1,
                nullptr);
            ImGui_ImplSDLGPU3_RenderDrawData(drawData, cmdBuffer, imguiPass);
            SDL_EndGPURenderPass(imguiPass);
        }
    }
}
void shutdown(){
    if (!gpuDevice){
        return;
    }
    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLGPU3_Shutdown();
    ImGui::DestroyContext();
}

}