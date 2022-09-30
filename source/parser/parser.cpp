#include <Windows.h>
#include "parser/parser.h"


std::string lower(std::string input)
{
	std::string output;
	std::transform(input.begin(), input.end(), back_inserter(output), (char(__cdecl*)(int c))::tolower);
	return output;
}

size_t find(std::string input, std::string target)
{
	std::string n = lower(input);
	std::string t = lower(target);
	size_t position = n.find(t);

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
	bool removeinvalid;

	std::string parse(std::string input, size_t maxlength)
	{
		std::string output(input);

		while (true)
		{
			bool parsed = false;

			for (int rule = 0; rule < parser::rules.size(); rule++)
			{
				size_t position = find(output, parser::rules[rule].content);
				if (position != std::string::npos)
				{
					output = replace(position, parser::rules[rule].length, output, parser::rules[rule].callback());
					parsed = true;
				}
			}

			if (parsed == false)
			{
				break;
			}
		}

		if(removeinvalid)
		{
			while(true)
			{
				size_t positionl = find(output, "${");
				size_t positionr = find(output, "}");
				if(positionl == std::string::npos)
				{
					break;
				}

				if(positionr == std::string::npos)
				{
					break;
				}

				output = replace(positionl, positionr - positionl + 1, output, "");
			}
		}

		if(maxlength > 0)
		{
			if(output.length() > maxlength)
			{
				output.resize(maxlength);
			}
		}
		
		return output;
	}

	std::string parse(std::string input)
	{
		return parse(input, 0);
	}

	void addrule(std::string content, std::string(*callback)())
	{
		parser::rules.push_back(rule_t{ content, content.length(), callback });
	}
}