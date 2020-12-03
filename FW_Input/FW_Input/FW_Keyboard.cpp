/////////////////////////////INCLUDE/////////////////////////
#include "FW_Keyboard.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class FW_Keyboard
*/
FW_Keyboard::FW_Keyboard()
{ }

FW_Keyboard::~FW_Keyboard()
{
	FW_keyboard_deallocated();
}

/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
void FW_Keyboard::FW_keyboard_initialized(HINSTANCE hInstance, HWND hwnd)
{
	/* DirectInput for keyboard Init */
	FW_Input *inputContext = new FW_Input();

	if (inputContext->FW_input_initialized(hInstance, hwnd))
	{
		//Create KeyBoard Device
		m_result = inputContext->FW_input_getDirectInputObject()->CreateDevice(GUID_SysKeyboard, &m_keyboardDevice, NULL);
		delete inputContext;

		if (FAILED(m_result))
			m_debug.FW_error("FW_Keyboard: directInputObject->CreateDevice Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
		else
			m_debug.FW_success("FW_Keyboard: directInputObject->CreateDevice Success", FW_debugType::LOGS, FW_debugType::NOTHING);

		//DataFormat
		m_result = m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(m_result))
			m_debug.FW_error("FW_Keyboard: m_keyboardDevice->SetDataFormat Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
		else
			m_debug.FW_success("FW_Keyboard: m_keyboardDevice->SetDataFormat Success", FW_debugType::LOGS, FW_debugType::NOTHING);

		//Cooperative Level
		m_result = m_keyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(m_result))
			m_debug.FW_error("FW_Keyboard: m_keyboardDevice->SetCooperativeLevel Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
		else
			m_debug.FW_success("FW_Keyboard: m_keyboardDevice->SetCooperativeLevel Success", FW_debugType::LOGS, FW_debugType::NOTHING);
	}
	else
		m_debug.FW_error("FW_Keyboard: DirectInput8Create Failed", FW_debugType::LOGS, FW_debugType::WINDOW);
}

void FW_Keyboard::FW_keyboard_deallocated()
{
	m_keyboardDevice->Unacquire();
	m_keyboardDevice->Release();
	m_keyboardDevice = nullptr;
}

void FW_Keyboard::FW_keyboard_acquire()
{
	m_keyboardDevice->Acquire();
	m_keyboardDevice->GetDeviceState(sizeof(m_keyboardBuffer), (LPVOID)&m_keyboardBuffer);
}

char *FW_Keyboard::FW_keyboard_getKeyboardBuffer()
{
	return m_keyboardBuffer;
}