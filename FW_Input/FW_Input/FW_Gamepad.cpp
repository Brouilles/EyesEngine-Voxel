/////////////////////////////INCLUDE/////////////////////////
#include "FW_Gamepad.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class FW_Gamepad
*/
FW_Gamepad::FW_Gamepad() : m_gamepadDetected(false)
{ }

FW_Gamepad::~FW_Gamepad()
{
	FW_Gamepad_deallocated();
}

/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
void FW_Gamepad::FW_Gamepad_initialized(HINSTANCE hInstance, HWND hwnd)
{
	/* DirectInput for keyboard Init */
	FW_Input *inputContext = new FW_Input();

	if (inputContext->FW_input_initialized(hInstance, hwnd))
	{
		//Create KeyBoard Device
		m_result = inputContext->FW_input_getDirectInputObject()->CreateDevice(GUID_Joystick, &m_gamepadDevice, NULL);
		delete inputContext;

		if (FAILED(m_result))
			m_debug.FW_warning("FW_Gamepad: directInputObject->CreateDevice Failed", FW_debugType::LOGS, FW_debugType::NOTHING);
		else {
			m_gamepadDetected = true;
			m_debug.FW_success("FW_Gamepad: directInputObject->CreateDevice Success", FW_debugType::LOGS, FW_debugType::NOTHING);

			//DataFormat
			m_result = m_gamepadDevice->SetDataFormat(&c_dfDIJoystick2);
			if (FAILED(m_result))
				m_debug.FW_warning("FW_Gamepad: m_keyboardDevice->SetDataFormat Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
			else
				m_debug.FW_success("FW_Gamepad: m_keyboardDevice->SetDataFormat Success", FW_debugType::LOGS, FW_debugType::NOTHING);

			//Cooperative Level
			m_result = m_gamepadDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if (FAILED(m_result))
				m_debug.FW_warning("FW_Gamepad: m_keyboardDevice->SetCooperativeLevel Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
			else
				m_debug.FW_success("FW_Gamepad: m_keyboardDevice->SetCooperativeLevel Success", FW_debugType::LOGS, FW_debugType::NOTHING);
		}
	}
	else
		m_debug.FW_error("FW_Gamepad: DirectInput8Create Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
}

void FW_Gamepad::FW_Gamepad_deallocated()
{
	m_gamepadDevice->Unacquire();
	m_gamepadDevice->Release();
	m_gamepadDevice = nullptr;
}

void FW_Gamepad::FW_Gamepad_acquire()
{
	if (m_gamepadDetected) {
		m_gamepadDevice->Acquire();
		m_gamepadDevice->GetDeviceState(sizeof(m_gamepadBuffer), (LPVOID)&m_gamepadBuffer);
	}
}

GAMEPADSTATE FW_Gamepad::FW_Gamepad_getGamepadBuffer()
{
	return m_gamepadBuffer;
}
