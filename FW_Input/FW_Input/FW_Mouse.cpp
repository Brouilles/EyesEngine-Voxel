/////////////////////////////INCLUDE/////////////////////////
#include "FW_Mouse.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class FW_Mouse
*/
FW_Mouse::FW_Mouse()
{ }

FW_Mouse::~FW_Mouse()
{ }

/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
void FW_Mouse::FW_Mouse_initialized(HINSTANCE hInstance, HWND hwnd)
{
	/* DirectInput for mouse Init */
	FW_Input *inputContext = new FW_Input();

	if (inputContext->FW_input_initialized(hInstance, hwnd))
	{
		//Create Mouse Device
		m_result = inputContext->FW_input_getDirectInputObject()->CreateDevice(GUID_SysMouse, &m_mouseDevice, NULL);
		delete inputContext;

		if (FAILED(m_result))
			m_debug.FW_error("FW_Mouse: directInputObject->CreateDevice Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
		else
			m_debug.FW_success("FW_Mouse: directInputObject->CreateDevice Success", FW_debugType::LOGS, FW_debugType::NOTHING);

		//DataFormat
		m_result = m_mouseDevice->SetDataFormat(&c_dfDIMouse);

		if (FAILED(m_result))
			m_debug.FW_error("FW_Mouse: m_mouseDevice->SetDataFormat Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
		else
			m_debug.FW_success("FW_Mouse: m_mouseDevice->SetDataFormat Success", FW_debugType::LOGS, FW_debugType::NOTHING);
	}
	else
		m_debug.FW_error("FW_Mouse: DirectInput8Create Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
}

void FW_Mouse::FW_Mouse_deallocated()
{
	m_mouseDevice->Unacquire();
	m_mouseDevice->Release();
	m_mouseDevice = nullptr;
}

void FW_Mouse::FW_Mouse_acquire()
{
	m_mouseDevice->Acquire();
	m_mouseDevice->GetDeviceState(sizeof(m_mouseBuffer), (LPVOID)&m_mouseBuffer);
}

MOUSESTATE FW_Mouse::FW_Mouse_getMouseBuffer()
{
	return m_mouseBuffer;
}