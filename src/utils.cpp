#include "rsdl.hpp"
#include "SDL3/SDL_misc.h"

namespace rsdl{

void openURL(const char* url){
    if (!url) return;
    SDL_OpenURL(url);
}
uint64_t getGarbage(){
    uint64_t garbage;
    return garbage;
}

}
