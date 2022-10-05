#include <Windows.h>
#include "config/config.h"
#include "discord/discord.h"
#include "leohook/leohook.h"
#include "engine/engine.h"
#include "parser/parser.h"
#include "hwbp/hwbp.h"
#include "spoofer/spoofer.h"

unsigned long long gentities = 0;
unsigned long long centities = 0;

std::string downs()
{
//	if(!gentities)
//	{
//		return "0";
//	}
//
	OutputDebugStringA("index");
	unsigned long long entitystate;
	if(!engine::ddl::movetoindex(&*engine::address::get<unsigned long long*>(0X7FF774C3F520), &entitystate, 0))
	{
		return "0";
	}

	OutputDebugStringA("name");
	unsigned long long state;
	if(!engine::ddl::movetoname(&entitystate, &state, "downs"))
	{
		return "0";
	}

	OutputDebugStringA("string");
	return std::to_string(engine::ddl::getuint(&state, &*engine::address::get<unsigned long long*>(0x7FF77B506A20)));
}

std::string mapname()
{
	if(engine::address::get<const char*>(0x7FF78AD517A2) == std::string(""))
	{
		return "usermaps";
	}

	return engine::address::get<const char*>(0x07FF78AD517A2);
}

std::string round()
{
	unsigned long long state;
	if (engine::ddl::movetoname(&*engine::address::get<unsigned long long*>(0x7FF774C3F680), &state, "numZombieRounds"))
	{
		int round = engine::ddl::getuint(&state, &*engine::address::get<unsigned long long*>(0x7FF77B506A20));
		return std::to_string(round + 1);
	}

	return "0";
}

DWORD WINAPI hook(LPVOID /* lpvReserved */)
{
	auto& manager = hook_manager::get();
	manager.init();
	manager["gentities"]->hook(engine::address::get<void*>(0x7FF77343C415), nullptr);
	manager["draw2d"]->hook(engine::cg::draw2d, engine::cg::draw2dhook);
	return TRUE;
}

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstance);
		parser::addrule("${mapname}", mapname);
		parser::addrule("${round}", round);
		parser::addrule("${downs}", downs);
		config::load();

		CreateThread(0, 0, hook, 0, 0, 0);
		CreateThread(0, 0, discord::thread, 0, 0, 0);
	}

	return TRUE;
}