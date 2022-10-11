#include "discord/discord.h"
#include "thirdparty/hook/hardware-breakpoint.h"
#include "thirdparty/hook/kiero.h"
#include "thirdparty/t7api/t7api.h"
#include "threads/threads.h"
#include <chrono>
#include "config.h"
#include "update.h"
#include "parser/parser.h"

unsigned long long g_entities = 0;
HRESULT(__stdcall* present)(IDXGISwapChain*, UINT, UINT);

std::chrono::steady_clock::time_point delta = std::chrono::steady_clock::now();
std::chrono::seconds getdelta(std::chrono::steady_clock::time_point now)
{
    return std::chrono::duration_cast<std::chrono::seconds>(now - delta);
}

HRESULT WINAPI update(IDXGISwapChain* swapchain, UINT interval, UINT flags)
{
    if(GetAsyncKeyState(VK_F9) & 0x8000)
    {
        discord::running.store(false);
        kiero::unbind(8);
        kiero::shutdown();
        hook_manager::get()["g_entities"]->unhook();

        CreateThread(0, 0, threads::detach, 0, 0, 0);
        return present(swapchain, interval, flags);
    }

    if(GetAsyncKeyState(VK_F5) & 0x8000)
    {
        config::load();
    }
    
    std::chrono::steady_clock steady_clock;
    if(getdelta(steady_clock.now()) >= ((t7api::com::isingame() == true) ? std::chrono::seconds(30) : std::chrono::seconds(5)))
    {
        auto presence = discord::presence::get();

        if(t7api::com::isingame())
        {
            if(presence.startTimestamp == 0)
                presence.startTimestamp = time(0);

            presence.partySize = t7api::lobbysession::getclientcount(1, 0);
                
            if(presence.partySize <= 0)
                presence.partySize = 1;

            presence.partyMax = t7api::lobbysession::getmaxclients(1);

            if(presence.partyMax <= 0)
                presence.partyMax = 1;

            // Developer Note: Puting this directly into largeImageKey
            // will cause the program to crash.
            /////////////////////////////////////////////////////////////
            const char* fastfile = reinterpret_cast<const char*>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF77AD1E5E8 - 0x7FF771910000));

            // Developer Note: Using the parser to get the fastfile
            // name does not work due to the max length value adding
            // a null terminating character at the end of the string.
            /////////////////////////////////////////////////////////////
            // Fix an issue where the image is empty if the key isnt a coremap
            presence.largeImageKey = fastfile;
            presence.largeImageText = parser::parse("${mapname}", 128).c_str();
            presence.smallImageKey = "logo-black";
            
            presence.state = "";
            presence.details = "";


            presence.instance = 1;

            try
            {
                const char* lobbymode = "";
                const char* sessionmode = "";

                // Developer Note: Puting this directly into the switch value
                // Will cause the program to crash.
                /////////////////////////////////////////////////////////////
                int mode = *(int*)(t7api::lobbysession::getsession(1) + 8);
                switch(mode)
                {
                    case LOBBY_MODE_PUBLIC:
                    lobbymode = "public";
                    break;
                    case LOBBY_MODE_CUSTOM:
                    lobbymode = "customs";
                    break;
                    case LOBBY_MODE_THEATER:
                    lobbymode = "theater";
                    break;
                    case LOBBY_MODE_ARENA:
                    lobbymode = "arena";
                    break;
                    case LOBBY_MODE_FREERUN:
                    lobbymode = "freerun";
                    break;

                }

                switch(t7api::com::sessionmode::getmode())
                {
                    case MODE_ZOMBIES:
                    sessionmode = "zombies";
                    break;
                    case MODE_MULTIPLAYER:
                    sessionmode = "multiplayer";
                    break;
                    case MODE_CAMPAIGN:
                    sessionmode = "campaign";
                    break;
                }

                
                if(lobbymode != NULL)
                {
                    if(sessionmode != NULL)
                    {
                        char details[128] = "";
                        char state[128] = "";

                        if(strcmp(sessionmode, "zombies"))
                        {
                            const char* partystate = "solo";

                            if(presence.partySize > 1)
                                partystate = "party";

                            sprintf_s(details, 128, "%s", parser::parse(config::get()["presence"][sessionmode][lobbymode][partystate]["details"].get<std::string>()).c_str());
                            sprintf_s(state, 128, "%s", parser::parse(config::get()["presence"][sessionmode][lobbymode][partystate]["state"].get<std::string>()).c_str());

                            if(!config::get()["presence"][sessionmode][lobbymode][partystate]["show-timestamp"].get<bool>())
                                presence.startTimestamp = 0;

                            if(!config::get()["presence"][sessionmode][lobbymode][partystate]["show-playercount"].get<bool>())
                                presence.instance = 0;
                        }
                        else
                        {
                            sprintf_s(details, 128, "%s", parser::parse(config::get()["presence"][sessionmode][lobbymode]["details"].get<std::string>()).c_str());
                            sprintf_s(state, 128, "%s", parser::parse(config::get()["presence"][sessionmode][lobbymode]["state"].get<std::string>()).c_str());

                            if(!config::get()["presence"][sessionmode][lobbymode]["show-timestamp"].get<bool>())
                                presence.startTimestamp = 0;

                            if(!config::get()["presence"][sessionmode][lobbymode]["show-playercount"].get<bool>())
                                presence.instance = 0;
                        }

                        if(details != NULL)
                            presence.details = details;

                        if(state != NULL)
                            presence.state = state;
                    }
                }
            }
            catch(...) {}
        }
        else
        {
            if(presence.startTimestamp != 0)
            {
                presence.startTimestamp = 0;
            }

            presence.details = "";
            presence.state = "";
            presence.largeImageKey = "logo-black";
            presence.largeImageText = "Call of Duty: Black Ops III";
            presence.smallImageKey = "";
            presence.partySize = 0;
            presence.partyMax = 0;
            presence.instance = 0;

            // Add support for pregame lobby later

            try
            {
                char cdetails[128];
                sprintf_s(cdetails, ARRAYSIZE(cdetails), "%s", parser::parse(config::get()["presence"]["mainmenu"]["details"].get<std::string>()).c_str());
                if(cdetails != NULL)
                    presence.details = cdetails;
                
                char cstate[128];
                sprintf_s(cstate, ARRAYSIZE(cstate), "%s", parser::parse(config::get()["presence"]["mainmenu"]["state"].get<std::string>()).c_str());
                if(cstate != NULL)
                    presence.state = cstate;

                OutputDebugStringA(cstate);
            }
            catch(...) {}
        }

        discord::presence::set(presence);
        delta = steady_clock.now();
    }

    return present(swapchain, interval, flags);
}



