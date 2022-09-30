#pragma once


namespace engine
{
    namespace cg
    {
    	extern void(__fastcall* draw2d)(int);
    	extern void(__fastcall* draw2dinternal)(int);
    	extern void(__fastcall* boldgamemessagecenter)(int, const char*);
        void draw2dhook(int);
    }
}