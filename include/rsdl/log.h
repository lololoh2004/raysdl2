#pragma once

#include "rsdl/common/export_macro.h"

typedef void (*rsdl_logHook)(const char* text);

EXPORT_MACRO void setLogFunc(rsdl_logHook inHook);
EXPORT_MACRO void rsdl_log(const char* text);
EXPORT_MACRO void rsdl_logf(const char* format, ...);