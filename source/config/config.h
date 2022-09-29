#pragma once
#include "config/parser/parser.h"

namespace config
{
	void load(); 
	void save();
	
	extern nlohmann::json data;
}