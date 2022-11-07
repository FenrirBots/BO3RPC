#include "thirdparty/t7api/t7api.h"

const char* (__fastcall* t7api::ui::safetranslatestring)(const char*) = 
    reinterpret_cast<const char*(__fastcall*)(const char*)>(reinterpret_cast<unsigned long long>(GetModuleHandleA(0)) + (0x7FF773B9F7B0 - 0x7FF771910000));