#pragma once


namespace engine
{
    namespace com
    {
	    extern bool(__cdecl* isingame)();

	    namespace sessionmode
	    {
	    	extern bool(__fastcall* ismode)(int);
	    	extern unsigned long long(__cdecl* getmode)();
	    }
    }
}