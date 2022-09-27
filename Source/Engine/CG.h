#pragma once
#include "Engine/EngineTypes.h"

// Client Game

namespace CG
{
	auto Draw2D = GetAddress<void(__fastcall*)(int localClientNumber)>(0x7FF771F1F910);
	auto Draw2DInternal = GetAddress<void(__fastcall*)(int localClientNumber)>(0x7FF771F1F920);
	auto BoldGameMessageCenter = GetAddress<void(__fastcall*)(int localClientNumber, const char* message)>(0x7FF7721D4C80);
}