#include "discord/discord.h"
#include "engine/cg.h"
#include "engine/com.h"
#include "engine/enginetypes.h"
#include <chrono>



namespace engine
{
    namespace cg
    {
        void(__fastcall* draw2d)(int) = engine::address::get<void(__fastcall*)(int)>(0x7FF771F1F910);
        void(__fastcall* draw2dinternal)(int) = engine::address::get<void(__fastcall*)(int)>(0x7FF771F1F920);
        void(__fastcall* boldgamemessagecenter)(int, const char*) = engine::address::get<void(__fastcall*)(int, const char*)>(0x7FF7721D4C80);
        void draw2dhook(int clientnum)
        {
            std::chrono::steady_clock time;
            static std::chrono::steady_clock::time_point delta = time.now();

            if(std::chrono::duration_cast<std::chrono::seconds>(time.now() - delta) >= ((com::isingame() == true) ? std::chrono::seconds(30) : std::chrono::seconds(5)))
            {
                auto presence = discord::presence::get();

                // We need to move this to a seperate function such as discord::presence::update and we can call the discord functions directly instead.
                if(com::isingame())
                {
                    
                }
                else
                {

                }

                discord::presence::set(presence);
                delta = time.now();
            }

            return engine::cg::draw2dinternal(clientnum);
        }
    }
}