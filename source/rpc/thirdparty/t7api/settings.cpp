#include "thirdparty/t7api/t7api.h"

int (__fastcall* t7api::settings::getuint)(const char*, int) = 
    reinterpret_cast<int(__fastcall*)(const char*, int)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF772F5ECB0 - 0x7FF771910000));