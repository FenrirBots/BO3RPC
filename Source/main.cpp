#include "LeoHook/LeoHook.h"
#include "discord/discord.h"
#include "Engine/Engine.h"

bool bEnabled;
bool bForceUpdate;
HINSTANCE Handle;

DWORD WINAPI Detach(LPVOID /* lpvReserved */)
{
	if (!LeoHook::Unhook())
	{
		FreeLibraryAndExitThread(Handle, 0);
		return FALSE;
	}

	return TRUE;
}

void CGDraw2D_Loop(int localClientNumber)
{
	// Handle all the discord stuff here and pass it to Discord::Loop when we are done...
	// It may be possible to run discord here but i havent checked...
	// The only issue with running it here and updating somewhere else is thread safety...

	// Add a way to set the keybinds from a config
	if (GetAsyncKeyState(VK_F5) & 0x01)
	{
		if (bEnabled == true)
		{
			bEnabled = false;
			
			// disable rpc here
			// clear presence here

			CG::BoldGameMessageCenter(0, "DiscordRPC has been Disabled.");
		}
		else
		{
			bEnabled = true;

			// enable rpc here
			
			CG::BoldGameMessageCenter(0, "DiscordRPC has been Enabled.");
		}
	}

	if (GetAsyncKeyState(VK_F9) & 0x1)
	{
		CreateThread(0, 0, Detach, 0, 0, 0);
		CG::Draw2DInternal(localClientNumber);
	}

	if (bEnabled)
	{
		if (Com::IsInGame() || bForceUpdate)
		{
			if (bForceUpdate)
				bForceUpdate = false;
		}
		else
		{

		}
	}

	// Calling CG_Draw2D will cause an infinite callback loop so we return CG_Draw2DInternal instead.
	return CG::Draw2DInternal(localClientNumber);
}

DWORD WINAPI Attach(LPVOID /* lpvReserved */)
{
	// I hate this uintptr_t cast
	if (!LeoHook::Hook((uintptr_t)CG::Draw2D, (uintptr_t)CGDraw2D_Loop))
	{
		OutputDebugStringA("LeoHook::Hook() returned FALSE");
		// Failed to hook...
		return 0;
	}

	OutputDebugStringA("LeoHook::Hook() returned TRUE");

	return 1;
}


#include <Windows.h>
BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstance);
		Handle = hInstance;

		CreateThread(0, 0, Attach, 0, 0, 0);
		//CreateThread(0, 0, Discord::Loop, 0, 0, 0);
	}

	return TRUE;
}