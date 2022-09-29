#pragma once
#include <fstream>
#include <iostream>
//#include <filesystem>
#include "Json/Json.hpp"

#define CONFIG_NAME "Presence.json"

namespace Config
{
	extern nlohmann::json m_Config;

	void LoadConfig();
}