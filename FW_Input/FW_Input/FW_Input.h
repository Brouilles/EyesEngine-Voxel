#ifndef FW_INPUT_H_INCLUDED
#define FW_INPUT_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <iostream>
#include <string>
#include <dinput.h>
#include "../../FW_Debug/FW_Debug/FW_Debug.h"
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
/// <summary> 
///		Direct Input option, version and buffer define.
/// </summary>
/////////////////////////////////////////////////////////////
#define DIRECTINPUT_VERSION 0x0800

class FW_Input
{
public:
	FW_Input();
	~FW_Input();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Initilize LPDIRECTINPUT8 object with direct input 8
	/// </summary>
	/////////////////////////////////////////////////////////////
	bool FW_input_initialized(HINSTANCE, HWND);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Deallocate memory.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void FW_input_deallocated();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Get LPDIRECTINPUT8 object. Call once initialize class.
	/// </summary>
	/////////////////////////////////////////////////////////////
	LPDIRECTINPUT8 FW_input_getDirectInputObject()const;

private:
	HRESULT m_result;
	FW_Debug m_debug;
	LPDIRECTINPUT8 m_directInputObject;
};

#endif