#include <Windows.h>
#include "discord/discord.h"
#include "leohook/leohook.h"


DWORD WINAPI hook(LPVOID /* lpvReserved */)
{
	if (!LeoHook::Hook(nullptr, nullptr))
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
		CreateThread(0, 0, discord::thread, 0, 0, 0);
		CreateThread(0, 0, hook, 0, 0, 0);
	}

	return TRUE;
}