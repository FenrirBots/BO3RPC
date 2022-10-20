#include "thirdparty/t7api/t7api.h"

const char*(__fastcall* t7api::cg::getmatchscoreboardmapname)(unsigned int) = 
    reinterpret_cast<const char*(__fastcall*)(unsigned int)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF772319BD0 - 0x7FF771910000));

void(__fastcall* t7api::cg::draw2d)(int) = 
    reinterpret_cast<void(__fastcall*)(int)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF771F1F910 - 0x7FF771910000));

void(__fastcall* t7api::cg::draw2dinternal)(int) = 
    reinterpret_cast<void(__fastcall*)(int)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF771F1F920 - 0x7FF771910000));

void(__fastcall* t7api::cg::boldgamemessagecenter)(int, const char*) = 
    reinterpret_cast<void(__fastcall*)(int, const char*)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF7721D4C80 - 0x7FF771910000));