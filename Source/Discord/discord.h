#pragma once
#include <Windows.h>
#include "discord/discord_register.h"
#include "discord/discord_rpc.h"

namespace Discord
{
	DWORD WINAPI Loop(LPVOID /*lpvReserved*/);
}