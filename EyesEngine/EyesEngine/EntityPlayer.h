#ifndef ENTITYPLAYER_H_INCLUDED
#define ENTITYPLAYER_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>

#include "../../FW_Debug/FW_Debug/FW_Debug.h"
#include "../../FW_Input/FW_Input/FW_Keyboard.h"
#include "../../FW_Input/FW_Input/FW_Input.h"

#include "EntityModel.h"
#include "ModelLoader_X.h"
/////////////////////////////////////////////////////////////

class EntityPlayer : public EntityModel
{
public:
	EntityPlayer();
	~EntityPlayer();

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Load, initialise entity player
	/// </summary>
	/////////////////////////////////////////////////////////////
	void EntityModel_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, std::string modelPath);

	/////////////////////////////////////////////////////////////
	/// <summary> 
	///		Update entity (animation, move)
	/// </summary>
	/////////////////////////////////////////////////////////////
	void EntityModel_update(FW_Keyboard *keyboard);

protected:
	ModelVector3D m_entityVector;
	ModelLoader_X m_entity3DModel;
};

#endif
