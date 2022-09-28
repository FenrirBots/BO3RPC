#pragma once
#include "Engine/EngineTypes.h"

// Reference for Com_SessionMode_IsMode
//	MODE_ZOMBIES = 0x0,
//	MODE_MULTIPLAYER = 0x1,
//	MODE_CAMPAIGN = 0x2,
//	MODE_COUNT = 0x3,
//	MODE_INVALID = 0x3,
//	MODE_FIRST = 0x0,


namespace Com
{
	extern bool(__cdecl* IsInGame)();

	namespace SessionMode
	{
		extern bool(__fastcall* IsMode)(int);
		extern uint64(__cdecl* GetMode)();
	}
}
