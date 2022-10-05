#include "config/config.h"
#include "discord/discord.h"
#include "engine/cg.h"
#include "engine/com.h"
#include "engine/lobbysession.h"
#include "engine/enginetypes.h"
#include "parser/parser.h"
#include <chrono>


enum LobbyMode
{
    LOBBY_MODE_PUBLIC  = 0x0,
    LOBBY_MODE_CUSTOM  = 0x1,
    LOBBY_MODE_THEATER = 0x2,
    LOBBY_MODE_ARENA   = 0x3,
    LOBBY_MODE_FREERUN = 0x4
};

namespace engine
{
    namespace cg
    {
        void(__fastcall* draw2d)(int) = engine::address::get<void(__fastcall*)(int)>(0x7FF771F1F910);
        void(__fastcall* draw2dinternal)(int) = engine::address::get<void(__fastcall*)(int)>(0x7FF771F1F920);
        void(__fastcall* boldgamemessagecenter)(int, const char*) = engine::address::get<void(__fastcall*)(int, const char*)>(0x7FF7721D4C80);
        void draw2dhook(int clientnum)
        {
            std::chrono::steady_clock steady_clock;
            static std::chrono::steady_clock::time_point delta = steady_clock.now();

            // If the player is in a game update once every 30 seconds else update once every 5 seconds.
            if(std::chrono::duration_cast<std::chrono::seconds>(steady_clock.now() - delta) >= ((com::isingame() == true) ? std::chrono::seconds(30) : std::chrono::seconds(5)))
            {
                auto presence = discord::presence::get();

                if(com::isingame())
                {
                    if(presence.startTimestamp == 0) {
                        presence.startTimestamp = time(0);
                    }

                    presence.partySize = engine::lobbysession::getclientcount(1, 0);
                    if(presence.partySize <= 0)
                    {
                        presence.partySize = 1;
                    }

                    presence.partyMax = engine::lobbysession::getmaxclients(0);

                    int lobbymode = *(int*)(engine::lobbysession::getsession(1) + 0x8);
                    switch(lobbymode)
                    {
                    case LOBBY_MODE_PUBLIC:
                        presence.partyMax = engine::lobbysession::getmaxclients(1);

                    case LOBBY_MODE_CUSTOM:
                    case LOBBY_MODE_ARENA:
                        try
                        {
                            // Zombies
                            if(engine::com::ismode(0))
                            {
                                std::string details = config::get()["lobby_mode"]["public"]["zombies"]["solo"]["details"].get<std::string>();
                                std::string state = config::get()["lobby_mode"]["public"]["zombies"]["solo"]["state"].get<std::string>();

                                if (presence.partySize > 1)
                                {
                                    details = config::get()["lobby_mode"]["public"]["zombies"]["party"]["details"].get<std::string>();
                                    state = config::get()["lobby_mode"]["public"]["zombies"]["party"]["state"].get<std::string>();
                                }

                                presence.details = parser::parse(
                                    details, 
                                    128
                                ).c_str();
                                presence.state = parser::parse(
                                    state, 
                                    128
                                ).c_str();
                            }
                            
                            // Multiplayer
                            if(engine::com::ismode(1))
                            {
                                std::string details = config::get()["lobby_mode"]["public"]["multiplayer"]["details"].get<std::string>();
                                std::string state = config::get()["lobby_mode"]["public"]["multiplayer"]["state"].get<std::string>();

                                presence.details = parser::parse(
                                    details, 
                                    128
                                ).c_str();
                                presence.state = parser::parse(
                                    state, 
                                    128
                                ).c_str();
                            }
                            
                            // Campaign
                            if(engine::com::ismode(2))
                            {
                                std::string details = config::get()["lobby_mode"]["public"]["campaign"]["details"].get<std::string>();
                                std::string state = config::get()["lobby_mode"]["public"]["campaign"]["state"].get<std::string>();

                                presence.details = parser::parse(
                                    details, 
                                    128
                                ).c_str();
    
                                presence.state = parser::parse(
                                    state, 
                                    128
                                ).c_str();
                            }
                        } catch(nlohmann::json::exception e) {  }
                        break;

                    case LOBBY_MODE_THEATER:
                        try
                        {
                            std::string details = config::get()["lobby_mode"]["theater"]["details"].get<std::string>();
                            std::string state = config::get()["lobby_mode"]["theater"]["state"].get<std::string>();

                            presence.details = parser::parse(
                                details, 
                                128
                            ).c_str();
    
                            presence.state = parser::parse(
                                state, 
                                128
                            ).c_str();
                        } catch(nlohmann::json::exception e) {  }
                        break;

                    case LOBBY_MODE_FREERUN:
                        try
                        {
                            std::string details = config::get()["lobby_mode"]["freerun"]["details"].get<std::string>();
                            std::string state = config::get()["lobby_mode"]["freerun"]["state"].get<std::string>();

                            presence.details = parser::parse(
                                details, 
                                128
                            ).c_str();
    
                            presence.state = parser::parse(
                                state, 
                                128
                            ).c_str();
                        } catch(nlohmann::json::exception e) { }
                        break;

                    default:
                        break;
                    }

                    presence.instance = 1;
                }
                else
                {
                    if(presence.startTimestamp != 0) {
                        presence.startTimestamp = 0;
                    }

                    // Add a check here to clear the mapname buffer as the game does not do this manualy.
                    // This allows us to add extra checks for if the player is in a usermap (custom map) for example.
                    // The check can look something like...
                    // if( engine::address::get<const char*>(0x0) != "" ) { memset(engine::address::get<const char*>(0x0), 32, ""); }
                    // Some additional reserach will have to be done before this is implemented to see if 
                    // anything references and requires it to be non null before doing it.

                    presence.state = "";
                    presence.details = "In the Main Menu";
                    presence.largeImageKey = "logo-black";
                    presence.largeImageText = "Call of Duty: Black Ops 3";                   
                    presence.partySize = 0;
                    presence.partyMax = 0;
                    presence.instance = 0;
                }

                discord::presence::set(presence);
                delta = steady_clock.now();
            }

            return engine::cg::draw2dinternal(clientnum);
        }
    }
}