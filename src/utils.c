#include "rsdl/all_utils.h"
#include "SDL3/SDL_misc.h"

void openURL(const char* url){
    if (!url) return;
    SDL_OpenURL(url);
}
int getGarbage(){
    int garbage;
    return garbage;
}