#ifndef BLOCKMODEL_H_INCLUDED
#define BLOCKMODEL_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#include "Model.h"
#include "../EyesEngine_Universal/BlocksList.h"

#include "Math.cpp"
#include "TexturesList.h"
#include "../../FW_Debug/FW_Debug/FW_Debug.h"
/////////////////////////////////////////////////////////////

class BlockModel
{
public:
	BlockModel();
	~BlockModel();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Load Block, initialize variable
	/// </summary>
	/////////////////////////////////////////////////////////////
	void BlockModel_load();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Draw Block
	/// </summary>
	/////////////////////////////////////////////////////////////
	void BlockModel_draw(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer[6], LPDIRECT3DINDEXBUFFER9 indexBuffer, LPD3DXEFFECT &shader, D3DXMATRIX view, D3DXMATRIX proj, float x, float y, float z);

	//Method
	void BlockModel_setTextures(BLOCKSTRUCTURE id, TexturesList *texturesList);
	void BlockModel_setFaces(bool blockFaces[5]);

protected:
	bool m_blockFaces[6]; //Define if face is visible
	LPDIRECT3DTEXTURE9 m_texture[6]; //Index start to 0 | 0: TOP / 1: Bottom
};

#endif
