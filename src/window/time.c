#include "rsdl/window.h"
#include "SDL3/SDL_timer.h"


static uint64_t s_lastTime;
static uint64_t s_curTime = 0;
static double s_deltaTime = 0;
static int s_maxFPS;


void updateDeltaTime(void){
    if (s_curTime == 0){
        s_curTime = SDL_GetPerformanceCounter();
    }

    s_lastTime = s_curTime;
    s_curTime = SDL_GetPerformanceCounter();
    s_deltaTime = (double)( s_curTime - s_lastTime );
    s_deltaTime /= (double)SDL_GetPerformanceFrequency();
}

float getDeltaFloat(void){
    return (float)s_deltaTime;
}
double getDeltaDouble(void){
    return s_deltaTime;
}

void setMaxFPS(int fps){
    s_maxFPS = fps;
}
// This function is required for the frame rate limit to work
// It will freeze the frame if it was processed too quickly
void sleepBeforeNextFrame(void){
    double delta = ( double )( SDL_GetPerformanceCounter() - s_curTime );
    delta = delta / ( double )SDL_GetPerformanceFrequency() * 1000.0;

    double targetFrameTime = 1000.0 / s_maxFPS;

    if (delta < targetFrameTime){
        SDL_Delay( ( Uint32 )( targetFrameTime - delta ) );
    }
}