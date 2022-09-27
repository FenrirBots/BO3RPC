#include "Engine/LobbySession.h"

int(__cdecl* LobbySession::GetMaxClients)(unsigned int) = GetAddress<int(__cdecl*)(unsigned int localClientNumber /* This could be wrong... */)>(0x7FF7737E8CB0);