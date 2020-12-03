#ifndef TEXTURESLIST_H_INCLUDED
#define TEXTURESLIST_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>

#include "../../FW_Debug/FW_Debug/FW_Debug.h"
/////////////////////////////////////////////////////////////

class TexturesList {
public:
	TexturesList();
	~TexturesList();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Load textures
	/// </summary>
	/////////////////////////////////////////////////////////////
	void TexturesList_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug);

	//Methods
	LPDIRECT3DTEXTURE9 TexturesList_getTexture(char id);

private:
	LPDIRECT3DTEXTURE9 m_texture[4]; //Index start to 1
};

#endif