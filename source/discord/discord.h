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

		void initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId);
		void shutdown();
		void update(DiscordRichPresence* presence);
		void clear();
		void set(DiscordRichPresence presence);
	}
}