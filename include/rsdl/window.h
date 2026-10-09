#pragma once

#include "rsdl/common/export_macro.h"
#include <stdbool.h>


EXPORT_MACRO bool initWindow(int width, int height, const char* title);
EXPORT_MACRO void closeWindow (void);
EXPORT_MACRO bool isWindowOpen(void);
EXPORT_MACRO void checkEvents (void);


EXPORT_MACRO void   updateDeltaTime(void);
// EXPORT_MACRO void   updateTime(void);
EXPORT_MACRO float  getDeltaFloat(void);
EXPORT_MACRO double getDeltaDouble(void);

EXPORT_MACRO void setMaxFPS(int fps);
EXPORT_MACRO void sleepBeforeNextFrame(void);
