#include "loop.h"
#include "config.h"
#include <chrono>

bool Loop::Update = true;
bool Loop::Running = true;
bool Loop::ForceUpdate = false;

auto Delta = std::chrono::steady_clock::now();

void Loop::Loop(int localClientNumber)
{
	if (Loop::Update)
	{
		std::chrono::steady_clock Time;

		auto UpdateTime = std::chrono::seconds(5);
		if (Com::IsInGame()) {
			UpdateTime = std::chrono::seconds(30);
		}

		if (std::chrono::duration_cast<std::chrono::seconds>(Time.now() - Delta) >= UpdateTime) {
			if (!Discord::Update) { // This needs to be named better...
				Discord::UpdatePresence();
			}
			Delta = Time.now();
		}
	}

	// This hook works by intercepting the target function as its called so we have to return CG_Draw2DInternal so we dont crash.
	return CG::Draw2DInternal(localClientNumber);
}

DWORD Loop::Attach(LPVOID /* lpvReserved */) {
	Config::LoadConfig();

	if (!LeoHook::Hook((uint64_t)CG::Draw2D, (uint64_t)Loop::Loop))
		return FALSE;

	return TRUE;
}