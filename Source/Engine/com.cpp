#include "Engine/Com.h"

bool (__cdecl* Com::IsInGame)() = GetAddress<bool(__cdecl*)()>(0x7FF773A58D20);