#include <Windows.h>
#include "discord/discord.h"
#include "leohook/leohook.h"
#include "engine/engine.h"


DWORD WINAPI hook(LPVOID /* lpvReserved */)
{
	// Initialize configuration here

	if (!LeoHook::Hook(reinterpret_cast<uintptr_t>(engine::cg::draw2d), reinterpret_cast<uintptr_t>(engine::cg::draw2dhook)))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstance);

		CreateThread(0, 0, hook, 0, 0, 0);
		CreateThread(0, 0, discord::thread, 0, 0, 0);
	}

	return TRUE;
}