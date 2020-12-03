/////////////////////////////INCLUDE/////////////////////////
#include "Direct3DFreeFlyCamera.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
** Class Direct3DFreeFlyCamera
*/

Direct3DFreeFlyCamera::Direct3DFreeFlyCamera()
{}

Direct3DFreeFlyCamera::~Direct3DFreeFlyCamera()
{}

bool Direct3DFreeFlyCamera::Direct3DFreeFlyCamera_initialized(LPDIRECT3DDEVICE9 D3DDevice)
{
	float aspect = 1.333f;
	float nearClip = 1.0f;
	float farClip = 10000.0f;

	//Setup MatrixPerspective
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4.0f, aspect, nearClip, farClip);
	D3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	//Vector position
	m_cameraVector.defaultForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_cameraVector.defaultRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_cameraVector.camForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_cameraVector.camRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_cameraVector.camPosition = D3DXVECTOR3(0.0f, 5.0f, -8.0f);
	m_cameraVector.camTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_cameraVector.camUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_cameraVector.moveLeftRight = 0.0f;
	m_cameraVector.moveBackForward = 0.0f;
	m_cameraVector.moveHeightDown = 0.0f;
	m_cameraVector.speed = 18.0f;

	return true;
}

void Direct3DFreeFlyCamera::Direct3DFreeFlyCamera_update(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, float elapsedGameTime, FW_Keyboard *keyboard, FW_Mouse *mouse, float mouse_x, float mouse_y)
{
	//Mouse
	Direct3DFreeFlyCamera_yaw(mouse_x * 0.001f);
	Direct3DFreeFlyCamera_pitch(mouse_y * 0.001f);

	// Keyboard - QWERTY
	if (KEYDOWN(keyboard->FW_keyboard_getKeyboardBuffer(), DIK_W)) //Foward
	{
		m_cameraVector.moveBackForward += m_cameraVector.speed * elapsedGameTime;
	}
	if (KEYDOWN(keyboard->FW_keyboard_getKeyboardBuffer(), DIK_S)) //Back
	{
		m_cameraVector.moveBackForward -= m_cameraVector.speed * elapsedGameTime;
	}
	if (KEYDOWN(keyboard->FW_keyboard_getKeyboardBuffer(), DIK_A)) //Left
	{
		m_cameraVector.moveLeftRight -= m_cameraVector.speed * elapsedGameTime;
	}
	if (KEYDOWN(keyboard->FW_keyboard_getKeyboardBuffer(), DIK_D)) //Right
	{
		m_cameraVector.moveLeftRight += m_cameraVector.speed * elapsedGameTime;
	}

	if (KEYDOWN(keyboard->FW_keyboard_getKeyboardBuffer(), DIK_SPACE)) //Up
	{
		m_cameraVector.moveHeightDown += m_cameraVector.speed * elapsedGameTime;
	}
	if (KEYDOWN(keyboard->FW_keyboard_getKeyboardBuffer(), DIK_LCONTROL)) //Down
	{
		m_cameraVector.moveHeightDown -= m_cameraVector.speed * elapsedGameTime;
	}

	//Calculate position & lookAt
	D3DXMatrixRotationYawPitchRoll(&m_cameraVector.camRotationMatrix, m_cameraVector.yaw, m_cameraVector.pitch, 0);
	D3DXVec3TransformCoord(&m_cameraVector.camTarget, &m_cameraVector.defaultForward, &m_cameraVector.camRotationMatrix);
	D3DXVec3Normalize(&m_cameraVector.camTarget, &m_cameraVector.camTarget);

	// Free-Look Camera
	D3DXVec3TransformCoord(&m_cameraVector.camRight, &m_cameraVector.defaultRight, &m_cameraVector.camRotationMatrix);
	D3DXVec3TransformCoord(&m_cameraVector.camForward, &m_cameraVector.defaultForward, &m_cameraVector.camRotationMatrix);
	D3DXVec3Cross(&m_cameraVector.camUp, &m_cameraVector.camForward, &m_cameraVector.camRight);

	m_cameraVector.camPosition += m_cameraVector.moveLeftRight * m_cameraVector.camRight;
	m_cameraVector.camPosition += m_cameraVector.moveBackForward * m_cameraVector.camForward;

	m_cameraVector.camPosition.y += m_cameraVector.moveHeightDown;

	//Reset Value
	m_cameraVector.moveLeftRight = 0.0f;
	m_cameraVector.moveBackForward = 0.0f;
	m_cameraVector.moveHeightDown = 0.0f;

	m_cameraVector.camTarget = m_cameraVector.camPosition + m_cameraVector.camTarget;

	D3DXMatrixLookAtLH(&m_cameraVector.camView, &m_cameraVector.camPosition, &m_cameraVector.camTarget, &m_cameraVector.camUp);
	D3DDevice->SetTransform(D3DTS_VIEW, &m_cameraVector.camView);
}

//Methods
void Direct3DFreeFlyCamera::Direct3DFreeFlyCamera_yaw(float value)
{
	m_cameraVector.yaw += value;
}

void Direct3DFreeFlyCamera::Direct3DFreeFlyCamera_pitch(float value)
{
	m_cameraVector.pitch += value;
}

D3DXVECTOR3 Direct3DFreeFlyCamera::Direct3DFreeFlyCamera_getPosition()const
{
	return m_cameraVector.camPosition;
}

D3DXMATRIX Direct3DFreeFlyCamera::Direct3DFreeFlyCamera_getViewMatrix()const
{
	return m_cameraVector.camView;
}

D3DXMATRIX Direct3DFreeFlyCamera::Direct3DFreeFlyCamera_getProjectionMatrix()const
{
	float aspect = 1.333f;
	float nearClip = 1.0f;
	float farClip = 1000.0f;

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4.0f, aspect, nearClip, farClip);

	return projectionMatrix;
}