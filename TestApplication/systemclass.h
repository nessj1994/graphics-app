#pragma once

//Win32 Lean and mean to remove unnecessary API's
#define WIN32_LEAN_AND_MEAN
//include windows.h for ability to create and destroy the application
#include "windows.h"

//MY CLASSES
#include "input.h"
#include "graphics.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();


	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private: 
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();


	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Input* m_pInput;
	Graphics* m_pGraphics;

};


//Function Prototype
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//GLOBAL
static SystemClass* ApplicationHandle = 0;

