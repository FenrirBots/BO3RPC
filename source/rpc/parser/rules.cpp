#include "update.h"
#include "parser/rules.h"
#include "thirdparty/t7api/t7api.h"

#pragma region score_s
std::string parser::callbacks::ping()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return std::to_string(*reinterpret_cast<int*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x280));
}
std::string parser::callbacks::place()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return std::to_string(*reinterpret_cast<int*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x280 + 0x8));
}
std::string parser::callbacks::score()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return std::to_string(*reinterpret_cast<int*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x280 + 0xC));
}
std::string parser::callbacks::kills()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return std::to_string(*reinterpret_cast<int*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x280 + 0x10));
}
std::string parser::callbacks::assists()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return std::to_string(*reinterpret_cast<int*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x280 + 0x14));
}
std::string parser::callbacks::deaths()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return std::to_string(*reinterpret_cast<int*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x280 + 0x18));
}
std::string parser::callbacks::downs()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return std::to_string(*reinterpret_cast<int*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x280 + 0x40));
}
std::string parser::callbacks::revives()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return std::to_string(*reinterpret_cast<int*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x280 + 0x44));
}
std::string parser::callbacks::headshots()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return std::to_string(*reinterpret_cast<int*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x280 + 0x48));
}
#pragma endregion


// Fix an issue where the mapname on anything other than zombies can be empty or wrong
std::string parser::callbacks::mapname()
{
    if(reinterpret_cast<const char*>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF78AD517A2 - 0x7FF771910000)) == std::string(""))
    {
        return "usermaps";
    }

    return reinterpret_cast<const char*>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF78AD517A2 - 0x7FF771910000));
}

std::string parser::callbacks::fastfile()
{
    return reinterpret_cast<const char*>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF77AD1E5E8 - 0x7FF771910000));
}

std::string parser::callbacks::username()
{
    if(g_entities == 0)
    {
        return "0";
    }

    return reinterpret_cast<const char*>(*reinterpret_cast<unsigned long long*>(g_entities + 0x250) + 0x16BF8 + 0x2C);
}

// Returns the address to g_entities, used for debugging.
std::string parser::callbacks::gentities()
{
    char string[128];
    sprintf_s(string, ARRAYSIZE(string), "[T7RPC]: 0x%llX", g_entities);
    return string;
}

std::string parser::callbacks::round()
{
    unsigned long long matchstate = 0;
    matchstate = t7api::g::getmatchstate();

    if(matchstate != 0)
    {
        int round = 0;
        round = *(int*)(matchstate + 0x18C);

        return std::to_string(round);
    }
    
    return "0";
}

std::string parser::callbacks::sessionmode()
{
    switch(t7api::com::sessionmode::getmode())
    {
        case MODE_ZOMBIES:
            return "Zombies";
        case MODE_MULTIPLAYER:
            return "Multiplayer";
        case MODE_CAMPAIGN:
            return "Campaign";
    }
    return "Invalid Mode";
}

/*
enum DIFFICULTIES : __int32
{
  DIFFICULTY_EASY = 0x0,
  DIFFICULTY_MEDIUM = 0x1,
  DIFFICULTY_HARD = 0x2,
  DIFFICULTY_VETERAN = 0x3,
  DIFFICULTY_FU = 0x4,
};
*/

const char* m_Difficulties[5] = {"Recruit", "Regular", "Hardened", "Veteran", "Realistic"};

std::string parser::callbacks::difficulty()
{
    unsigned long long controllerindex = t7api::com::localclient::getcontrollerindex(0);
    unsigned long long difficulty = t7api::settings::getuint("g_skilltype", controllerindex);

    if(difficulty < 5)
        return m_Difficulties[difficulty];
 
    return "UNKNOWN";
}