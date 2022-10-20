#include "thirdparty/t7api/t7api.h"

bool(__fastcall* t7api::ddl::movetoname)(ulong*, ulong*, const char*) = 
    reinterpret_cast<bool(__fastcall*)(ulong*, ulong*, const char*)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773E33020 - 0x7FF771910000));

uint(__fastcall* t7api::ddl::getuint)(ulong*, ulong*) = 
    reinterpret_cast<uint(__fastcall*)(ulong*, ulong*)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773E32AF0 - 0x7FF771910000));

bool(__cdecl* t7api::ddl::movetoindex)(ulong*, ulong*, int) = 
    reinterpret_cast<bool(__cdecl*)(ulong*, ulong*, int)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773E33010 - 0x7FF771910000));

ulong(__fastcall* t7api::ddl::getvalue)(ulong*, ulong*) = 
    reinterpret_cast<ulong(__fastcall*)(ulong*, ulong*)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773E32B70 - 0x7FF771910000));

bool(__fastcall* t7api::ddl::movetopath)(ulong*, ulong*, int, const char**) = 
    reinterpret_cast<bool(__fastcall*)(ulong*, ulong*, int, const char**)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773E33030 - 0x7FF771910000));