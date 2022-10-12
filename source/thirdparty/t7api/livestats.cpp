#include "thirdparty/t7api/t7api.h"

ulong (__fastcall* t7api::livestats::getintzombiestatbykey)(ulong, ulong, ulong) = 
    reinterpret_cast<ulong(__fastcall*)(ulong, ulong, ulong)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF7737ADDE0 - 0x7FF771910000));