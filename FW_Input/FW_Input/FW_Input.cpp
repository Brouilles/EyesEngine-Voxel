/////////////////////////////INCLUDE/////////////////////////
#include "FW_Input.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class FW_Input
*/

FW_Input::FW_Input()
{	}

FW_Input::~FW_Input()
{
	FW_input_deallocated();
}

/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
bool FW_Input::FW_input_initialized(HINSTANCE hInstance, HWND hwnd)
{
	/* DirectInput Create */
	m_result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInputObject, NULL);
	if (FAILED(m_result))
	{
		m_debug.FW_warning("FW_Input: DirectInput8Create Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
		return false;
	}
	else
	{
		m_debug.FW_success("FW_Input: DirectInput8Create", FW_debugType::LOGS, FW_debugType::NOTHING);
		return true;
	}
}

void FW_Input::FW_input_deallocated()
{
	m_directInputObject->Release();
	m_directInputObject = nullptr;
}

LPDIRECTINPUT8 FW_Input::FW_input_getDirectInputObject()const
{
	return m_directInputObject;
}