#ifndef MODELLOADER_X_H_INCLUDED
#define MODELLOADER_X_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>

#include "Math.cpp"
#include "../../FW_Debug/FW_Debug/FW_Debug.h"
/////////////////////////////////////////////////////////////

class ModelLoader_X
{
public:
	ModelLoader_X();
	~ModelLoader_X();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Load 3D model Array, texture, material and Light (ambien color)
	/// </summary>
	/////////////////////////////////////////////////////////////
	bool ModelLoader_X_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, std::string filePath);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Deallocated m_D3DMaterial and m_D3DTexture
	/// </summary>
	/////////////////////////////////////////////////////////////
	bool ModelLoader_X_deallocated();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Render 3D model: texture, material, light.
	/// </summary>
	/////////////////////////////////////////////////////////////
	void ModelLoader_X_render(LPDIRECT3DDEVICE9 D3DDevice);

	//Methods
	//Get
	void ModelLoader_X_setScale(float scale);
	void ModelLoader_X_setRotation(float x, float y, float z);
	void ModelLoader_X_setPosition(float x, float y, float z);

	//Set
	D3DXVECTOR3 ModelLoader_X_getScale();
	D3DXVECTOR3 ModelLoader_X_getRotation();
	D3DXVECTOR3 ModelLoader_X_getPosition();

private:
	HRESULT m_result;
	LPD3DXBUFFER m_DxBuffer;

	LPD3DXMESH m_D3DMesh;
	D3DMATERIAL9 *m_D3DMaterial;
	LPDIRECT3DTEXTURE9 *m_D3DTexture;
	DWORD m_materialCount;

	ModelVector3D m_modelVector;
};

#endif
