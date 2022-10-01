#include <Windows.h>
#include "config/config.h"
#include "discord/discord.h"
#include "leohook/leohook.h"
#include "engine/engine.h"
#include "parser/parser.h"


DWORD WINAPI hook(LPVOID /* lpvReserved */)
{
	// Initialize configuration here
	config::load();

	parser::removeinvalid = true;
	parser::addrule("${mapname}", []()->std::string {
		if(engine::address::get<const char*>(0x7FF78AD517A2) == std::string(""))
		{
			return "usermaps";
		}

		return engine::address::get<const char*>(0x07FF78AD517A2);
	});
	parser::addrule("${round}", []()->std::string {
		unsigned long long state;
		if (engine::ddl::movetoname(&*engine::address::get<unsigned long long*>(0x7FF774C3F680), &state, "numZombieRounds"))
		{
			int round = engine::ddl::getuint(&state, &*engine::address::get<unsigned long long*>(0x7FF77B506A20));
			return std::to_string(round + 1);
		}

		return "0";
	});

	// Planned rules that are to be added
	//parser::addrule("${team}", team);
	//parser::addrule("${nattype}", nattype);
	//parser::addrule("${downs}", downs);
	//parser::addrule("${kills}", kills);
	//parser::addrule("${deaths}", deaths);
	//parser::addrule("${videoname}", videoname);

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