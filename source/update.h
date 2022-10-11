#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <dxgi.h>
#pragma comment(lib, "dxgi.lib")

extern HRESULT (__stdcall* present)(IDXGISwapChain*, UINT, UINT);
HRESULT WINAPI update(IDXGISwapChain*, UINT, UINT);

extern unsigned long long g_entities;