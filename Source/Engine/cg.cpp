#include "Engine/CG.h"

void(__fastcall* CG::Draw2D)(int) = GetAddress<void(__fastcall*)(int localClientNumber)>(0x7FF771F1F910);
void(__fastcall* CG::Draw2DInternal)(int) = GetAddress<void(__fastcall*)(int localClientNumber)>(0x7FF771F1F920);
void(__fastcall* CG::BoldGameMessageCenter)(int, const char*) = GetAddress<void(__fastcall*)(int localClientNumber, const char* message)>(0x7FF7721D4C80);