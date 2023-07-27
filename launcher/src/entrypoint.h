// This just helps to hide some of the includes and defines
#ifndef _ENTRYPOINT_H
#define _ENTRYPOINT_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <tlhelp32.h>
#include <stdlib.h>

typedef DWORD (WINAPI * oDllStartup) (LPVOID);

#pragma warning(disable : 4152)
#endif /* _ENTRYPOINT_H*/