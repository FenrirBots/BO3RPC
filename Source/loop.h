#pragma once
#include <Windows.h >
#include "Discord/Discord.h"
#include "Engine/Engine.h"
#include "LeoHook/LeoHook.h"

namespace Loop
{
	DWORD Attach(LPVOID);
	void GetInput();
	void Loop(int);

	extern bool Running;
	extern bool Update;
	extern bool ForceUpdate;
}