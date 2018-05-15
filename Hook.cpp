#include "Hook.h"
#include "stdafx.h"

void SetHook(HWND m_hWnd)
{
	HINSTANCE hInst;
	hInst = LoadLibrary(L".\\Dll\\GHookDLL.dll");
	typedef void(*SetHookProc)(HWND hWnd);
	SetHookProc SetHook = (SetHookProc)GetProcAddress(hInst, "SetHook");
	SetHook(m_hWnd);
}

void StopHook(HWND m_hWnd)
{
	HINSTANCE hInst;
	hInst = LoadLibrary(L"GHookDLL.dll");
	
	typedef void(*StopHookProc)(HWND hWnd);
	StopHookProc StopHook = (StopHookProc)GetProcAddress(hInst, "StopHook");
	StopHook(m_hWnd);

}