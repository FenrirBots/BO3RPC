#pragma once
#include "Engine/EngineTypes.h"

namespace DDL
{
	extern bool(__fastcall* MoveToName)(uint64*, uint64*, const char*);
	extern unsigned int(__fastcall* GetUInt)(uint64*, uint64*);
}