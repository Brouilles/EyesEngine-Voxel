/////////////////////////////INCLUDE/////////////////////////
#include "BlocksList.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class BlocksList
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
BlocksList::BlocksList()
{}

BlocksList::~BlocksList()
{}

void BlocksList::BlocksList_load()
{
	//Grass
	grass.id = 0;
	grass.collision = true;
	grass.texturesId[0] = 0; 
	grass.texturesId[1] = 2;
	grass.texturesId[2] = 1;
	grass.texturesId[3] = 1;
	grass.texturesId[4] = 1;
	grass.texturesId[5] = 1;

	//Dirt
	dirt.id = 1;
	dirt.collision = true;
	dirt.texturesId[0] = 2;
	dirt.texturesId[1] = 2;
	dirt.texturesId[2] = 2;
	dirt.texturesId[3] = 2;
	dirt.texturesId[4] = 2;
	dirt.texturesId[5] = 2;

	//Gras Plant
	grasPlant.id = 2;
	grasPlant.collision = false;
	grasPlant.texturesId[0] = 3;
	grasPlant.texturesId[1] = 0;
	grasPlant.texturesId[2] = 0;
	grasPlant.texturesId[3] = 0;
	grasPlant.texturesId[4] = 0;
	grasPlant.texturesId[5] = 0;
}