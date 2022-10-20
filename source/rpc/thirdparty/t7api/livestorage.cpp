#include "thirdparty/t7api/t7api.h"

ulong (__fastcall* t7api::livestorage::getstatsbufferwithcaller)(ulong, const char*, const char*, int, uint, uint) = 
    reinterpret_cast<ulong (__fastcall*)(ulong, const char*, const char*, int, uint, uint)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF7737CEF00 - 0x7FF771910000));