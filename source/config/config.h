#pragma once
#include "parser/parser.h"


namespace config
{
	void load(); 
	void save();
	
	extern nlohmann::json data;
}