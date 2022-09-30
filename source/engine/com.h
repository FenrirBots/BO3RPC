#pragma once


namespace engine
{
    namespace com
    {
	    extern bool(__cdecl* isingame)();
    	extern bool(__fastcall* ismode)(int);

	    namespace sessionmode
	    {
	    	extern unsigned long long(__cdecl* getmode)();
	    }
    }
}