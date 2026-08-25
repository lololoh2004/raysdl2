#include "rsdl/color.h"

#include "SDL3/SDL_pixels.h"

// Future me please fix this shit
#define CLAMP(val, min, max) ((val) < (min) ? (min) : ((val) > (max) ? (max) : (val)))

void fadeLambdaColor(Color* c, float alpha){
    if (!c) return;
    alpha = CLAMP(alpha, 0.0f, 1.0f);
    c->a = (unsigned char)(alpha * 255.0f);
}
Color fadeColor(Color c, float alpha){
    fadeLambdaColor(&c, alpha);
    return c;
}
uint32_t colorToInt(Color c){
    static const SDL_PixelFormatDetails* pixelFormatDetails = NULL;

    if (pixelFormatDetails == NULL)
        pixelFormatDetails = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);

    return SDL_MapRGBA(pixelFormatDetails, NULL, c.r, c.g, c.b, c.a);
}
Color intToColor(uint32_t intC){
    static const SDL_PixelFormatDetails* pixelFormatDetails = NULL;

    if (pixelFormatDetails == NULL)
        pixelFormatDetails = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);

    Color color = {};
    SDL_GetRGBA(intC, pixelFormatDetails, NULL, &color.r, &color.g, &color.b, &color.a);
    return color;
}
