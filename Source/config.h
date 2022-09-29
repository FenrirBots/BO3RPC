#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Json/Json.hpp"

#define CONFIG_NAME "Presence.json"

namespace Config
{
	void LoadConfig()
	{
		try
		{
			std::ifstream file(CONFIG_NAME);
			if (file.good())
			{
				Config::Config = nlohmann::json::parse(file);
			}
		}
		catch(nlohmann::json::exception)
		{

		}
		catch (std::exception)
		{

		}
	}

	extern nlohmann::json Config;
}