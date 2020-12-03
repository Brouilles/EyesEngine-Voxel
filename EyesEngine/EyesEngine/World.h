#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#include "EntityPlayer.h"
#include "Direct3DFreeFlyCamera.h"
#include "Chunk.h"

#include "TexturesList.h"
#include "../EyesEngine_Universal/BlocksList.h"

#include "../../FW_Debug/FW_Debug/FW_Debug.h"
#include "../../FW_Input/FW_Input/FW_Keyboard.h"
#include "../../FW_Input/FW_Input/FW_Mouse.h"
#include "../../FW_Input/FW_Input/FW_Input.h"
/////////////////////////////////////////////////////////////

class World
{
public:
	World();
	~World();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		
	/// </summary>
	/////////////////////////////////////////////////////////////
	void World_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Update World
	/// </summary>
	/////////////////////////////////////////////////////////////
	void World_update(LPDIRECT3DDEVICE9 D3DDevice, GameTime gameTime, FW_Keyboard *m_keyboard, FW_Mouse *m_mouse, float mouse_x, float mouse_y);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Draw World(Chunk, entity)
	/// </summary>
	/////////////////////////////////////////////////////////////
	void World_draw(LPDIRECT3DDEVICE9 D3DDevice);

	//Methods
	D3DXVECTOR3 World_getLocalEntityPosition()const;

private:
	FW_Debug *m_debug;
	EntityPlayer m_entityPlayer;
	Direct3DFreeFlyCamera m_camera;

	TexturesList m_texturesList;
	BlocksList m_blocksList;


	//std::vector<std::vector<Chunk>> m_chunkList;
	Chunk m_chunkList;
};

#endif
