#pragma once

#include "common.h"

namespace rsdl{

// Log utils
WRAPPER void setLogHook(LogHook hook);
WRAPPER void log(const char* msg, LogLvl lvl);

// Cfg tools
WRAPPER void   setTargetFPS(int fps);
WRAPPER void   setCfgFlags(unsigned int flags);
WRAPPER unsigned int getCfgFlags();

// Small utils
WRAPPER void openURL(const char* url);
WRAPPER int  getGarbage();

}