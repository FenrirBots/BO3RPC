#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <conio.h>
#include <stdlib.h>
#include <tlhelp32.h>

// TODO: Cleanup Code

void Log(int warningLevel, const char* message)
{
    if(warningLevel < 0 || warningLevel > 2)
    {
        return;
    }

    const char* warningLevels[] = {
        "[ ## ]",
        "[ !! ]",
        "[ !! ]"
    };
    
    _cprintf_s("%s: %s\n", warningLevels[warningLevel], message);
}

CHAR * GetDirectory() {
	DWORD s = 260 * sizeof(char);
	char* p = malloc(s);

	if(memset(p, '\0', s) == NULL) {
		return NULL;
	}

	GetCurrentDirectory(s, p);

	if(p[0] == '\0') {
		free(p);
		return NULL;
	}

	return p;
}

HANDLE * GetRemoteProcess(const char * processname)
{
  HANDLE         snapshot     = NULL;
  HANDLE *       process      = NULL;
  PROCESSENTRY32 processentry = { sizeof(PROCESSENTRY32) };
    
  if((snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == NULL)
  {
      return NULL;
  }
    
  if(Process32First(snapshot, &processentry))
  {
    do
    {
      if(_stricmp(processname, processentry.szExeFile) == 0)
      {
        process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processentry.th32ProcessID);
        break;
  	  }
    } while (Process32Next(snapshot, &processentry));
  }

  CloseHandle(snapshot);

  return process;
}

HMODULE GetRemoteProcessModule(HANDLE * process, const char * modulename)
{
  HMODULE       module      = NULL;
  HANDLE        snapshot    = NULL;
  MODULEENTRY32 moduleentry = { sizeof(MODULEENTRY32) };
	DWORD         processid   = 0;

	if((processid = GetProcessId(process)) == 0)
	{
		return NULL;
	}

  while((snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, processid)) == NULL)
  {
    if(GetLastError() == ERROR_BAD_LENGTH)
    {
      continue;
    }

    return NULL;
  }

  if(Module32First(snapshot, &moduleentry))
  {
    do
    {
      if(_stricmp(modulename, moduleentry.szModule) == 0)
      {
        module = moduleentry.hModule;
        break;
      }
    } while (Module32Next(snapshot, &moduleentry));
  }
    
  CloseHandle(snapshot);

  return module;
}

// I hate all this error checking...
int main(int argc, char ** argv)
{
	(void) argc;
	(void) argv;

	char * directory = GetDirectory();
	if(!directory) {
		return 0;
	}

	char * file = malloc(260 * sizeof(char));
	if(!file) {
		free(directory);
		return 0;
	}

	if(!memset(file, '\0', 260 * sizeof(char))) {
		free(directory);
		return 0;
	}

	strcat_s(file, 260, directory);
	strcat_s(file, 260, "\\");
	strcat_s(file, 260, "presence.dll"); // Replace with some config stuff later
	
	HANDLE process = GetRemoteProcess("blackops3.exe");
	if(!process) {
		_cprintf_s("%s: %lu\n", "Failed to get a handle to the process", GetLastError());
		free(directory);
		free(file);
		return 0;
	}

	LPVOID memory = VirtualAllocEx(process, 0, strlen(file) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if(!memory) {	
		_cprintf_s("%s: %lu\n", "Failed to allocate memory", GetLastError());
		free(directory);
		free(file);
		return 0;
	}

	if(WriteProcessMemory(process, memory, file, strlen(file) + 1, 0) == FALSE) {
		_cprintf_s("%s: %lu\n", "Failed to write memory", GetLastError());
		free(directory);
		free(file);
		return 0;
	}

	INT64 loadlibrary = (INT64)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA") - (INT64)GetModuleHandle("kernel32.dll") + (INT64)GetRemoteProcessModule(process, "kernel32.dll");
	HANDLE thread = CreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)loadlibrary, memory, 0, 0);
	if(thread == NULL) {
		_cprintf_s("%s: %lu\n", "Failed to create thread", GetLastError());
		free(directory);
		free(file);
		return 0;
	}

	WaitForSingleObject(thread, INFINITE);

	if(!VirtualFreeEx(process, memory, 0, MEM_RELEASE)) {
		_cprintf_s("%s: %lu\n", "Uh... VirtualFree failed? what now!", GetLastError());
		free(directory);
		free(file);
		return 0;
	}
	
	free(file);

	LPVOID memory2 = VirtualAllocEx(process, 0, strlen(directory) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if(!memory2) {	
		_cprintf_s("%s: %lu\n", "Failed to allocate memory", GetLastError());
		free(directory);
		return 0;
	}

	if(WriteProcessMemory(process, memory2, directory, strlen(directory) + 1, 0) == FALSE) {
		_cprintf_s("%s: %lu\n", "Failed to write memory", GetLastError());
		free(directory);
	}
	
	if(!LoadLibrary("presence.dll")) {
		_cprintf_s("%s: %lu", "Failed to load the library", GetLastError());
		free(directory);
		return 0;
	}

	INT64 dllstartup = (INT64)GetProcAddress(GetModuleHandle("presence.dll"), "DllStartup") - (INT64)GetModuleHandle("presence.dll") + (INT64)GetRemoteProcessModule(process, "presence.dll");
	HANDLE thread2 = CreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)dllstartup, memory2, 0, 0);
	if(thread2 == NULL) {
		_cprintf_s("%s: %lu\n", "Failed to create thread", GetLastError());
		free(directory);
		return 0;
	}

	WaitForSingleObject(thread2, INFINITE);

	if(!VirtualFreeEx(process, memory, 0, MEM_RELEASE)) {
		_cprintf_s("%s: %lu\n", "Uh... VirtualFree failed? what now!", GetLastError());
		free(directory);
		return 0;
	}

	free(directory);

	//	Load the dll
	// VirtualAllocEx        (hProcess, 0, sizeof(a), 0, 0);
	// WriteProcessMemory    (hProcess, k, a, sizeof(a), 0);
	// GetRemoteProcessModule(hProcess, "kernel32");
	// CreateRemoteThreadEx  (hProcess, 0, 0, (LPTHREAD_START_ROUTINE)m, k, 0, 0, 0);
	// WaitOnSingleObject    (hThread, INFINITE); // Wait on the thread to finish so we can call VirtualFree without getting a STATUS_STACK_BUFFER_OVERRUN error
	// VirtualFreeEx         (hProcess, k, 0, 0);

	//	Call the dll
	// VirtualAllocEx        (hProcess, 0, 0, 0, 0);
	// WriteProcessMemory    (hProcess, p, , 0, 0);
	// GetRemoteProcessModule(hProcess, 0);
	// CreateRemoteThreadEx  (hProcess, 0, 0, NULL, NULL, 0, 0, 0);
	// WaitOnSingleObject    (hThread, INFINITE); // Wait on the thread to finish so we can call VirtualFree without getting a STATUS_STACK_BUFFER_OVERRUN error
	// VirtualFreeEx         (hProcess, 0, 0, 0);

	return TRUE;
}