/////////////////////////////INCLUDE/////////////////////////
#include "World.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class World
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
World::World()
{}

World::~World()
{}

void World::World_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug)
{
	m_debug = &debug;

	m_texturesList.TexturesList_load(D3DDevice, *m_debug);
	m_blocksList.BlocksList_load();

	m_camera.Direct3DFreeFlyCamera_initialized(D3DDevice);
	m_entityPlayer.EntityModel_load(D3DDevice, *m_debug, "Content/Player/player.x");
	m_entityPlayer.EntityModel_setScale(0.4f);
	m_entityPlayer.EntityModel_setPosition(1.0f, 4.0f, 2.0f);

	//Initialized Chunk array
	m_chunkList.Chunk_load(D3DDevice, *m_debug, &m_texturesList, m_blocksList, 0, 0);
	/*for (int x = 0; x < 2; x++)
	{
		m_chunkList.push_back(vector<Chunk>());
		for (int z = 0; z < 2; z++)
		{
			m_chunkList[x].push_back(Chunk());
			m_chunkList[x][z].Chunk_load(D3DDevice, *m_debug, &m_texturesList, m_blocksList, x, z);
		}
	}*/
}

void World::World_update(LPDIRECT3DDEVICE9 D3DDevice, GameTime gameTime, FW_Keyboard *m_keyboard, FW_Mouse *m_mouse, float mouse_x, float mouse_y)
{
	m_camera.Direct3DFreeFlyCamera_update(D3DDevice, *m_debug, gameTime.GameTime_getElapsedGameTime(), m_keyboard, m_mouse, mouse_x, mouse_y);
	// m_entityPlayer.EntityModel_update(m_keyboard);
}

void World::World_draw(LPDIRECT3DDEVICE9 D3DDevice)
{
	m_entityPlayer.EntityModel_draw(D3DDevice);

	m_chunkList.Chunk_draw(D3DDevice, m_camera.Direct3DFreeFlyCamera_getViewMatrix(), m_camera.Direct3DFreeFlyCamera_getProjectionMatrix());
	/*for (int x = 0; x < 2; x++)
	{
		for (int z = 0; z < 2; z++)
		{
			m_chunkList[x][z].Chunk_draw(D3DDevice, m_camera.Direct3DFreeFlyCamera_getViewMatrix(), m_camera.Direct3DFreeFlyCamera_getProjectionMatrix());
		}
	}*/
}

//Methods
D3DXVECTOR3 World::World_getLocalEntityPosition()const
{
	return m_camera.Direct3DFreeFlyCamera_getPosition();
}