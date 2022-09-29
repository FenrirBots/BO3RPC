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

std::string lower(std::string input)
{
	std::string output;
	std::transform(input.begin(), input.end(), back_inserter(output), ::tolower);
	return output;
}

size_t find(std::string input, std::string target)
{
	std::string n = lower(input);
	std::string t = lower(target);
	size_t position = n.find(t);

	if (position == std::string::npos)
	{
		return 0;
	}

	return position;
}

std::string replace(size_t position, size_t length, std::string input, std::string replacement)
{
	std::string output(input);

	output.replace(output.begin() + position, output.begin() + position + length, replacement);

	return output;
}

std::string Discord::ParseString(std::string input)
{
	std::string output(input);

	while (true)
	{
		size_t position = 0;

		position = find(input, "${currentround}");
		if (position > 0)
		{
			uint64 DDLState = 0;
			static size_t length = std::string("${currentround}").length();

			if (DDL::MoveToName(&*GetAddress<uint64*>(0x7FF774C3F680), &DDLState, "numZombieRounds"))
			{
				auto CurrentRound = DDL::GetUInt(&DDLState, &*GetAddress<uint64*>(0x7FF77B506A20)) + 1;
				output = replace(position, length, output, std::to_string(CurrentRound));
			}
			else
			{
				output = replace(position, length, output, "0");
			}

			continue;
		}

		position = find(input, "${currentround}");
		if (position > 0)
		{
			static size_t length = std::string("${currentround}").length();
			output = replace(position, length, output, GetAddress<const char*>(0x7FF78AD517A2));
			continue;
		}

		break;
	}

	return output;
}

void Discord::UpdatePresence()
{
	if (!Discord::Update)
	{
		Discord::RichPresence.lock();
		auto LobbyMode = *(int*)(LobbySession::GetSession(1) + 0x8);
		
		if (Com::IsInGame())
		{
			if (Discord::RichPresence.Presence.startTimestamp == 0)
			{
				Discord::RichPresence.Presence.startTimestamp = time(0);
			}

			switch (LobbyMode)
			{
			case 0:
				if (Com::SessionMode::IsMode(0))
				{
					std::string details;
					std::string state;

					try
					{
						if (LobbySession::GetClientCount(1, 0) <= 1)
						{
							details = Config::m_Config["Zombies"]["presence"]["details"]["0-1"]["ingame-public"].get<std::string>();
							state = Config::m_Config["Zombies"]["presence"]["state"]["0-1"]["ingame-public"].get<std::string>();
						}
						else
						{
							details = Config::m_Config["Zombies"]["presence"]["details"]["2-4"]["ingame-public"].get<std::string>();
							state = Config::m_Config["Zombies"]["presence"]["state"]["2-4"]["ingame-public"].get<std::string>();
						}

						Discord::RichPresence.Presence.state = Discord::ParseString(state).c_str();
						Discord::RichPresence.Presence.details = Discord::ParseString(details).c_str();
					} catch (nlohmann::json::exception e) { OutputDebugStringA(e.what()); }
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
					std::string details;
					std::string state;

					try
					{
						if (LobbySession::GetClientCount(1, 0) <= 1)
						{
							details = Config::m_Config["Zombies"]["presence"]["details"]["0-1"]["ingame-customs"].get<std::string>();
							state = Config::m_Config["Zombies"]["presence"]["state"]["0-1"]["ingame-customs"].get<std::string>();
						}
						else
						{
							details = Config::m_Config["Zombies"]["presence"]["details"]["2-4"]["ingame-customs"].get<std::string>();
							state = Config::m_Config["Zombies"]["presence"]["state"]["2-4"]["ingame-customs"].get<std::string>();
						}

						Discord::RichPresence.Presence.state = Discord::ParseString(state).c_str();
						Discord::RichPresence.Presence.details = Discord::ParseString(details).c_str();
					} catch (nlohmann::json::exception e) { OutputDebugStringA(e.what()); }
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
				break;
			}
		}
		else
		{

		}

		Discord::RichPresence.unlock();
		Discord::Update = true;
	}
}