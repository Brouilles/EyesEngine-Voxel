#pragma once
#ifndef FW_GAMEPAD_H_INCLUDED
#define FW_GAMEPAD_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <iostream>
#include <string>
#include <dinput.h>
#include "../../FW_Debug/FW_Debug/FW_Debug.h"

#include "FW_Input.h"
/////////////////////////////////////////////////////////////

typedef struct GAMEPADSTATE {
	LONG lX;			// Axe X, g�n�ralement Gauche-Droite du Stick
	LONG lY;			// Axe Y, g�n�ralement Haut-Bas du Stick
	LONG lZ;			// Axe Z, troisi�me axe, les gaz pour certains joysticks
	LONG lRx;			// Rotation de l'axe X
	LONG lRy;			// Rotation de l'axe Y
	LONG lRz;			// Rotation de l'axe Z
	LONG rglSlider[2];		// Deux axes suppl�mentaires
	DWORD rgdwPOV[4];		// Controlleur de point de vue
	BYTE rgbButtons[128];	// Etat des bouttons
	LONG lVX;			// Vitesse de l'axe X
	LONG lVY;			// Vitesse de l'axe Y
	LONG lVZ;			// Vitesse de l'axe Z
	LONG lVRx;			// Vitesse de rotation de l'axe X
	LONG lVRy;			// Vitesse de rotation de l'axe Y
	LONG lVRz;			// Vitesse de rotation de l'axe Z
	LONG rglVSlider[2];		// Vitesse des axes suppl�mentaires
	LONG lAX;			// Acc�l�ration de l'axe X
	LONG lAY;			// Acc�l�ration de l'axe Y
	LONG lAZ;			// Acc�l�ration de l'axe Z
	LONG lARx;			// Acc�l�ration de la rotation l'axe X
	LONG lARy;			// Acc�l�ration de la rotation l'axe Y
	LONG lARz;			// Acc�l�ration de la rotation l'axe Z
	LONG rglASlider[2];		// Acc�l�ration des axes suppl�mentaires
	LONG lFX;			// Force de l'axe X
	LONG lFY;			// Force de l'axe Y
	LONG lFZ;			// Force de l'axe Z
	LONG lFRx;			// Couple de l'axe X
	LONG lFRy;			// Couple de l'axe Y
	LONG lFRz;			// Couple de l'axe Z
	LONG rglFSlider[2];		// Force des axes suppl�mentaires
};

class FW_Gamepad
{
public:
	FW_Gamepad();
	~FW_Gamepad();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Initialize memory. Get keyboard input.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void FW_Gamepad_initialized(HINSTANCE hInstance, HWND hwnd);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Deallocate memory.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void FW_Gamepad_deallocated();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Acquire input and device state. Update KEYDOWN buffer.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void FW_Gamepad_acquire();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Return m_keyboardBuffer[256].
	/// </summary>
	/////////////////////////////////////////////////////////////
	GAMEPADSTATE FW_Gamepad_getGamepadBuffer();

private:
	HRESULT m_result;
	bool m_gamepadDetected;
	FW_Debug m_debug;

	LPDIRECTINPUTDEVICE8  m_gamepadDevice;
	GAMEPADSTATE m_gamepadBuffer;
};

#endif