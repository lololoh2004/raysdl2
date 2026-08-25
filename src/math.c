#include "rsdl/math.h"

#include <stdint.h>

static uint32_t seed = 123456789;

void setRandomSeed(unsigned int inSeed){
    seed = (inSeed == 0) ? seed : inSeed;
}
int getRandVal(int min, int max){
    if (min == max) return min;
    if (min > max){
        int temp = min;
        min = max;
        max = temp;
    }
    uint32_t x = seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    seed = x;

    return (int)x % (max - min + 1) + min;
}