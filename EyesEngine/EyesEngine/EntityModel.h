#ifndef ENTITYMODEL_H_INCLUDED
#define ENTITYMODEL_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>

#include "../../FW_Debug/FW_Debug/FW_Debug.h"
#include "ModelLoader_X.h"
/////////////////////////////////////////////////////////////

class EntityModel
{
public:
	EntityModel();
	~EntityModel();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Load map file with MapLoader class
	/// </summary>
	/////////////////////////////////////////////////////////////
	bool EntityModel_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, std::string modelPath);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Update entity (animation, move)
	/// </summary>
	/////////////////////////////////////////////////////////////
	void EntityModel_update();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Draw 3D models, add rotation, translate
	/// </summary>
	/////////////////////////////////////////////////////////////
	void EntityModel_draw(LPDIRECT3DDEVICE9 D3DDevice);

	//Methods
	//Models 
	void EntityModel_setScale(float scale);

	void EntityModel_setRotation(float x, float y, float z);
	void EntityModel_setRotation(D3DXVECTOR3 Rotation);

	void EntityModel_setPosition(float x, float y, float z);
	void EntityModel_setPosition(D3DXVECTOR3 position);

	float EntityModel_getScale();
	D3DXVECTOR3 EntityModel_getRotation();
	D3DXVECTOR3 EntityModel_getPosition();


protected:
	ModelVector3D m_entityVector;
	ModelLoader_X m_entity3DModel;
};

#endif
