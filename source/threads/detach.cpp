#include "threads/threads.h"
#include <winternl.h>
EXTERN_C IMAGE_DOS_HEADER __ImageBase;


DWORD WINAPI threads::detach(LPVOID /* lpvReserved */)
{
    FreeLibraryAndExitThread((HINSTANCE)&__ImageBase, 0);
}