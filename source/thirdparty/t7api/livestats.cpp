#include "thirdparty/t7api/t7api.h"

ulong (__fastcall* t7api::livestats::core::getddlrootstate)(int) = 
    reinterpret_cast<ulong(__fastcall*)(int)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF7737B9760 - 0x7FF771910000));

ulong (__fastcall* t7api::livestats::core::getddlcontext)(ulong, int) = 
    reinterpret_cast<ulong(__fastcall*)(ulong, int)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF7737B96F0 - 0x7FF771910000));

ulong (__fastcall* t7api::livestats::getintzombiestatbykey)(uint, const char*, ulong*) = 
    reinterpret_cast<ulong(__fastcall*)(uint, const char*, ulong*)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF7737ADDE0 - 0x7FF771910000));