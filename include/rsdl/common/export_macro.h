#pragma once


#ifndef EXPORT_MACRO
#   ifdef _WIN32
#       ifdef BUILD_RSDL_DLL
#           define EXPORT_MACRO __declspec(dllexport)
#       elif defined(USE_RSDL_DLL)
#           define EXPORT_MACRO __declspec(dllimport)
#       else
#           define EXPORT_MACRO
#       endif
#   else
#       define EXPORT_MACRO
#   endif
#endif

#ifdef __cplusplus
#   define RSDL_API extern "C" WRAPPER
#else
#   define RSDL_API WRAPPER
#endif