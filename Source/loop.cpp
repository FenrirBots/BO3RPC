#include "loop.h"
#include <chrono>

bool Loop::Update = true;
bool Loop::Running = true;
bool Loop::ForceUpdate = false;

std::chrono::steady_clock::time_point delta = std::chrono::steady_clock::now();


void Loop::GetInput()
{
	// Enable Rich Presence
	if (GetAsyncKeyState(VK_F5) & 0x01)
	{
		if (Loop::Update == false)
		{
			Discord::Update = true;
			Loop::Update = true;
		}
	}

	// Disable Rich Presence
	if (GetAsyncKeyState(VK_F6) & 0x01)
	{
		if (Loop::Update == true)
		{
			Discord::Update = false;
			Loop::Update = false;
		}
	}

	// Clear Presence Data
	if (GetAsyncKeyState(VK_F7) & 0x01)
	{
		Discord::Clear = true;
	}

	// Reload config from disk
	if (GetAsyncKeyState(VK_F8))
	{
		// This hasnt been implemented yet
	}

	// Detach from target process
	if (GetAsyncKeyState(VK_F9))
	{
		// This doesnt work with leohook...
	}
}

void Loop::Loop(int localClientNumber)
{
	Loop::GetInput();

	if (Loop::Update)
	{
		std::chrono::steady_clock timer;

		if (std::chrono::duration_cast<std::chrono::seconds>(timer.now() - delta) >= std::chrono::seconds(5))
		{
			Discord::RichPresence.lock();

			if (Com::IsInGame())
			{

				Discord::RichPresence.Presence.instance = 1;
			}
			else
			{
				// Find the function for this
				Discord::RichPresence.Presence.partySize = 1;
				Discord::RichPresence.Presence.partyMax = LobbySession::GetMaxClients(0);
				Discord::RichPresence.Presence.instance = 0;
			}

			Discord::RichPresence.unlock();

			delta = timer.now();
		}
	}

	// This hook works by intercepting the target function as its called so we have to return CG_Draw2DInternal so we dont crash.
	return CG::Draw2DInternal(localClientNumber);
}

DWORD Loop::Attach(LPVOID /* lpvReserved */)
{
	if (!LeoHook::Hook((uint64_t)CG::Draw2D, (uint64_t)Loop::Loop))
	{
		// Failed to hook, notify the user somehow.
		return FALSE;
	}

	return TRUE;
}