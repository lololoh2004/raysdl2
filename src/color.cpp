#include "rsdl.hpp"

#include <algorithm>
#include "SDL3/SDL_pixels.h"

namespace rsdl{

void fadeLambdaColor(Color& c, float alpha){
    alpha = std::clamp(alpha, 0.0f, 1.0f);
    c.a = static_cast<unsigned char>(alpha * 255.0f);
}
Color fadeColor(Color c, float alpha){
    fadeLambdaColor(c, alpha);
    return c;
}
uint32_t colorToInt(Color c){
    static const auto* pixelFormatDetails = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
    return SDL_MapRGBA(pixelFormatDetails, nullptr,
        c.r, c.g, c.b, c.a);
}
Color intToColor(uint32_t intC){
    static const auto* pixelFormatDetails = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
    Color color{};
    SDL_GetRGBA(intC, pixelFormatDetails, nullptr,
        &color.r, &color.g, &color.b, &color.a);
    return color;
}

}
