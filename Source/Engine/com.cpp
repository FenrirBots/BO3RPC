#include "Engine/Com.h"

bool(__cdecl* Com::IsInGame)() = GetAddress<bool(__cdecl*)()>(0x7FF773A58D20);
bool(__fastcall* Com::SessionMode::IsMode)(int) = GetAddress<bool(__fastcall*)(int)>(0x7FF773A07DD0);

// This returns a union (I hate unions)
uint64(__cdecl* Com::SessionMode::GetMode)() = GetAddress<uint64(__cdecl*)()>(0x7FF773A07790);