#pragma once

#include "common.h"

namespace rsdl::imgui{
WRAPPER void setup(bool darkMode);
WRAPPER void pollEvents(SDL_Event& event);
WRAPPER void begin();
WRAPPER void end();
WRAPPER void doRenderPass(SDL_GPUTexture* swapchainTexture, SDL_GPUCommandBuffer* cmdBuffer);
WRAPPER void shutdown();
}