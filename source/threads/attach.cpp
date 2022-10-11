#include "discord/discord.h"
#include "thirdparty/hook/hardware-breakpoint.h"
#include "thirdparty/hook/kiero.h"
#include "threads/threads.h"
#include "parser/parser.h"
#include "parser/rules.h"
#include "config.h"
#include "update.h"


DWORD WINAPI threads::attach(LPVOID /* lpvReserved */)
{
    config::load();
      parser::addrule("${ping}", parser::callbacks::ping);
      parser::addrule("${place}", parser::callbacks::place);
      parser::addrule("${score}", parser::callbacks::score);
      parser::addrule("${kills}", parser::callbacks::kills);
      parser::addrule("${assists}", parser::callbacks::assists);
      parser::addrule("${deaths}", parser::callbacks::deaths);
      parser::addrule("${downs}", parser::callbacks::downs);
      parser::addrule("${revives}", parser::callbacks::revives);
      parser::addrule("${headshots}", parser::callbacks::headshots);
      parser::addrule("${mapname}", parser::callbacks::mapname);
      parser::addrule("${fastfile}", parser::callbacks::fastfile);
      parser::addrule("${round}", parser::callbacks::round);
      parser::addrule("${username}", parser::callbacks::username);
      parser::addrule("${sessionmode}", parser::callbacks::sessionmode);

    if(KIEROFAILED(kiero::init(kiero::RenderType::D3D11))  ||
       KIEROFAILED(kiero::bind(8, (void**)&present, update)))
    {
        return FALSE;
    }

    if(hook_manager::get().init())
    {
        hook_manager::get()["g_entities"]->hook(reinterpret_cast<void*>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF77343C415 - 0x7FF771910000)), nullptr);
    }

	CreateThread(0, 0, discord::thread, 0, 0, 0);
    return TRUE;
}