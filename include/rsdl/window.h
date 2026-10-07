#pragma once

#include "rsdl/common/export_macro.h"
#include <stdbool.h>


EXPORT_MACRO bool initWindow(int width, int height, const char* title);
EXPORT_MACRO void closeWindow(void);