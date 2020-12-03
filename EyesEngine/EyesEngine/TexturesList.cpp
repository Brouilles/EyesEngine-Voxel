/////////////////////////////INCLUDE/////////////////////////
#include "TexturesList.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class TexturesList
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
TexturesList::TexturesList()
{}

TexturesList::~TexturesList()
{}

void TexturesList::TexturesList_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug)
{
	//Defined textures list
	string texturesPath[sizeof(m_texture) / sizeof(m_texture[0])] = { //Index start to 0
		"Content/blocks/grass/grass_top.png", //Grass top - 0
		"Content/blocks/grass/grass_side.png", //Grass side - 1
		"Content/blocks/grass/grass_bottom.png", //Grass bottom - 2
		"Content/blocks/plants/grass1.png" // 3
	};

	//Load textures
	for (int loop = 0; loop < sizeof(m_texture) / sizeof(m_texture[0]); loop++)
	{
		if (FAILED(D3DXCreateTextureFromFile(D3DDevice, texturesPath[loop].c_str(), &m_texture[loop])))
			debug.FW_warning("TexturesList_load: Could not find texture: " + texturesPath[loop], FW_debugType::LOGS, FW_debugType::NOTHING);
		else
			debug.FW_success("TexturesList_load: Texture Load: " + texturesPath[loop], FW_debugType::LOGS, FW_debugType::NOTHING);
	}
}

//Methods
LPDIRECT3DTEXTURE9 TexturesList::TexturesList_getTexture(char id)
{
	return m_texture[id];
}