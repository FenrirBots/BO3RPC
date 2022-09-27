#include "discord/discord.h"

DWORD WINAPI Discord::Loop(LPVOID /*lpvReserved*/)
{
	DiscordEventHandlers pEventHandlers;
	ZeroMemory(&pEventHandlers, sizeof DiscordEventHandlers);
	Discord_Initialize("1023037909848297522", &pEventHandlers, 0, 0);

	static bool bRunning = true;
	while (bRunning)
	{
		// Do not call engine functions here...
	}

	Discord_Shutdown();
	return 1;
}