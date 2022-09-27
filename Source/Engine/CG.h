#pragma once
#include "Engine/EngineTypes.h"

namespace CG
{
	extern void(__fastcall* Draw2D)(int);
	extern void(__fastcall* Draw2DInternal)(int);
	extern void(__fastcall* BoldGameMessageCenter)(int, const char*);
}