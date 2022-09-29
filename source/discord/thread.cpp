#include "discord/discord.h"
#define APPLICATION_ID "1023037909848297522"

std::atomic<bool> discord::running = true;
std::atomic<bool> discord::presence::update = false;
MultiThreadedPresence discord::presence::data;


DWORD WINAPI discord::thread(LPVOID /* lpvReserved */)
{
	ZeroMemory(&discord::presence::data.presence, sizeof(DiscordRichPresence));

	DiscordEventHandlers EventHandlers;
	ZeroMemory(&EventHandlers, sizeof(DiscordEventHandlers));


	discord::presence::initialize("", &EventHandlers, 0, 0);

	while (discord::running)
	{
		if (discord::presence::update == false)
		{
			continue;
		}

		discord::presence::update(&discord::presence::data.presence);
		discord::presence::update = false;
	}

	discord::presence::shutdown();
}