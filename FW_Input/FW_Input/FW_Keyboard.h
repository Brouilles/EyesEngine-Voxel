#ifndef FW_KEYBOARD_H_INCLUDED
#define FW_KEYBOARD_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <iostream>
#include <string>
#include <dinput.h>
#include "../../FW_Debug/FW_Debug/FW_Debug.h"

#include "FW_Input.h"
/////////////////////////////////////////////////////////////

#define KEYDOWN( buffer, key ) ( buffer[key] & 0x80 )

class FW_Keyboard
{
public:
	FW_Keyboard();
	~FW_Keyboard();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Initialize memory. Get keyboard input.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void FW_keyboard_initialized(HINSTANCE hInstance, HWND hwnd);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Deallocate memory.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void FW_keyboard_deallocated();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Acquire input and device state. Update KEYDOWN buffer.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void FW_keyboard_acquire();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Return m_keyboardBuffer[256].
	/// </summary>
	/////////////////////////////////////////////////////////////
	char *FW_keyboard_getKeyboardBuffer();

private:
	HRESULT m_result;
	FW_Debug m_debug;

	LPDIRECTINPUTDEVICE8 m_keyboardDevice;
	char m_keyboardBuffer[256];
};

#endif