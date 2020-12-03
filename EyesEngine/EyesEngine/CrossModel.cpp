/////////////////////////////INCLUDE/////////////////////////
#include "CrossModel.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class CrossModel
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
CrossModel::CrossModel()
{}

CrossModel::~CrossModel()
{}

void CrossModel::CrossModel_draw(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer[2], LPDIRECT3DINDEXBUFFER9 indexBuffer, LPD3DXEFFECT &shader, D3DXMATRIX view, D3DXMATRIX proj, float x, float y, float z)
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
	shader->SetTechnique(shader->GetTechniqueByName("technique0"));
	shader->SetMatrix("WorldViewProj", &(transMatrix * view * proj));

	//TRANGLE LIST METHODS
	for (int loop = 0; loop < 2; loop++)
	{
		UINT numPass = 0;
		shader->Begin(&numPass, 0);

		for (int i = 0; i < numPass; ++i)
		{
			shader->SetTexture("shaderTexture", m_texture);
			shader->BeginPass(i);

			D3DDevice->SetFVF(D3DFVF_BLOCKSVERTEX);
			D3DDevice->SetStreamSource(0, vertexBuffer[loop], 0, sizeof(BLOCKVERTEX));
			D3DDevice->SetIndices(indexBuffer);
			D3DDevice->SetTexture(0, m_texture);

			shader->CommitChanges();
			//D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 3);
			//D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			shader->EndPass();
		}
	}
}

void CrossModel::CrossModel_setTextures(BLOCKSTRUCTURE id, TexturesList *texturesList)
{
	m_texture = texturesList->TexturesList_getTexture(id.texturesId[0]);
}