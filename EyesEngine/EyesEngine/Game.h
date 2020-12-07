#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>
#include <thread>

#include <d3d9.h>
#include <d3dx9.h>

#include "Direct3DManager.h"
#include "../EyesEngine_Universal/GameTime.h"

#include "../../FW_Debug/FW_Debug/FW_Debug.h"
#include "../../FW_Input/FW_Input/FW_Keyboard.h"
#include "../../FW_Input/FW_Input/FW_Gamepad.h"
#include "../../FW_Input/FW_Input/FW_Mouse.h"
#include "../../FW_Input/FW_Input/FW_Input.h"
/////////////////////////////////////////////////////////////

class Game
{
public:
	Game();
	~Game();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Initializes engine content: 3D context, inputs
	/// </summary>
	/////////////////////////////////////////////////////////////
	bool Game_initialized(HWND hWnd, HINSTANCE hInstance, bool fullscreen, int windowHeight, int windowWidth);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Load game content: 3D Models, textures, camera
	/// </summary>
	/////////////////////////////////////////////////////////////
	virtual void Game_loadContent();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Game loop
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Game_loop(float mouse_x, float mouse_y, float screenWidth, float screenHeight);

	virtual void Game_render();

	//Methods
	bool getThreadRenderState();
protected:
	virtual void Game_update();

	//FW_Technology
	FW_Debug m_debug;
	FW_Keyboard m_keyboard;
	FW_Mouse m_mouse;
	FW_Gamepad m_gamepad;

	//Win32 information
	float m_mouse_x, m_mouse_y, m_screenWidth, m_screenHeight;

	Direct3DManager m_direct3DManager;
	GameTime m_gameTime;
	GameTime m_ThreadGameTime;

	//Thread
	bool m_threadRenderFinish;
};

#endif