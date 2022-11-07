#include "thirdparty/t7api/t7api.h"

const char*(__fastcall* t7api::dvar::getstring)(ulong) =
	reinterpret_cast<const char*(__fastcall*)(ulong)>(reinterpret_cast<unsigned long long>(GetModuleHandle(0)) + (0x7FF773BCFFF0 - 0x7FF771910000));