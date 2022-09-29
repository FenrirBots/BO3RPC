#pragma once
#include <string>
#include <vector>


struct rule_t
{
	std::string content;
	size_t length;
	std::string(*callback)();
};

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
		return -1;
	}

	return position;
}

std::string replace(size_t position, size_t length, std::string input, std::string replacement)
{
	std::string output(input);

	output.replace(output.begin() + position, output.begin() + position + length, replacement);

	return output;
}

namespace parser
{
	std::vector<rule_t> rules;

	std::string parse(std::string input)
	{
		std::string output(input);

		while (true)
		{
			bool parsed = false;

			for (int rule = 0; rule < config::parser::rules.size(); rule++)
			{
				size_t position = find(output, config::parser::rules[rule].content);
				if (position != -1)
				{
					output = replace(position, config::parser::rules[rule].length, output, config::parser::rules[rule].callback());
					parsed = true;
				}

				break;
			}

			// If nothing has been parsed
			if (parsed == false)
			{
				break;
			}
		}

		return output;
	}

	void addrule(std::string content, std::string(*callback)())
	{
		config::parser::rules.push_back(rule_t{ content, content.length(), callback });
	}
}