#include "thirdparty/t7api/t7api.h"

bool(__cdecl* t7api::com::isingame)() = 
    reinterpret_cast<bool(__cdecl*)()>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773A58D20 - 0x7FF771910000));

bool(__fastcall* t7api::com::ismode)(eModes) = 
    reinterpret_cast<bool(__fastcall*)(eModes)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773A07DD0 - 0x7FF771910000));

int(__cdecl* t7api::com::sessionmode::getmode)() = 
    reinterpret_cast<int(__cdecl*)()>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773A07790 - 0x7FF771910000));

ulong(__fastcall* t7api::com::localclient::getcontrollerindex)(uint) = 
    reinterpret_cast<ulong(__fastcall*)(uint)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773A00390- 0x7FF771910000));