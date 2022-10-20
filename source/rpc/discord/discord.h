#pragma once
#include <Atomic>
#include <Mutex>
#include <Windows.h>
#include "thirdparty/discord/discord_register.h"
#include "thirdparty/discord/discord_rpc.h"


struct MultiThreadedPresence : public std::mutex
{
	DiscordRichPresence presence;
};

namespace discord
{
    namespace presence
    {
		void initialize(const char* applicationId, int autoRegister, const char* optionalSteamId);
		DiscordRichPresence get();
		void set(DiscordRichPresence presence);
		void update(DiscordRichPresence* presence);
		void clear();
		void shutdown();
    
        extern MultiThreadedPresence data;
    }
    
	DWORD WINAPI thread(LPVOID);
    extern std::atomic<bool> update;
    extern std::atomic<bool> running;
}