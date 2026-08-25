#pragma once

#include "common.h"

#include <stdint.h>

WRAPPER void     fadeLambdaColor(Color* c, float alpha);
WRAPPER Color    fadeColor(Color c, float alpha);
WRAPPER uint32_t colorToInt(Color c);
WRAPPER Color    intToColor(uint32_t intC);