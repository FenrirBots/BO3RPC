#pragma once
#include "thirdparty/json/json.h"

namespace config
{
	void load();
	nlohmann::json get();

	extern nlohmann::json data;
}