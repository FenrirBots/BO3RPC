#include "discord/discord.h"
#include "engine/engine.h"
#include "config.h"

#define APPLICATION_ID "1023037909848297522"

std::atomic<bool> Discord::Clear = false;
std::atomic<bool> Discord::Update = false;
std::atomic<bool> Discord::Running = true;
MultiThreadedPresence Discord::RichPresence = { };

DWORD WINAPI Discord::Loop(LPVOID /*lpvReserved*/)
{
	DiscordEventHandlers EventHandlers;
	Discord_Initialize(APPLICATION_ID, &EventHandlers, 0, 0);

	// Having a boolean here is useless as of now as we cannot detach from the target process without breaking the game.
	while (Discord::Running)
	{
		if (Discord::Clear)
		{
			Discord::Clear = false;
			Discord_ClearPresence();
		}

		else if (Discord::Update)
		{

			// Do not call engine functions here...

			// This is really expensive performance wise to update, so there has to be alot of checks before we do update.
			Discord_UpdatePresence(&Discord::RichPresence.Presence);
			Discord::Update = false;
		}
	}

	Discord_Shutdown();
	return 1;
}

void Discord::UpdatePresence()
{
	if (!Discord::Update)
	{
		Discord::RichPresence.lock();
		auto LobbyMode = *(int*)(LobbySession::GetSession(1) + 0x8);
		

		Discord::RichPresence.unlock();
	}
}