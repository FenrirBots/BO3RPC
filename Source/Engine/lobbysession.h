#pragma once
#include "Engine/EngineTypes.h"

namespace LobbySession
{
	extern uint64(__fastcall* GetSession)(unsigned int);
	extern int(__cdecl* GetMaxClients)(unsigned int);
	extern int(__fastcall* GetClientCount)(unsigned int, unsigned int);
}
