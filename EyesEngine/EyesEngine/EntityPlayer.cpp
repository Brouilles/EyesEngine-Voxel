/////////////////////////////INCLUDE/////////////////////////
#include "EntityPlayer.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class EntityPlayer
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
EntityPlayer::EntityPlayer()
{}

EntityPlayer::~EntityPlayer()
{}

void EntityPlayer::EntityModel_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, string modelPath)
{
	EntityModel::EntityModel_load(D3DDevice, debug, modelPath);
}


void EntityPlayer::EntityModel_update(FW_Keyboard *keyboard)
{
	
}
