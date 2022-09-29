#pragma once
#include <Atomic>
#include <Mutex>
#include <Windows.h>
#include "discord/discord_register.h"
#include "discord/discord_rpc.h"


struct MultiThreadedPresence : public std::mutex
{
	DiscordRichPresence presence;
};

namespace discord
{
	DWORD WINAPI thread(LPVOID);

	extern std::atomic<bool> update;
	extern std::atomic<bool> running;

	namespace presence
	{
		extern MultiThreadedPresence data;

		void initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId)
		{
			Discord_Initialize(applicationId, handlers, autoRegister, optionalSteamId);
		}

		void shutdown()
		{
			Discord_Shutdown();
		}

		void update(DiscordRichPresence* presence)
		{
			Discord_UpdatePresence(presence);
		}

		void clear()
		{
			Discord_ClearPresence();
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
	}
}