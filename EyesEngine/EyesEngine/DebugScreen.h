#ifndef DEBUGSCREEN_H_INCLUDED
#define DEBUGSCREEN_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <Windows.h>

#include <string>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#include "../EyesEngine_Universal/CoolDown.h"
#include "../../FW_Input/FW_Input//FW_Keyboard.h"
/////////////////////////////////////////////////////////////

class DebugScreen
{
public:
	DebugScreen();
	~DebugScreen();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Initiazed GameTime
	/// </summary>
	/////////////////////////////////////////////////////////////
	bool DebugScreen_initialized(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Calculate new value, FPS, GPU
	/// </summary>
	/////////////////////////////////////////////////////////////
	void updateRender(float elapsedTime, D3DXVECTOR3 m_entityPos);
	void updateLogic(float elapsedTime);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Draw information
	/// </summary>
	/////////////////////////////////////////////////////////////
	void DebugScreen_draw();

private:
	//Frames per second (GPU)
	int m_lastFrameRate, m_frameRate;
	CoolDown m_coolDown;

	//Frames per second (CPU)
	int m_lastFrameRateCPU, m_frameRateCPU;
	CoolDown m_coolDownCPU;

	//Player/Camera position
	D3DXVECTOR3 m_entityPos;

	//Font
	ID3DXFont *m_font = NULL;
	int m_fontSize;
	RECT m_rectanglePosition[4];
	TCHAR m_strFont[LF_FACESIZE]; //Font name
	ID3DXMesh *m_mesh3DText = NULL;
};

#endif