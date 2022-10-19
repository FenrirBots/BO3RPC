#include "thirdparty/t7api/t7api.h"

ulong (__cdecl* t7api::g::getmatchstate)() =
    reinterpret_cast<ulong(__cdecl*)()>(reinterpret_cast<unsigned long long>(GetModuleHandle(0)) + (0x7FF7732DA380 - 0x7FF771910000));