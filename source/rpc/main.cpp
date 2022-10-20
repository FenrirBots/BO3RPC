#include <Windows.h>
#include "threads/threads.h"

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstance);
		CreateThread(0, 0, threads::attach, 0, 0, 0);
	}

	return TRUE;
}