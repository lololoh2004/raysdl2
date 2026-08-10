#include "rsdl.hpp"

namespace{
    uint32_t seed = 123456789;
}
namespace rsdl{
    void setRandomSeed(unsigned int inSeed){
        seed = (inSeed == 0) ? seed : inSeed;
    }
    int getRandVal(int min, int max){
        if (min > max){
            int init_min = min;
            min = max;
            max = init_min;
        }
        uint32_t x = seed;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        seed = x;

        return static_cast<int>(x) % (max - min + 1) + min;
    }
}