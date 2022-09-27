#pragma once
#include "Engine/EngineTypes.h"

namespace LobbySession
{
	auto GetMaxClients = GetAddress<uint64(__cdecl*)(unsigned int localClientNumber /* This could be wrong... */)>(0x7FF7737E8CB0);
}