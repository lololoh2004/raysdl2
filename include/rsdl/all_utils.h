#pragma once

#include "common.h"

// Cfg tools
WRAPPER void   setTargetFPS(int fps);
WRAPPER void   setCfgFlags(unsigned int flags);
WRAPPER unsigned int getCfgFlags();

// Small utils
WRAPPER void openURL(const char* url);
WRAPPER int  getGarbage();