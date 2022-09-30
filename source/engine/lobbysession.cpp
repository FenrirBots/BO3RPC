#include "engine/lobbysession.h"


namespace engine
{
    namespace lobbysession
    {
        int(__cdecl* getmaxclients)(unsigned int) = engine::address::get<int(__cdecl*)(unsigned int)>(0x7FF7737E8CB0);
        unsigned long long(__fastcall* getsession)(unsigned int) = engine::address::get<unsigned long long(__fastcall*)(unsigned int)>(0x7FF7737DDAB0);
        int(__fastcall* getclientcount)(unsigned int, unsigned int) = engine::address::get<int(__fastcall*)(unsigned int, unsigned int)>(0x7FF7737DB0C0);
    }
}