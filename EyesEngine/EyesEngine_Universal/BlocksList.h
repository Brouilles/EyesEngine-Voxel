#ifndef BLOCKSLIST_H_INCLUDED
#define BLOCKSLIST_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>
#include <vector>
/////////////////////////////////////////////////////////////

struct BLOCKSTRUCTURE {
	char id; //Limite 256
	bool collision;
	int texturesId[6]; //Index start to 0 | 0: TOP / 1: Bottom
};

class BlocksList {
public:
	BlocksList();
	~BlocksList();

	void BlocksList_load();

	BLOCKSTRUCTURE grass;
	BLOCKSTRUCTURE dirt;
	BLOCKSTRUCTURE grasPlant;
};

#endif