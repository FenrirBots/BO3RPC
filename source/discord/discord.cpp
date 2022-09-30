#include "discord/discord.h"

namespace discord
{
	std::atomic<bool> update;
	std::atomic<bool> running = true;

	namespace presence
	{
		MultiThreadedPresence data;

		void initialize(const char* applicationId, int autoRegister, const char* optionalSteamId)
		{
			DiscordEventHandlers EventHandlers;
			ZeroMemory(&EventHandlers, sizeof(DiscordEventHandlers));
			
			discord::presence::data.lock();
			ZeroMemory(&discord::presence::data.presence, sizeof(DiscordRichPresence));
			discord::presence::data.unlock();

			Discord_Initialize(applicationId, &EventHandlers, autoRegister, optionalSteamId);
		}

		DiscordRichPresence get()
		{
			// Not sure if this is thread safe
			return discord::presence::data.presence;
		}

		void set(DiscordRichPresence presence)
		{
			if (discord::update.load() == false) {
				discord::presence::data.lock();
				discord::presence::data.presence = presence;
				discord::presence::data.unlock();
				discord::update.store(true);
			}
		}

		void update(DiscordRichPresence* presence)
		{
			Discord_UpdatePresence(presence);
		}

		void clear()
		{
			Discord_ClearPresence();
		}

		void shutdown()
		{
			Discord_Shutdown();
		}
	}
}