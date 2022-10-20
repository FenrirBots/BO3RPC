#pragma once
#include <Windows.h>

namespace threads
{
    DWORD WINAPI attach(LPVOID);
    DWORD WINAPI detach(LPVOID);
}