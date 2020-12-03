/////////////////////////////INCLUDE/////////////////////////
#include "Block.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class Block
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
Block::Block(): m_x(0), m_y(0), m_z(0)
{}

Block::~Block()
{
	/*if (m_cubeType == CubeType::block)
		delete m_blockRender;
	else if (m_cubeType == CubeType::cross)
		delete m_crossRender;*/
}

void Block::Block_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, CubeType cubeType, float x, float y, float z)
{
	m_cubeType = cubeType;
	m_x = x;
	m_y = y;
	m_z = z;

	if (m_cubeType == CubeType::block)
	{
		//m_blockRender = new BlockModel;
		m_blockRender.BlockModel_load();
		//delete m_crossRender;

		for (int loop = 0; loop < 6; loop++)
			m_blockFaces[loop] = true;
	} 
	/*else if (m_cubeType == CubeType::cross)
	{
		m_crossRender = new CrossModel;
		//delete m_blockRender;
	}*/
}

void Block::Block_draw(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer[6], LPDIRECT3DINDEXBUFFER9 indexBuffer, LPD3DXEFFECT &shader, D3DXMATRIX view, D3DXMATRIX proj)
{
	if (m_cubeType == CubeType::block)
	{
		m_blockRender.BlockModel_draw(D3DDevice, vertexBuffer, indexBuffer, shader, view, proj, m_x, m_y, m_z);
	}
	/*else if (m_cubeType == CubeType::cross)
	{
		m_crossRender->CrossModel_draw(D3DDevice, vertexBuffer, indexBuffer, shader, view, proj, m_cubePos.x, m_cubePos.y, m_cubePos.z);
	}*/
}

//Methods
//Set
void Block::Block_setCubeId(BLOCKSTRUCTURE id, TexturesList *texturesList)
{
	m_cubeId = id;

	if (m_cubeType == CubeType::block)
		m_blockRender.BlockModel_setTextures(m_cubeId, texturesList);
	/*else if (m_cubeType == CubeType::cross)
		m_crossRender->CrossModel_setTextures(m_cubeId, texturesList);*/
}

void Block::BlockModel_setBlockFaceTop(bool value)
{
	m_blockFaces[0] = value;
}

void Block::BlockModel_setBlockFaceBottom(bool value)
{
	m_blockFaces[1] = value;
}

void Block::BlockModel_setBlockFaceOne(bool value)
{
	m_blockFaces[2] = value;
}

void Block::BlockModel_setBlockFaceTwo(bool value)
{
	m_blockFaces[3] = value;
}

void Block::BlockModel_setBlockFaceThird(bool value)
{
	m_blockFaces[4] = value;
}

void Block::BlockModel_setBlockFaceFour(bool value)
{
	m_blockFaces[5] = value;
}

void Block::BlockModel_setUpdateFaces()
{
	m_blockRender.BlockModel_setFaces(m_blockFaces);
}

//Get
CubeType Block::Block_getCubeType()const
{
	return m_cubeType;
}

BLOCKSTRUCTURE Block::Block_getCubeId()const
{
	return m_cubeId;
}
