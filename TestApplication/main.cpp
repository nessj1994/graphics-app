//*******************************************//
//File: main.cpp
//Purpose: House the main entry point for the application
//Creator: Jordan Ness
//Date: 10/21/2018
//*******************************************//

#include "systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, PSTR pScmdline, int iCmdshow)
{
	SystemClass* m_pSystem;
	bool m_bResult;

	//Create System Object
	m_pSystem = new SystemClass;
	if (!m_pSystem)
	{
		return 0;
	}

	//Initialize and run
	m_bResult = m_pSystem->Initialize();
	if (m_bResult)
	{
		m_pSystem->Run();
	}

	//Shutdown and release system object
	m_pSystem->Shutdown();
	delete m_pSystem;
	m_pSystem = 0;

	return 0;
}