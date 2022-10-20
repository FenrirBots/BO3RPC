#include "thirdparty/t7api/t7api.h"

int(__cdecl* t7api::lobbysession::getmaxclients)(uint) = 
    reinterpret_cast<int(__cdecl*)(uint)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF7737E8CB0 - 0x7FF771910000));

ulong(__fastcall* t7api::lobbysession::getsession)(uint) = 
    reinterpret_cast<ulong(__fastcall*)(uint)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF7737DDAB0 - 0x7FF771910000));

int(__fastcall* t7api::lobbysession::ismode)(uint) = 
    [](uint mode)->int {
        unsigned int lobbymode = *(int*)(t7api::lobbysession::getsession(1) + 8);
        return (mode == lobbymode);
    };

int(__fastcall* t7api::lobbysession::getclientcount)(uint, uint) = 
    reinterpret_cast<int(__fastcall*)(uint, uint)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF7737DB0C0 - 0x7FF771910000));