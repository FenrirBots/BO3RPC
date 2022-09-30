#include "engine/com.h"
#include "engine/enginetypes.h"


namespace engine
{
    namespace com
    {
        bool(__cdecl* isingame)() = engine::address::get<bool(__cdecl*)()>(0x7FF773A58D20);
        bool(__fastcall* ismode)(int) = engine::address::get<bool(__fastcall*)(int)>(0x7FF773A07DD0);

        namespace sessionmode
        {
            unsigned long long(__cdecl* getmode)() = engine::address::get<unsigned long long(__cdecl*)()>(0x7FF773A07790);
        }
    }
}
