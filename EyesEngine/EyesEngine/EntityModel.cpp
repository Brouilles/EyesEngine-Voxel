/////////////////////////////INCLUDE/////////////////////////
#include "EntityModel.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class EntityModel
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
EntityModel::EntityModel()
{}

EntityModel::~EntityModel()
{}

bool EntityModel::EntityModel_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, string modelPath)
{
	if (m_entity3DModel.ModelLoader_X_load(D3DDevice, debug, modelPath.c_str()))
		return true;
	else
		return false;
}

void EntityModel::EntityModel_update()
{}

void EntityModel::EntityModel_draw(LPDIRECT3DDEVICE9 D3DDevice)
{
	m_entity3DModel.ModelLoader_X_render(D3DDevice);
}

//Methods
//Set
void EntityModel::EntityModel_setScale(float scale)
{
	m_entityVector.scale = D3DXVECTOR3(scale, scale, scale);
	m_entity3DModel.ModelLoader_X_setScale(scale);
}

void EntityModel::EntityModel_setRotation(float x, float y, float z)
{
	m_entityVector.rotation = D3DXVECTOR3(x, y, z);
	m_entity3DModel.ModelLoader_X_setRotation(x, y, z);
}

void EntityModel::EntityModel_setRotation(D3DXVECTOR3 rotation)
{
	m_entityVector.rotation = rotation;
	m_entity3DModel.ModelLoader_X_setRotation(rotation.x, rotation.y, rotation.z);
}

void EntityModel::EntityModel_setPosition(float x, float y, float z)
{
	m_entityVector.position = D3DXVECTOR3(x, y, z);
	m_entity3DModel.ModelLoader_X_setPosition(x, y, z);
}

void EntityModel::EntityModel_setPosition(D3DXVECTOR3 position)
{
	m_entityVector.position = position;
	m_entity3DModel.ModelLoader_X_setPosition(position.x, position.y, position.z);
}

//Get
float EntityModel::EntityModel_getScale()
{
	return m_entity3DModel.ModelLoader_X_getScale().x;
}

D3DXVECTOR3 EntityModel::EntityModel_getRotation()
{
	return m_entity3DModel.ModelLoader_X_getRotation();
}

D3DXVECTOR3 EntityModel::EntityModel_getPosition()
{
	return m_entity3DModel.ModelLoader_X_getPosition();
}