#pragma once
#include "Engine/EngineTypes.h"

namespace Com
{
	auto IsInGame = GetAddress<bool(__cdecl*)()>(0x7FF773A58D20);
}