//                // So many if not empty checks...
//
//                    char cdetails[128];
//
//                    if(presence.partySize > 1) {
//                        sprintf_s(cdetails, ARRAYSIZE(cdetails), "%s", parser::parse(config::get()["presence"][sessionmode][lobbymode]["party"]["details"].get<std::string>()).c_str());
//                    } else {
//                        sprintf_s(cdetails, ARRAYSIZE(cdetails), "%s", parser::parse(config::get()["presence"][sessionmode][lobbymode]["solo"]["details"].get<std::string>()).c_str());
//                    } 
//                        
//                    if(cdetails != NULL) {
//                        presence.details = cdetails;
//                    }
//
//
//                    char cstate[128];
//                    if(presence.partySize > 1) {
//                        sprintf_s(cdetails, ARRAYSIZE(cdetails), "%s", parser::parse(config::get()["presence"][sessionmode][lobbymode]["party"]["state"].get<std::string>()).c_str());
//                    } else {
//                        sprintf_s(cdetails, ARRAYSIZE(cdetails), "%s", parser::parse(config::get()["presence"][sessionmode][lobbymode]["solo"]["state"].get<std::string>()).c_str());
//                    }
//                        
//                    if(cstate != NULL) {
//                        presence.state = cstate;



















/*

                    switch(t7api::com::sessionmode::getmode())
                    {
                        case MODE_ZOMBIES:
                            if(presence.partySize > 1)
                            {
                                sprintf_s(details, 128, "%s", parser::parse(config::get()["presence"]["zombies"][lobbymode]["party"]["details"].get<std::string>()).c_str());
                                sprintf_s(state, 128, "%s", parser::parse(config::get()["presence"]["zombies"][lobbymode]["party"]["state"].get<std::string>()).c_str());

                                if(!config::get()["presence"]["zombies"][lobbymode]["party"]["show-timestamp"].get<bool>())
                                    presence.startTimestamp = 0;

                                if(config::get()["presence"]["zombies"][lobbymode]["party"]["show-playercount"].get<bool>())
                                    presence.instance = 0;
                            }

                            else
                            {
                                sprintf_s(details, 128, "%s", parser::parse(config::get()["presence"]["zombies"][lobbymode]["solo"]["details"].get<std::string>()).c_str());
                                sprintf_s(state, 128, "%s", parser::parse(config::get()["presence"]["zombies"][lobbymode]["solo"]["state"].get<std::string>()).c_str());

                                if(!config::get()["presence"]["zombies"][lobbymode]["party"]["show-timestamp"].get<bool>())
                                    presence.startTimestamp = 0;

                                if(config::get()["presence"]["zombies"][lobbymode]["party"]["show-playercount"].get<bool>())
                                    presence.instance = 0;
                            }
                        break;
                        case MODE_MULTIPLAYER:
                            sprintf_s(details, 128, "%s", parser::parse(config::get()["presence"]["multiplayer"][lobbymode]["details"].get<std::string>()).c_str());
                            sprintf_s(state, 128, "%s", parser::parse(config::get()["presence"]["multiplayer"][lobbymode]["state"].get<std::string>()).c_str());
                        break;

                                if(!config::get()["multiplayer"]["zombies"][lobbymode]["show-timestamp"].get<bool>())
                                    presence.startTimestamp = 0;

                                if(config::get()["multiplayer"]["zombies"][lobbymode]["show-playercount"].get<bool>())
                                    presence.instance = 0;
                        case MODE_CAMPAIGN:
                            sprintf_s(details, 128, "%s", parser::parse(config::get()["presence"]["campaign"][lobbymode]["details"].get<std::string>()).c_str());
                            sprintf_s(state, 128, "%s", parser::parse(config::get()["presence"]["campaign"][lobbymode]["state"].get<std::string>()).c_str());

                                if(!config::get()["presence"]["campaign"][lobbymode]["show-timestamp"].get<bool>())
                                    presence.startTimestamp = 0;

                                if(config::get()["presence"]["campaign"][lobbymode]["show-playercount"].get<bool>())
                                    presence.instance = 0;
                        break;
                    }


*/