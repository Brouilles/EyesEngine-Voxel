#ifndef DIRECT3DMANAGER_H_INCLUDED
#define DIRECT3DMANAGER_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../../FW_Debug/FW_Debug/FW_Debug.h"
/////////////////////////////////////////////////////////////

class Direct3DManager
{
public:
	Direct3DManager();
	~Direct3DManager();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Initiazed DirectX 9: context  and device.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Direct3DManager_initialized(HWND hWnd, FW_Debug debug, bool fullscreen, int windowHeight, int windowWidth);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Deallocated memory.
	/// </summary>
	/////////////////////////////////////////////////////////////
	bool Direct3DManager_deallocated();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Render game: clear device, matrix, Shader.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Direct3DManager_restore();
	void Direct3DManager_clear();

	LPDIRECT3DDEVICE9 Direct3DManager_getD3Ddevice();

private:
	LPDIRECT3D9 m_D3D9;
	LPDIRECT3DDEVICE9 m_D3Ddevice;
};

#endif