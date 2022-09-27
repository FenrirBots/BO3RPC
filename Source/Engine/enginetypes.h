#pragma once
#include <Windows.h>

typedef unsigned long long uint64;

template<typename T> T GetAddress(uint64 addr)
{
	return (T)((uint64)GetModuleHandle(0) + (addr - 0x7FF771910000));
}
