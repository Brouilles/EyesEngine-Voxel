#ifndef CROSSMODEL_H_INCLUDED
#define CROSSMODEL_H_INCLUDED

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

class CrossModel
{
public:
	CrossModel();
	~CrossModel();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Draw Cross model (Texture)
	/// </summary>
	/////////////////////////////////////////////////////////////
	void CrossModel_draw(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer[2], LPDIRECT3DINDEXBUFFER9 indexBuffer, LPD3DXEFFECT &shader, D3DXMATRIX view, D3DXMATRIX proj, float x, float y, float z);

	//Method
	void CrossModel_setTextures(BLOCKSTRUCTURE id, TexturesList *texturesList);

private:
	LPDIRECT3DTEXTURE9 m_texture; 
};

#endif
