#pragma once

#include <cstdint>
#include "common.h"

namespace rsdl{

WRAPPER void   setRandomSeed(unsigned int inSeed);
WRAPPER int    getRandVal(int min, int max);

}