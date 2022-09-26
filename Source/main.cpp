#include <Windows.h>
#include "main.h"
#include <string>

// Temp Functions
DWORD Hook(LPVOID)
{

}

DWORD Loop(LPVOID)
{
	DiscordEventHandlers pEventHandlers;
	ZeroMemory(&pEventHandlers, sizeof DiscordEventHandlers);

	Discord_Initialize("", pEventHandlers, 1, 0);

	while (true)
	{

	}
}
//!Temp Functions



BOOL APIENTRY DllMain(HINSTANCE lpReserved, DWORD dwReason, LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(lpReserved);
		
		CreateThread(0, 0, Hook, 0, 0, 0);
		CreateThread(0, 0, Loop, 0, 0, 0);
	}
}