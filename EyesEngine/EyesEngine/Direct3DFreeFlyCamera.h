#ifndef DIRECT3DFREEFLYCAMERA_H_INCLUDED
#define DIRECT3DFREEFLYCAMERA_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>

#define _USE_MATH_DEFINES
#include "cmath"

#include "Math.cpp"
#include "../../FW_Input/FW_Input/FW_Keyboard.h"
#include "../../FW_Input/FW_Input/FW_Mouse.h"
#include "../../FW_Input/FW_Input/FW_Input.h"
#include "../EyesEngine_Universal/GameTime.h"
/////////////////////////////////////////////////////////////

struct CAMERAFREEFLYVECTOR {
	D3DXVECTOR3 defaultForward, defaultRight, camTarget, camUp, camPosition;
	D3DXVECTOR3 camForward, camRight, camHeight;
	D3DXMATRIX camRotationMatrix, camView;
	float moveLeftRight, moveBackForward, moveHeightDown, speed;
	float yaw, pitch; //In Radian
};

class Direct3DFreeFlyCamera
{
public:
	Direct3DFreeFlyCamera();
	~Direct3DFreeFlyCamera();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Initiazed Camera and Matrix
	/// </summary>
	/////////////////////////////////////////////////////////////
	bool Direct3DFreeFlyCamera_initialized(LPDIRECT3DDEVICE9 D3DDevice);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Update D3DDevice and update Matrix
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Direct3DFreeFlyCamera_update(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, float elapsedGameTime, FW_Keyboard *keyboard, FW_Mouse *mouse, float mouse_x, float mouse_y);

	//Methods
	void Direct3DFreeFlyCamera_yaw(float value);
	void Direct3DFreeFlyCamera_pitch(float value);

	D3DXVECTOR3 Direct3DFreeFlyCamera_getPosition()const;
	D3DXVECTOR3 Direct3DFreeFlyCamera_getLookAtVector()const;
	D3DXMATRIX Direct3DFreeFlyCamera_getViewMatrix()const;
	D3DXMATRIX Direct3DFreeFlyCamera_getProjectionMatrix()const;

private:
	HRESULT m_result;
	CAMERAFREEFLYVECTOR m_cameraVector;
};

#endif