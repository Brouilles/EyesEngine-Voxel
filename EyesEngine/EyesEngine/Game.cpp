/////////////////////////////INCLUDE/////////////////////////
#include "Game.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class Game
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
Game::Game()
{	}

Game::~Game()
{	}

bool Game::Game_initialized(HWND hWnd, HINSTANCE hInstance, bool fullscreen, int windowHeight, int windowWidth)
{
	//Input
	m_keyboard.FW_keyboard_initialized(hInstance, hWnd);
	m_mouse.FW_Mouse_initialized(hInstance, hWnd);
	m_gamepad.FW_Gamepad_initialized(hInstance, hWnd);

	m_direct3DManager.Direct3DManager_initialized(hWnd, m_debug, fullscreen, windowHeight, windowWidth);

	//Timer
	if(m_gameTime.GameTime_initialized())
		m_debug.FW_success("Game_initialized: GameTime_initialized", FW_debugType::LOGS, FW_debugType::NOTHING);
	else
		m_debug.FW_error("Game_initialized: GameTime_initialized", FW_debugType::WINDOW, FW_debugType::LOGS);
	
	if (m_ThreadGameTime.GameTime_initialized())
		m_debug.FW_success("Game_initialized: GameTime_initialized", FW_debugType::LOGS, FW_debugType::NOTHING);
	else
		m_debug.FW_error("Game_initialized: GameTime_initialized", FW_debugType::WINDOW, FW_debugType::LOGS);

	return true;
}

void Game::Game_loadContent()
{

}

void Game::Game_loop(float mouse_x, float mouse_y, float screenWidth, float screenHeight)
{
	//Update Timer
	m_gameTime.GameTime_update();

	//Get mouse position on Window
	m_mouse_x = mouse_x;
	m_mouse_y = mouse_y;

	//Screen
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	//Update Inputs 
	m_keyboard.FW_keyboard_acquire();
	m_mouse.FW_Mouse_acquire();
	m_gamepad.FW_Gamepad_acquire();

	//Call Function
	Game:Game_update();
	//Game_render();
}

//Methods
bool Game::getThreadRenderState()
{
	return m_threadRenderFinish;
}

/////////////////////////////////////////////////////////////
///		PRIVATE
/////////////////////////////////////////////////////////////
void Game::Game_update()
{

}

void Game::Game_render()
{
	m_direct3DManager.Direct3DManager_restore();
	m_direct3DManager.Direct3DManager_clear();
}