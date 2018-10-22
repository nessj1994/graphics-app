#include "systemclass.h"

SystemClass::SystemClass()
{
	m_pInput = 0;
	m_pGraphics = 0;
}

SystemClass::SystemClass(const SystemClass& other)
{

}

SystemClass::~SystemClass()
{

}

bool SystemClass::Initialize()
{
	//Create necessary variables to initialize the window
	int m_nScreenHeight, m_nScreenWidth;
	bool m_bResult;

	//Initialize the height and width of the screen before using variables
	m_nScreenHeight = 0;
	m_nScreenWidth = 0;

	//Initialize the windows API
	InitializeWindows(m_nScreenHeight, m_nScreenWidth);

	//Create Input object to handle any user interaction
	m_pInput = new Input;
	if (!m_pInput)
	{
		return false;
	}

	//Initialize input object
	m_pInput->Initialize();

	//Create Graphics object to handle rendering for this application
	m_pGraphics = new Graphics;
	if (!m_pGraphics)
	{
		return false;
	}

	//Initialize the graphics object
	m_bResult = m_pGraphics->Initialize(m_nScreenHeight, m_nScreenWidth, m_hwnd);
	if (!m_bResult)
	{
		return false;
	}

	return true;
}


void SystemClass::Shutdown()
{
	//Release graphics object
	if (m_pGraphics)
	{
		m_pGraphics->Shutdown();
		delete m_pGraphics;
		m_pGraphics = 0;
	}

	//Release the input object
	if (m_pInput)
	{
		delete m_pInput;
		m_pInput = 0;
	}

	//Close the window
	ShutdownWindows();

	return;
}

void SystemClass::Run()
{
	MSG msg;
	bool m_bDone, m_bResult;

	//Initialize the message structure;
	ZeroMemory(&msg, sizeof(msg));

	//Loop until there is a quit message from the window or the user;
	m_bDone = false;

	while (!m_bDone)
	{
		//Handle windows messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//Check if windows has signalled to end the application
		if (msg.message == WM_QUIT)
		{
			m_bDone = true;
		}
		else
		{
			//Process Frame
			m_bResult = Frame();
			if (!m_bResult)
			{
				m_bDone = true;
			}
		}
	}
	return;
}

bool SystemClass::Frame()
{
	bool m_bResult;

	//Check if the user pressed escape to exit the application
	if (m_pInput->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	//process frame for graphics object
	m_bResult = m_pGraphics->Frame();
	if (!m_bResult)
	{
		return false;
	}
	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		//Check if a key has been pressed
	case WM_KEYDOWN:
	{
		//If a key had been pressed send it to the input object to record the information
		m_pInput->KeyDown((unsigned int)wparam);
		return 0;
	}
	case WM_KEYUP:
	{
		//If a key was released sent it to the input object to record the information
		m_pInput->KeyUp((unsigned int)wparam);
		return 0;
	}
	default:
	{
		//Any other messages will not be used
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

void SystemClass::InitializeWindows(int& screenHeight, int& screenWidth)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int m_nPosX, m_nPosY;

	//Get an external pointer to the this object
	ApplicationHandle = this;
}