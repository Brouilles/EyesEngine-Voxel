#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>

#include "CrossModel.h"
#include "BlockModel.h"

#include "TexturesList.h"
#include "../EyesEngine_Universal/BlocksList.h"

#include "../../FW_Debug/FW_Debug/FW_Debug.h"
/////////////////////////////////////////////////////////////

enum CubeType { air, block, cross };

class Block
{
public:
	Block();
	~Block();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Load block model, add texture
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Block_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, CubeType cubeType, float x, float y, float z);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Draw Block
	/// </summary>
	/////////////////////////////////////////////////////////////
	void Block_draw(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer[6], LPDIRECT3DINDEXBUFFER9 indexBuffer, LPD3DXEFFECT &shader, D3DXMATRIX view, D3DXMATRIX proj);

	//Methods
	//Set
	void Block_setCubeId(BLOCKSTRUCTURE id, TexturesList *texturesList);

	//For block render
	void BlockModel_setBlockFaceTop(bool value);
	void BlockModel_setBlockFaceBottom(bool value);
	void BlockModel_setBlockFaceOne(bool value);
	void BlockModel_setBlockFaceTwo(bool value);
	void BlockModel_setBlockFaceThird(bool value);
	void BlockModel_setBlockFaceFour(bool value);
	void BlockModel_setUpdateFaces();

	//Get
	CubeType Block_getCubeType()const;
	BLOCKSTRUCTURE  Block_getCubeId()const;

private:
	BlockModel m_blockRender;
	//CrossModel *m_crossRender;

	bool m_blockFaces[6]; //Define if face is visible

	BLOCKSTRUCTURE m_cubeId;
	CubeType m_cubeType;
	float m_x, m_y, m_z;
};

#endif
