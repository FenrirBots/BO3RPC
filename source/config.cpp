
#include <fstream>
#include <iostream>
#include <windows.h>
#include "config.h"

const char* DEFAULT_CONFIGURATION = "{ \
\n    \"lobby_mode\": \
\n    { \
\n        \"public\": \
\n        { \
\n            \"multiplayer\": \
\n            { \
\n                \"state\": \"\", \
\n                \"details\": \"\" \
\n            }, \
\n            \"zombies\": \
\n            { \
\n                \"solo\": \
\n                { \
\n                    \"state\": \"Playing Solo\", \
\n                    \"details\": \"Round ${round} on ${mapname}\" \
\n                }, \
\n                \"party\": \
\n                { \
\n                    \"state\": \"In a Party\", \
\n                    \"details\": \"Round ${round} on ${mapname}\" \
\n                } \
\n            }, \
\n            \"campaign\": \
\n            { \
\n                \"state\": \"\", \
\n                \"details\": \"\" \
\n            } \
\n        }, \
\n        \"theater\": \
\n        { \
\n            \"state\": \"In Theater Mode\", \
\n            \"details\": \"Watching ${videoname}\" \
\n        }, \
\n        \"arena\": \
\n        { \
\n            \"state\": \"\", \
\n            \"details\": \"\" \
\n        }, \
\n        \"freerun\": \
\n        { \
\n            \"state\": \"\", \
\n            \"details\": \"\" \
\n        } \
\n    } \
\n}";


namespace config
{
    void load()
    {
        try
        {
            // I hate this
            std::fstream file("presence.json", std::fstream::binary | std::fstream::in);
            if(!file || file.peek() == std::fstream::traits_type::eof())
            {
                file.close();
                file.clear();
                file.open("presence.json", std::fstream::beg  | std::fstream::binary | std::fstream::out);
                if(!file)
                {
                    return;
                }

                file << DEFAULT_CONFIGURATION;
                file.flush();
                file.close();

                file.open("presence.json", std::fstream::binary | std::fstream::in);
                if(!file)
                {
                    return;
                }
            }

            config::data = nlohmann::json::parse(file, nullptr, true, true);
    
            file.flush();
            file.close();
        }
        catch(nlohmann::json::exception e)
        {
            OutputDebugStringA(e.what());
        }
        catch(const std::exception& e)
        {
            OutputDebugStringA(e.what());
        }
    }

    nlohmann::json get()
    {
        return data;
    }

    nlohmann::json data;
}