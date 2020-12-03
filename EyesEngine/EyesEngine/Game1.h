#ifndef GAME1_H_INCLUDED
#define GAME1_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "Direct3DManager.h"

#include "World.h"

#include "DebugScreen.h"
/////////////////////////////////////////////////////////////

class Game1 : public Game
{
public:
	Game1();
	~Game1();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Load game content: 3D Models, textures, camera
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Game_loadContent();

protected:
	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Update Timer, entity, camera, ...
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Game_update();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Scene Render: 3D models, textures, World Matrix
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Game_render();

	//Entity
	World m_world;

	//DebugScreen
	DebugScreen m_debugScreen;
};

void threadRender(Game &GameInstance);

#endif