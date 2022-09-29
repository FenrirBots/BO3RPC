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


int find(std::string string, const char* szstring)
{
	std::string::iterator pos = std::search(string.begin(), string.end(), std::string(szstring).begin(), std::string(szstring).end(), [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); });
	if (fpos != string.end())
		return std::distance(text.beign(), pos);
	return 0;
}

const char* ParseString(const char* data)
{
	std::string string(data);

	while (true)
	{
		int pos = 0;
		
		pos = find(string, "${CurrentRound}");
		if (pos > 0)
		{
			uint64 DDLState = 0;
			if (DDL::MoveToName(&*GetAddress<uint64*>(0x7FF774C3F680), &DDLState, "numZombieRounds"))
			{
				auto CurrentRound = DDL::GetUInt(&DDLState, &*GetAddress<uint64*>(0x7FF77B506A20)) + 1);
				string.replace(pos, std::string("${CurrentRound}").length(), std::to_string(CurrentRound));
			}
			else
			{
				string.replace(pos, std::string("${CurrentRound}").length(), "0");
			}

			continue;
		}

		pos = find(string, "${ZombiesKilled");
		if (pos > 0)
		{
			string.replace(pos, std::string("${Deaths}").length(), "0");
			continue;
		}
		
		pos = find(string, "${Downs}");
		if (pos > 0)
		{
			string.replace(pos, std::string("${Deaths}").length(), "0");
			continue;
		}

		`pos = find(string, "${Deaths}");
		if (pos > 0)
		{
			string.replace(pos, std::string("${Deaths}").length(), "0");
			continue;
		}
		
		pos = find(string, "${MapName}");
		if (pos > 0)
		{
			string.replace(pos, std::string("${MapName}").length(), (const char*)((uint64)GetModuleHandle(0) + 0x194417A2));
			continue;
		}

		// If we dont find anything, exit the loop.
		break;
	}

	return string.c_str();
}

void Discord::UpdatePresence()
{
	if (!Discord::Update)
	{
		Discord::RichPresence.lock();
		auto LobbyMode = *(int*)(LobbySession::GetSession(1) + 0x8);
		
		if (Com::IsInGame())
		{

			switch (LobbyMode)
			{
			case 0:
				if (Com::SessionMode::IsMode(0))
				{
					std::string details;
					std::string state;

					if (LobbySession::GetClientCount(1, 0) <= 1)
					{
						state = Config::Config["Zombies"]["Presence"]["State"]["2-4"];
					}
					else
					{
						state = Config::Config["Zombies"]["Presence"]["State"]["2-4"];
					}

					Discord::RichPresence.Presence.state = Discord::ParseString(state);
				}
				else if (Com::SessionMode::IsMode(1))
				{

				}
				else if (Com::SessionMode::IsMode(2))
				{

				}
				break;
			case 1:
				if (Com::SessionMode::IsMode(0))
				{

				}
				else if (Com::SessionMode::IsMode(1))
				{

				}
				else if (Com::SessionMode::IsMode(2))
				{

				}
				break;
			case 2:
				if (Com::SessionMode::IsMode(0))
				{

				}
				else if (Com::SessionMode::IsMode(1))
				{

				}
				break;
			case 3:
				// Arena
				break;
			case 4:
				// Freerun
				break;
			default:
			}
		}
		else
		{

		}

		Discord::RichPresence.unlock();
	}
}