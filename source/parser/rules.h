#pragma once
#include <string>

namespace parser
{
    namespace callbacks
    {
        std::string ping();
        std::string place();
        std::string score();
        std::string kills();
        std::string assists();
        std::string deaths();
        std::string downs();
        std::string revives();
        std::string headshots();

        std::string username();
        std::string mapname();
        std::string fastfile();
        std::string round();
        std::string sessionmode();

        std::string gentities();
        /*
        std::string friendcode();
        std::string username();
        std::string fastfile();
        std::string mapname();
        std::string round();
        std::string weapon_primary();
        std::string weapon_secondary();
        std::string weapon_mulekick();
        */
    }
}