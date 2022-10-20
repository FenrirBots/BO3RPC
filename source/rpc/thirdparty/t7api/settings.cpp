#include "thirdparty/t7api/t7api.h"

unsigned long long (__fastcall* t7api::settings::getuint)(const char*, unsigned long long) = 
    reinterpret_cast<unsigned long long(__fastcall*)(const char*, unsigned long long)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF772F5ECB0 - 0x7FF771910000));