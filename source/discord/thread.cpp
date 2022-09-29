#include "discord/discord.h"
#define APPLICATION_ID "1023037909848297522"

std::atomic<bool> discord::running = true;
std::atomic<bool> discord::update = false;
MultiThreadedPresence discord::presence::data;


DWORD WINAPI discord::thread(LPVOID /* lpvReserved */)
{
	ZeroMemory(&discord::presence::data.presence, sizeof(DiscordRichPresence));

	DiscordEventHandlers EventHandlers;
	ZeroMemory(&EventHandlers, sizeof(DiscordEventHandlers));


	discord::presence::initialize("", &EventHandlers, 0, 0);

	while (discord::running)
	{
		if (discord::update.load() == false)
		{
			continue;
		}

		discord::presence::update(&discord::presence::data.presence);
		discord::update.store(false);
	}

	discord::presence::shutdown();
	return TRUE;
}