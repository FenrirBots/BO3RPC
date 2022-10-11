#include "thirdparty/t7api/t7api.h"

void(__cdecl* t7api::demo::drawdebuginformation)() = 
    reinterpret_cast<void(__cdecl*)()>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773F56660 - 0x7FF771910000));

bool(__cdecl* t7api::demo::isplaying)() = 
    reinterpret_cast<bool(__cdecl*)()>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773F10DD0 - 0x7FF771910000));

bool(__cdecl* t7api::demo::ispaused)() = 
    reinterpret_cast<bool(__cdecl*)()>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773F22330 - 0x7FF771910000));

bool(__cdecl* t7api::demo::isplaybackinited)() = 
    reinterpret_cast<bool(__cdecl*)()>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773F22380 - 0x7FF771910000));