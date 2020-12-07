/////////////////////////////INCLUDE/////////////////////////
#include "Chunk.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class Chunk
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
Chunk::Chunk(): m_blockArray(nullptr), realBlock(0)
{}

Chunk::~Chunk()
{
	delete m_blockArray;
}

void Chunk::Chunk_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, TexturesList *texturesList, BlocksList blocksList, float chunk_x, float chunk_z)
{
	m_chunkPos.x = chunk_x;
	m_chunkPos.y = chunk_z;

	//Defined Block Index and Vertex position
	//Block Vertex Buffer
	for (int loop = 0; loop <= 6; loop++)
	{
		if (FAILED(D3DDevice->CreateVertexBuffer(4 * sizeof(BLOCKVERTEX), 0, D3DFVF_BLOCKSVERTEX, D3DPOOL_MANAGED, &m_blockVertexBuffer[loop], NULL)))
			debug.FW_warning("Block: D3DDevice->CreateVertexBuffer", FW_debugType::LOGS, FW_debugType::NOTHING);
	}

	BLOCKVERTEX blockVertices[6][4] = {
		{ //Top
			{ -0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },
			{ -0.0f, 1.0f, -0.0f, 0.0f, 1.0f },
			{ 1.0f, 1.0f, -0.0f, 1.0f, 1.0f }
		},
		{ //Bottom
			{ 1.0f, -0.0f, 1.0f, 0.0f, 0.0f },
			{ -0.0f, -0.0f, 1.0f, 1.0f, 0.0f },
			{ 1.0f, -0.0f, -0.0f, 0.0f, 1.0f },
			{ -0.0f, -0.0f, -0.0f, 1.0f, 1.0f }
		},
		{ //Face 1
			{ -0.0f, 1.0f, -0.0f, 0.0f, 0.0f },
			{ 1.0f, 1.0f, -0.0f, 1.0f, 0.0f },
			{ -0.0f, -0.0f, -0.0f, 0.0f, 1.0f },
			{ 1.0f, -0.0f, -0.0f, 1.0f, 1.0f }
		},
		{ //Face 2
			{ 1.0f, 1.0f, -0.0f, 0.0f, 0.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },
			{ 1.0f, -0.0f, -0.0f, 0.0f, 1.0f },
			{ 1.0f, -0.0f, 1.0f, 1.0f, 1.0f },
		},
		{ //Face 3
			{ 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
			{ -0.0f, 1.0f, 1.0f, 1.0f, 0.0f },
			{ 1.0f, -0.0f, 1.0f, 0.0f, 1.0f },
			{ -0.0f, -0.0f, 1.0f, 1.0f, 1.0f }
		},
		{ //Face 4
			{ -0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
			{ -0.0f, 1.0f, -0.0f, 1.0f, 0.0f },
			{ -0.0f, -0.0f, 1.0f, 0.0f, 1.0f },
			{ -0.0f, -0.0f, -0.0f, 1.0f, 1.0f },
		}
	};

	VOID* pVoid;
	for (int loop = 0; loop <= 6; loop++)
	{
		m_blockVertexBuffer[loop]->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, blockVertices[loop], sizeof(blockVertices[loop]));
		m_blockVertexBuffer[loop]->Unlock();
	}

	//Cross Vertex Buffer
	for (int loop = 0; loop <= 1; loop++)
	{
		if (FAILED(D3DDevice->CreateVertexBuffer(4 * sizeof(BLOCKVERTEX), 0, D3DFVF_BLOCKSVERTEX, D3DPOOL_MANAGED, &m_crossVertexBuffer[loop], NULL)))
			debug.FW_warning("Block: D3DDevice->CreateVertexBuffer", FW_debugType::LOGS, FW_debugType::NOTHING);
	}

	BLOCKVERTEX crossVertices[2][4] = {
		{ //Face 1
			{ 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
			{ 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 0.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 0.0f, 1.0f, 0.0f }
		},
		{ //Face 2
			{ 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f, 1.0f, 0.0f }
		}
	};

	for (int loop = 0; loop <= 1; loop++)
	{
		m_crossVertexBuffer[loop]->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, crossVertices[loop], sizeof(crossVertices[loop]));
		m_crossVertexBuffer[loop]->Unlock();
	}
	//Indices Buffer
	if (FAILED(D3DDevice->CreateIndexBuffer(6 * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_indexBuffer, NULL)))
		debug.FW_warning("Block: D3DDevice->CreateIndexBuffer", FW_debugType::LOGS, FW_debugType::NOTHING);

	short indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};

	m_indexBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	m_indexBuffer->Unlock();

	//Load Shader
	//For Block
	blockShader = NULL;
	LPD3DXBUFFER pErrorShaderBuffer = NULL;
	if (FAILED(D3DXCreateEffectFromFileA(D3DDevice, "Content/Shaders/ShaderTexture.fx", 0, 0, 0, 0, &blockShader, &pErrorShaderBuffer)))
	{
		char *error = (char *)pErrorShaderBuffer->GetBufferPointer();
		debug.FW_error(error, FW_debugType::LOGS, FW_debugType::WINDOW);
	}
	blockShader->SetTechnique(blockShader->GetTechniqueByName("technique0"));

	//For Cross
	crossShader = NULL;
	if (FAILED(D3DXCreateEffectFromFileA(D3DDevice, "Content/Shaders/ShaderTextureCross.fx", 0, 0, 0, 0, &crossShader, &pErrorShaderBuffer)))
	{
		char *error = (char *)pErrorShaderBuffer->GetBufferPointer();
		debug.FW_error(error, FW_debugType::LOGS, FW_debugType::WINDOW);
	}

	//Initialized Map array
	std::vector<std::vector<std::vector<unsigned char>>> blockMapArray;
	for (int x = 0; x < 16; x++)
	{
		blockMapArray.push_back(vector<vector<unsigned char>>());
		for (int y = 0; y < 16; y++)
		{
			blockMapArray[x].push_back(vector<unsigned char>());
			for (int z = 0; z < 16; z++)
			{
				blockMapArray[x][y].push_back(unsigned char());

				if (y == 3)
				{
					realBlock++;
					blockMapArray[x][y][z] = 0; //Grass
				}
				else if (y < 3)
				{
					realBlock++;
					blockMapArray[x][y][z] = 1; //Dirt
				}
				else
					blockMapArray[x][y][z] = 254; //Empty
			}
		}
	}

	//Map Block
	m_blockArray = new Block[realBlock];

	int arrayLoop(0);
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			for (int z = 0; z < 16; z++)
			{
				if (blockMapArray[x][y][z] != 254)
				{
					m_blockArray[arrayLoop] = Block();
					m_blockArray[arrayLoop].Block_load(D3DDevice, debug, CubeType::block, (float)x, (float)y, (float)z);

					if (blockMapArray[x][y][z] == 0)
						m_blockArray[arrayLoop].Block_setCubeId(blocksList.grass, texturesList);
					else if (blockMapArray[x][y][z] == 1)
						m_blockArray[arrayLoop].Block_setCubeId(blocksList.dirt, texturesList);

					//Define faces
					if (y + 1 < 16) {
						if (blockMapArray[x][y + 1][z] != 254) //Top
							m_blockArray[arrayLoop].BlockModel_setBlockFaceTop(false);
					}

					if (y - 1 >= 0) {
						if (blockMapArray[x][y - 1][z] != 254) //Bottom 
							m_blockArray[arrayLoop].BlockModel_setBlockFaceBottom(false);
					}

					if (z - 1 >= 0) {
						if (blockMapArray[x][y][z - 1] != 254) //One
							m_blockArray[arrayLoop].BlockModel_setBlockFaceOne(false);
					}

					if (x + 1 < 16) {
						if (blockMapArray[x + 1][y][z] != 254) //Two
							m_blockArray[arrayLoop].BlockModel_setBlockFaceTwo(false);
					}

					if (z + 1 < 16) {
						if (blockMapArray[x][y][z + 1] != 254) //Third
							m_blockArray[arrayLoop].BlockModel_setBlockFaceThird(false);
					}

					if (x - 1 >= 0) {
						if (blockMapArray[x - 1][y][z] != 254) //Four
							m_blockArray[arrayLoop].BlockModel_setBlockFaceFour(false);
					}

					m_blockArray[arrayLoop].BlockModel_setUpdateFaces();
					arrayLoop++;
				}
			}
		}
	}
	blockMapArray.clear();
}


void Chunk::Chunk_update()
{

}

void Chunk::Chunk_draw(LPDIRECT3DDEVICE9 D3DDevice, D3DXMATRIX view, D3DXMATRIX proj)
{
	for (int i = 0; i < realBlock; i++)
	{
		m_blockArray[i].Block_draw(D3DDevice, m_blockVertexBuffer, m_indexBuffer, blockShader, view, proj);
	}
}