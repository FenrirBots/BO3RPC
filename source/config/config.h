#pragma once
#include "parser/parser.h"


namespace config
{
	void load();
	nlohmann::json get();

	extern nlohmann::json data;
}