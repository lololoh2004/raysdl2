#include "include/all_utils.h"

#include <iostream>
#include <format>

namespace{

void defltLog(const char* msg, rsdl::LogLvl lvl){
    auto c_lvl = [lvl] {
        switch (lvl) {
        case rsdl::LogLvl::Info: return "INFO";
        case rsdl::LogLvl::Warn: return "Warn";
        case rsdl::LogLvl::Err:  return "ERROR";
        default:                 return "UNKNOWN_LOG_LEVEL_TYPE";
        }
    }();
    std::cout << std::format("[RSDL] {} : {}\n", c_lvl, msg);
}
rsdl::LogHook current_hook = defltLog;
}

namespace rsdl{

void setLogHook(LogHook hook){
    current_hook = (hook != nullptr) ? hook : current_hook;
}
void log(const char* msg, LogLvl lvl){
#ifdef RSDL_NO_LOGS
#else
    current_hook(msg, lvl);
#endif
}

}