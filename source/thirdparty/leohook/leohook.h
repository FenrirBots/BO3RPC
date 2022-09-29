// https://github.com/hoangprod/LeoSpecial-VEH-Hook

#pragma once
#include <Windows.h>
#include <stdio.h>
#include <iostream>

#ifdef _WIN64
#define XIP Rip
#else
#define XIP Eip
#endif



class LeoHook {
public:
	static bool Hook(uintptr_t og_fun, uintptr_t hk_fun);
	static bool Unhook();

private:
	static uintptr_t og_fun;
	static uintptr_t hk_fun;
	static PVOID VEH_Handle;
	static DWORD oldProtection;

	static bool AreInSamePage(const uint8_t* Addr1, const uint8_t* Addr2);
	static LONG WINAPI LeoHandler(EXCEPTION_POINTERS* pExceptionInfo);
};