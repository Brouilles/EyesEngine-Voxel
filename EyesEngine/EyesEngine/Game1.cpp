/////////////////////////////INCLUDE/////////////////////////
#include "Game1.h"
/////////////////////////////////////////////////////////////

using namespace std;

void threadRender(Game &GameInstance)
{
	cout << "thread start" << endl;
	int endOfPorgram = 0;
	bool threadFinish;

	while (endOfPorgram == 0) {
		threadFinish = GameInstance.getThreadRenderState();
		while (threadFinish) { this_thread::yield(); Sleep(100); }  // wait for start signal
		GameInstance.Game_render();
		threadFinish = true;
	}
}

/*
**Class Game
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
Game1::Game1()
{	}

Game1::~Game1()
{	}

void Game1::Game_loadContent()
{
	//Game World
	m_world.World_load(m_direct3DManager.Direct3DManager_getD3Ddevice(), m_debug);

	//Debug Screen
	m_debugScreen.DebugScreen_initialized(m_direct3DManager.Direct3DManager_getD3Ddevice(), m_debug, m_playerId, m_playerPseudo);

	//Thread
	thread m_renderThread(threadRender, ref(*this));
	m_renderThread.detach();
}

/////////////////////////////////////////////////////////////
///		PROTECTED
/////////////////////////////////////////////////////////////
void Game1::Game_update()
{
	m_debugScreen.updateLogic(m_gameTime.GameTime_getElapsedGameTime());
	m_world.World_update(m_direct3DManager.Direct3DManager_getD3Ddevice(), m_gameTime, &m_keyboard, &m_mouse, m_mouse_x, m_mouse_y);

	if (KEYDOWN(m_keyboard.FW_keyboard_getKeyboardBuffer(), DIK_F4) || KEYDOWN(m_keyboard.FW_keyboard_getKeyboardBuffer(), DIK_ESCAPE))
		m_debug.FW_error("F4 exit", FW_debugType::LOGS, FW_debugType::NOTHING);

	if(m_gamepad.FW_Gamepad_getGamepadBuffer().rgbButtons[0])
		m_debug.FW_success("GamePad press", FW_debugType::WINDOW, FW_debugType::NOTHING);

	if (m_threadRenderFinish == true)
		m_threadRenderFinish = false;
}

void Game1::Game_render()
{
	m_ThreadGameTime.GameTime_update();
	m_direct3DManager.Direct3DManager_restore();

	m_debugScreen.updateRender(m_ThreadGameTime.GameTime_getElapsedGameTime(), m_world.World_getLocalEntityPosition());
	m_debugScreen.DebugScreen_draw();

	m_world.World_draw(m_direct3DManager.Direct3DManager_getD3Ddevice());

	m_direct3DManager.Direct3DManager_clear();
}