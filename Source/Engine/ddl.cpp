#include "Engine/DDL.h"

bool(__fastcall* DDL::MoveToName)(uint64, uint64, const char*) = GetAddress<bool(__fastcall*)(uint64, uint64, const char*)>(0x7FF773E33020);
unsigned int(__fastcall* DDL::GetUInt)(uint64, uint64) = GetAddress<unsigned int(__Fastcall*)(uint64, uint64)>(0x7FF773E32AF0);