#pragma once
#include <Windows.h>


// Why am i like this
namespace engine
{
    namespace address
    {
        template<typename T> T get(unsigned long long address)
        {
        	return reinterpret_cast<T>((reinterpret_cast<unsigned long long>(GetModuleHandle(0)) + (address - 0x7FF771910000)));
        }
    }
}