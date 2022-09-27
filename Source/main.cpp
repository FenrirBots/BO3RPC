#include "loop.h"

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstance);

		CreateThread(0, 0, Loop::Attach, 0, 0, 0);
		CreateThread(0, 0, Discord::Loop, 0, 0, 0);
	}

	return TRUE;
}




//bool bEnabled;
//bool bForceUpdate;
//
//void CGDraw2D_Loop(int localClientNumber)
//{
	// Handle all the discord stuff here and pass it to Discord::Loop when we are done...
	// It may be possible to run discord here but i havent checked...
	// The only issue with running it here and updating somewhere else is thread safety...

	// Add a way to set the keybinds from a config
//	if (GetAsyncKeyState(VK_F5) & 0x01)
//	{
//		if (bEnabled == true)
//		{
//			bEnabled = false;
//			
//			// disable rpc here
//			// clear presence here
//
//			CG::BoldGameMessageCenter(0, "DiscordRPC has been Disabled.");
//		}
//		else
//		{
//			bEnabled = true;
//
//			// enable rpc here
//			
//			CG::BoldGameMessageCenter(0, "DiscordRPC has been Enabled.");
//		}
//	}
//
//	if (GetAsyncKeyState(VK_F6) & 0x01)
//	{
//		CG::BoldGameMessageCenter(0, "DiscordRPC: Force Update Requested.");
//
//		Discord::pTestPresence.lock();
//		Discord::pTestPresence.details = "Testing123asd";
//		Discord::pTestPresence.state = "TestState";
//		Discord::pTestPresence.partyMax = 4;
//		Discord::pTestPresence.partySize = 1;
//		Discord::pTestPresence.unlock();
//	}
//
//	if (bEnabled)
//	{
//		if (!Com::IsInGame() || bForceUpdate)
//		{
//			if (bForceUpdate)
//				bForceUpdate = false;
//		}
//		else
//		{
//
//		}
//	}
//
//	// Calling CG_Draw2D will cause an infinite callback loop so we return CG_Draw2DInternal instead.
//	return CG::Draw2DInternal(localClientNumber);
//}
//
//DWORD WINAPI Attach(LPVOID /* lpvReserved */)
//{
//	if (!LeoHook::Hook((uintptr_t)CG::Draw2D, (uintptr_t)CGDraw2D_Loop))
//	{
//		return FALSE;
//	}
//
//	return TRUE;
//}
