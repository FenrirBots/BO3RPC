#include "Engine/LobbySession.h"

int(__cdecl* LobbySession::GetMaxClients)(unsigned int) = GetAddress<int(__cdecl*)(unsigned int localClientNumber /* This could be wrong... */)>(0x7FF7737E8CB0);
int(__fastcall* LobbySession::GetClientCount)(unsigned int, unsigned int) = [](unsigned int u1, unsigned int u2)->int {
	static auto GetClientCount = GetAddress<int(__fastcall*)(unsigned int, unsigned int)>(0x7FF7737DB0C0);
	int count = GetClientCount(u1, u2);

	if (count < 0)
	{
		count = 1;
	}

	return count;
}