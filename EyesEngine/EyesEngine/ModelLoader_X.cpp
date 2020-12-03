/////////////////////////////INCLUDE/////////////////////////
#include "ModelLoader_X.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class ModelLoader_X
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
ModelLoader_X::ModelLoader_X()
{}

ModelLoader_X::~ModelLoader_X()
{}

bool ModelLoader_X::ModelLoader_X_load(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug, string filePath)
{
	if (SUCCEEDED(D3DXLoadMeshFromXA(filePath.c_str(), D3DXMESH_SYSTEMMEM, D3DDevice, NULL, &m_DxBuffer, NULL, &m_materialCount, &m_D3DMesh)))
	{
		D3DXMATERIAL *D3DMaterial = (D3DXMATERIAL*)m_DxBuffer->GetBufferPointer();

		//Create arrays for material and texture
		m_D3DMaterial = new D3DMATERIAL9[m_materialCount];
		m_D3DTexture = new LPDIRECT3DTEXTURE9[m_materialCount];

		for (DWORD loop = 0; loop < m_materialCount; loop++)
		{
			//Copy material
			m_D3DMaterial[loop] = D3DMaterial[loop].MatD3D;

			//Set ambien color
			m_D3DMaterial[loop].Ambient = m_D3DMaterial[loop].Diffuse;

			//Load texture
			if (D3DMaterial[loop].pTextureFilename != NULL && lstrlen(D3DMaterial[loop].pTextureFilename) > 0)
			{
				m_result = D3DXCreateTextureFromFileA(D3DDevice, D3DMaterial[loop].pTextureFilename, &m_D3DTexture[loop]);
				if (FAILED(m_result))
				{
					m_D3DTexture[loop] = NULL;
					debug.FW_warning("D3DXCreateTextureFromFileA Error in ModelLoader_X", FW_debugType::LOGS, FW_debugType::NOTHING);
				}
			}
			else
			{
				D3DXCreateTextureFromFileA(D3DDevice, "noTexture.bmp", &m_D3DTexture[loop]);
				debug.FW_warning("Load texture Warning in ModelLoader_X", FW_debugType::LOGS, FW_debugType::NOTHING);
			}
		}
		return true;
	}
	else
	{
		debug.FW_warning("D3DXLoadMeshFromX Warning in ModelLoader_X", FW_debugType::LOGS, FW_debugType::NOTHING);
		return false;
	}
}

bool ModelLoader_X::ModelLoader_X_deallocated()
{
	delete m_D3DMaterial;
	delete m_D3DTexture;

	return true;
}

void ModelLoader_X::ModelLoader_X_render(LPDIRECT3DDEVICE9 D3DDevice)
{
	//Transformation
	D3DXMATRIX scaleMatrix;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX transMatrix;

	D3DXMatrixScaling(&scaleMatrix, m_modelVector.scale.x, m_modelVector.scale.y, m_modelVector.scale.z);
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_modelVector.rotation.x, m_modelVector.rotation.y, m_modelVector.rotation.z);
	D3DXMatrixTranslation(&transMatrix, m_modelVector.position.x, m_modelVector.position.y, m_modelVector.position.z);

	D3DXMatrixMultiply(&transMatrix, &scaleMatrix, &transMatrix);
	D3DXMatrixMultiply(&transMatrix, &rotationMatrix, &transMatrix);

	D3DDevice->SetTransform(D3DTS_WORLD, &transMatrix);

	//Render model
	for (DWORD i = 0; i < m_materialCount; i++)
	{
		D3DDevice->SetMaterial(&m_D3DMaterial[i]);
		if (m_D3DTexture[i] == NULL)
			D3DDevice->SetTexture(0, m_D3DTexture[i]);

		m_D3DMesh->DrawSubset(i);
	}
}

//Methods
//set
void ModelLoader_X::ModelLoader_X_setRotation(float x, float y, float z)
{
	m_modelVector.rotation = D3DXVECTOR3(x, y, z);
}

void ModelLoader_X::ModelLoader_X_setPosition(float x, float y, float z)
{
	m_modelVector.position = D3DXVECTOR3(x, y, z);
}

void ModelLoader_X::ModelLoader_X_setScale(float scale)
{
	m_modelVector.scale = D3DXVECTOR3(scale, scale, scale);
}

//get
D3DXVECTOR3 ModelLoader_X::ModelLoader_X_getScale()
{
	return m_modelVector.scale;
}

D3DXVECTOR3 ModelLoader_X::ModelLoader_X_getRotation()
{
	return m_modelVector.rotation;
}

D3DXVECTOR3 ModelLoader_X::ModelLoader_X_getPosition()
{
	return m_modelVector.position;
}