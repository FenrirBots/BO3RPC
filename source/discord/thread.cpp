#include "discord/discord.h"
#define APPLICATION_ID "1023037909848297522"


DWORD WINAPI discord::thread(LPVOID /* lpvReserved */)
{
	discord::presence::initialize(APPLICATION_ID, 0, NULL);

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