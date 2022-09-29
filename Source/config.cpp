#include "Config.h"

nlohmann::json Config::m_Config;

void Config::LoadConfig()
{
	try
	{
		std::ifstream file(CONFIG_NAME);
		if (file.good())
		{
			Config::m_Config = nlohmann::json::parse(file);
		}
	}
	catch (nlohmann::json::exception)
	{

	}
	catch (std::exception)
	{

	}
}