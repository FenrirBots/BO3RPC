#pragma once
#include <Atomic>
#include <Mutex>
#include <Windows.h>
#include "discord/discord_register.h"
#include "discord/discord_rpc.h"


struct MultiThreadedPresence : public std::mutex
{
	DiscordRichPresence Presence;
};

namespace Discord
{
	DWORD WINAPI Loop(LPVOID);
	void UpdatePresence();

	extern MultiThreadedPresence RichPresence;
	extern std::atomic<bool> Clear;
	extern std::atomic<bool> Update;
	extern std::atomic<bool> Running;
}