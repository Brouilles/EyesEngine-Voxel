#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

/////////////////////////////INCLUDE/////////////////////////
#include <stdio.h>
#include <string>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>
/////////////////////////////////////////////////////////////

struct BLOCKVERTEX
{
	FLOAT x, y, z; // The transformed position for the vertex
	FLOAT tu, tv; //Texture coordinates
	//FLOAT nx, ny, nz; //Light informations
};

struct BLOCKTEXTURE
{
	char id;
	LPDIRECT3DTEXTURE9 texture;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_BLOCKSVERTEX (D3DFVF_XYZ | D3DFVF_TEX1/*| D3DFVF_NORMALD3DFVF_DIFFUSE*/)

#endif
