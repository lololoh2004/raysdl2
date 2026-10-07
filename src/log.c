#include "rsdl/log.h"

#include <stdarg.h>
#include <stdio.h>


static void defltLogHook(const char* text){
    printf("%s\n", text);
}

static rsdl_logHook curLogHook = defltLogHook;

void setLogFunc(rsdl_logHook inHook){
    if (inHook){
        curLogHook = inHook;
    } else {
        curLogHook = defltLogHook;
    }
}

void rsdl_log(const char* text){
    curLogHook(text);
}

void rsdl_logf(const char* format, ...) {
    char buffer[1024];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    curLogHook(buffer);
}