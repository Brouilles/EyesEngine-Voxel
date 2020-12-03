/////////////////////////////INCLUDE/////////////////////////
#include "BlockModel.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class BlockModel
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
BlockModel::BlockModel()
{}

BlockModel::~BlockModel()
{}

void BlockModel::BlockModel_load()
{
	for (int loop = 0; loop < 6; loop++)
		m_blockFaces[loop] = true;
}

void BlockModel::BlockModel_draw(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer[6], LPDIRECT3DINDEXBUFFER9 indexBuffer, LPD3DXEFFECT &shader, D3DXMATRIX view, D3DXMATRIX proj, float x, float y, float z)
{
	if (!(m_blockFaces[0] == false && m_blockFaces[1] == false && m_blockFaces[2] == false && m_blockFaces[3] == false && m_blockFaces[4] == false && m_blockFaces[5] == false))
	{
		D3DXMATRIX scaleMatrix;
		D3DXMATRIX rotationMatrix;
		D3DXMATRIX transMatrix;

		D3DXMatrixScaling(&scaleMatrix, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, 0.0f, 0.0f, 0.0f);
		D3DXMatrixTranslation(&transMatrix, x, y, z);

		D3DXMatrixMultiply(&transMatrix, &scaleMatrix, &transMatrix);
		D3DXMatrixMultiply(&transMatrix, &rotationMatrix, &transMatrix);

		D3DDevice->SetTransform(D3DTS_WORLD, &transMatrix);

		//Shader
		//shader->SetTechnique(shader->GetTechniqueByName("technique0"));
		shader->SetMatrix("WorldViewProj", &(transMatrix * view * proj));

		//Argument
		D3DDevice->SetFVF(D3DFVF_BLOCKSVERTEX);
		D3DDevice->SetIndices(indexBuffer);

		//TRANGLE LIST METHODS
		UINT numPass = 0;
		shader->Begin(&numPass, 0);
		for (int loop = 0; loop <= 5; loop++)
		{
			for (int i = 0; i < numPass; ++i)
			{
				if (m_blockFaces[loop] == true)
				{
					shader->BeginPass(i);

					D3DDevice->SetStreamSource(0, vertexBuffer[loop], 0, sizeof(BLOCKVERTEX));
					shader->SetTexture("MeshTexture", m_texture[loop]);

					shader->CommitChanges();
					D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 3);
					shader->EndPass();
				}
			}
		}
		shader->End();
		/*
		D3DDevice->SetFVF(D3DFVF_BLOCKSVERTEX);
		D3DDevice->SetIndices(indexBuffer);

		for (int loop = 0; loop <= 5; loop++)
		{
			if (m_blockFaces[loop] == true)
			{
				D3DDevice->SetStreamSource(0, vertexBuffer[loop], 0, sizeof(BLOCKVERTEX));
				D3DDevice->SetTexture(0, m_texture[loop]);
				D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 3);
			}
		}*/
	}
}

//Methods
void BlockModel::BlockModel_setTextures(BLOCKSTRUCTURE id, TexturesList *texturesList)
{
	for (int loop = 0; loop <= 5; loop++)
		m_texture[loop] = texturesList->TexturesList_getTexture(id.texturesId[loop]);
}

void BlockModel::BlockModel_setFaces(bool blockFaces[5])
{
	for (int loop = 0; loop <= 5; loop++)
		m_blockFaces[loop] = blockFaces[loop];
}
