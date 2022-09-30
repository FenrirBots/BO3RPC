#pragma once

namespace engine
{
    namespace ddl
    {
	    extern bool(__fastcall* movetoname)(unsigned long long*, unsigned long long*, const char*);
	    extern unsigned int(__fastcall* getuint)(unsigned long long*, unsigned long long*);
    }
}