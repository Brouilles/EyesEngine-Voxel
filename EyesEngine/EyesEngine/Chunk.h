#ifndef CHUNK_H_INCLUDED
#define CHUNK_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>
#include <list>

#include <d3d9.h>
#include <d3dx9.h>

#include "Block.h"

#include "TexturesList.h"
#include "../EyesEngine_Universal/BlocksList.h"

#include "../../FW_Debug/FW_Debug/FW_Debug.h"
/////////////////////////////////////////////////////////////

class Chunk
{
public:
	Chunk();
	~Chunk();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Define chunk size
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Chunk_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, TexturesList *texturesList, BlocksList blocksList, float chunk_x, float chunk_z);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Update chunk
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Chunk_update();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Update chunk
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Chunk_draw(LPDIRECT3DDEVICE9 D3DDevice, D3DXMATRIX view, D3DXMATRIX proj);

private:
	//Block
	LPDIRECT3DVERTEXBUFFER9 m_blockVertexBuffer[6]; //0 = top, 1 = bottom, etc ...
	LPDIRECT3DVERTEXBUFFER9 m_crossVertexBuffer[2];

	LPDIRECT3DINDEXBUFFER9 m_indexBuffer;
	LPD3DXEFFECT blockShader, crossShader;

	//Chunk
	//Block m_blockArray[16][16][16];
	int realBlock;
	Block *m_blockArray;

	D3DXVECTOR2 m_chunkPos;
};

#endif
