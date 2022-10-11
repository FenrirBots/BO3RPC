#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include "thirdparty/json/json.h"


struct rule_t
{
	std::string content;
	size_t length;
	std::string(*callback)();
};

namespace parser
{
	extern bool removeinvalid;
	extern std::vector<rule_t> rules;

	std::string parse(const std::string input, size_t maxlength);
	std::string parse(const std::string input);
	void addrule(std::string content, std::string(*callback)());
}