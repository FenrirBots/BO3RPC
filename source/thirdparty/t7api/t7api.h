#pragma once
#include <Windows.h>
typedef unsigned long long ulong;
typedef unsigned int uint;

enum eModes
{
  MODE_ZOMBIES     = 0,
  MODE_MULTIPLAYER = 1,
  MODE_CAMPAIGN    = 2,
  MODE_INVALID     = 3,
};

enum LobbyMode
{
    LOBBY_MODE_PUBLIC  = 0,
    LOBBY_MODE_CUSTOM  = 1,
    LOBBY_MODE_THEATER = 2,
    LOBBY_MODE_ARENA   = 3,
    LOBBY_MODE_FREERUN = 4
};

namespace t7api
{
    namespace cg
    {
    	extern void (__fastcall* draw2d)(int);
    	extern void (__fastcall* draw2dinternal)(int);
    	extern void (__fastcall* boldgamemessagecenter)(int, const char*);
    }

    namespace com
    {
	    extern bool (__cdecl* isingame)();
    	extern bool (__fastcall* ismode)(eModes);

        namespace localclient
        {
            extern long long (__cdecl* getcontrollerindex)(int);
        }

	    namespace sessionmode
	    {
	    	extern int (__cdecl* getmode)();
	    }
    }

    namespace ddl
    {
	    extern bool (__fastcall* movetoname)(ulong*, ulong*, const char*);
	    extern uint (__fastcall* getuint)(ulong*, ulong*);
        extern bool (__cdecl* movetoindex)(ulong*, ulong*, int);
        extern bool (__fastcall* movetopath)(ulong*, ulong*, const char**);
    }

    namespace demo
    {
        extern void (__cdecl* drawdebuginformation)();
        extern bool (__cdecl* isplaying)();
        extern bool (__cdecl* ispaused)();
        extern bool (__cdecl* isplaybackinited)();
    }

    namespace livestats
    {
        extern ulong (__fastcall* getintzombiestatbykey)(ulong, ulong, ulong);
    }

    namespace livestorage
    {
        extern ulong (__fastcall* getstatsbufferwithcaller)(ulong, const char*, const char*, int, uint, uint);
    }

    namespace lobbysession
    {
        extern int (__cdecl* getmaxclients)(uint);
        extern ulong (__fastcall* getsession)(uint);
        extern int (__fastcall* ismode)(uint);
        extern int (__fastcall* getclientcount)(uint, uint);
    }
}