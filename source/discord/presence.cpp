#include "discord/discord.h"

DWORD WINAPI discord::thread(LPVOID /* lpvReserved */)
{
	discord::presence::initialize("1023037909848297522", 0, NULL);

	while (discord::running)
	{
		if (discord::update.load() == false)
		{
			Sleep(1);
			continue;
		}

		discord::presence::update(&discord::presence::data.presence);
		discord::update.store(false);
	}

	discord::presence::shutdown();
    return TRUE;
}