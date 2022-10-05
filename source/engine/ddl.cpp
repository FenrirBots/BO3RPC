#include "ddl.h"
#include "engine/enginetypes.h"


namespace engine
{
    namespace ddl
    {
	    bool(__fastcall* movetoname)(unsigned long long*, unsigned long long*, const char*) = engine::address::get<bool(__fastcall*)(unsigned long long*, unsigned long long*, const char*)>(0x7FF773E33020);
	    unsigned int(__fastcall* getuint)(unsigned long long*, unsigned long long*) = engine::address::get<unsigned int(__fastcall*)(unsigned long long*, unsigned long long*)>(0x7FF773E32AF0);
        bool(__cdecl* movetoindex)(unsigned long long*, unsigned long long*, int) = engine::address::get<bool(__cdecl*)(unsigned long long*, unsigned long long*, int)>(0x7FF773E33010);
    }
}