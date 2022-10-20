
#include <fstream>
#include <iostream>
#include <windows.h>
#include "config.h"

const char* DEFAULT_CONFIGURATION = "//======Parser Rules======// \
\n//  - ${ping} \
\n//  - ${place} \
\n//  - ${score} \
\n//  - ${kills} \
\n//  - ${assists} \
\n//  - ${deaths} \
\n//  - ${downs} \
\n//  - ${revives} \
\n//  - ${headshots} \
\n//  - ${mapname} \
\n//  - ${fastfile} \
\n//  - ${round} \
\n//  - ${username} \
\n//  - ${sessionmode} \
\n \
\n{ \
\n    \"remove-invalid-rules\": true, \
\n    \"presence\": { \
\n        \"zombies\": { \
\n            \"public\": { \
\n                \"solo\": { \
\n                    \"state\": \"Round ${round} | ${kills} kills | ${downs} downs\", \
\n                    \"details\": \"${sessionmode} : Playing Solo on ${mapname}\", \
\n                    \"show-timestamp\": true, \
\n                    \"show-playercount\": true \
\n                }, \
\n                \"party\": { \
\n                    \"state\": \"Round ${round} | ${kills} kills | ${downs} downs\", \
\n                    \"details\": \"${sessionmode} | In a Party on ${mapname}\", \
\n                    \"show-timestamp\": true, \
\n                    \"show-playercount\": true \
\n                } \
\n            }, \
\n            \"customs\": { \
\n                \"solo\": { \
\n                    \"state\": \"Round ${round} | ${kills} kills | ${downs} downs\", \
\n                    \"details\": \"${sessionmode} : Playing Solo on ${mapname}\", \
\n                    \"show-timestamp\": true, \
\n                    \"show-playercount\": true \
\n                }, \
\n                \"party\": { \
\n                    \"state\": \"Round ${round} | ${kills} kills | ${downs} downs\", \
\n                    \"details\": \"${sessionmode} | In a Party on ${mapname}\", \
\n                    \"show-timestamp\": true, \
\n                    \"show-playercount\": true \
\n                } \
\n            } \
\n        }, \
\n \
\n        \"multiplayer\": { \
\n            \"public\": { \
\n                \"state\": \"Playing ${gamemode} on ${mapname} : ${score}\", \
\n                \"details\": \"${kills} kills : ${deaths} deaths : ${assists} assists\", \
\n                \"show-timestamp\": true, \
\n                \"show-playercount\": true \
\n            }, \
\n            \"customs\": { \
\n                \"state\": \"Playing ${gamemode} on ${mapname} : ${score}\", \
\n                \"details\": \"${kills} kills : ${deaths} deaths : ${assists} assists\", \
\n                \"show-timestamp\": true, \
\n                \"show-playercount\": true \
\n            }, \
\n            \"arena\": { \
\n                \"state\": \"Playing ${gamemode} on ${mapname} : ${score}\", \
\n                \"details\": \"${kills} kills : ${deaths} deaths : ${assists} assists\", \
\n                \"show-timestamp\": true, \
\n                \"show-playercount\": true \
\n            } \
\n        }, \
\n \
\n        \"campaign\": { \
\n            \"public\": { \
\n                \"state\": \"${sessionmode} on ${mapname}\", \
\n                \"details\": \"${difficulty} difficulty : ${kills} kills\", \
\n                \"show-timestamp\": true, \
\n                \"show-playercount\": false \
\n            }, \
\n            \"customs\": { \
\n                \"state\": \"${sessionmode} on ${mapname}\", \
\n                \"details\": \"${difficulty} difficulty : ${kills} kills\", \
\n                \"show-timestamp\": true, \
\n                \"show-playercount\": false \
\n            } \
\n        }, \
\n        \"mainmenu\": { \
\n            \"state\": \"In the Main Menu\", \
\n            \"details\": \"\", \
\n            \"show-timestamp\": false, \
\n            \"show-playercount\": false \
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