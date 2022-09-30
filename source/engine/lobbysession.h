#pragma once
#include "engine/enginetypes.h"


namespace engine
{
    namespace lobbysession
    {
        extern int(__cdecl* getmaxclients)(unsigned int);
        extern unsigned long long(__fastcall* getsession)(unsigned int);
        extern int(__fastcall* getclientcount)(unsigned int, unsigned int);
    }
}