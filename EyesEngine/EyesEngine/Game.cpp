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
{
	WSACleanup();
}

bool Game::Game_initialized(HWND hWnd, HINSTANCE hInstance, bool fullscreen, int windowHeight, int windowWidth)
{
	//Server connexion
	WSAStartup(MAKEWORD(2, 0), &m_WSAData);
	m_sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_sin.sin_family = AF_INET;
	m_sin.sin_port = htons(4148);

	SOCKET sockConnect;
	sockConnect = socket(AF_INET, SOCK_STREAM, 0);

	if (FAILED(connect(sockConnect, (SOCKADDR*)&m_sin, sizeof(m_sin))))
	{
		m_debug.FW_error("Game_initialized: Server connexion FAILED", FW_debugType::WINDOW, FW_debugType::LOGS);
	}
	else
		m_debug.FW_success("Game_initialized: Server connexion", FW_debugType::LOGS, FW_debugType::NOTHING);
	
	char buffer[255], voidBuffer[255];
	memset(buffer, 0, sizeof(buffer));
	memset(voidBuffer, 0, sizeof(voidBuffer));
	m_playerPseudo = "void";

	do
	{
		recv(sockConnect, buffer, sizeof(buffer), 0);
	} while (buffer == voidBuffer);
	m_playerId = (int)buffer[0];

	memcpy(voidBuffer, (buffer + 1), sizeof(buffer) - 1);
	m_playerPseudo = voidBuffer;

	m_debug.FW_success("Game_initialized: Server Reponse (" + m_playerPseudo + ", " + to_string(m_playerId).c_str() + ")", FW_debugType::LOGS, FW_debugType::NOTHING);

	closesocket(sockConnect);

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