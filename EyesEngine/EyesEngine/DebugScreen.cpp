/////////////////////////////INCLUDE/////////////////////////
#include "DebugScreen.h"
/////////////////////////////////////////////////////////////

using namespace std;

/*
**Class DebugScreen
*/
/////////////////////////////////////////////////////////////
///		PUBLIC
/////////////////////////////////////////////////////////////
DebugScreen::DebugScreen()
{	}

DebugScreen::~DebugScreen()
{	}

bool DebugScreen::DebugScreen_initialized(LPDIRECT3DDEVICE9 D3DDevice, FW_Debug debug)
{
	m_fontSize = 21;

	//Create Font
	D3DXCreateFont(D3DDevice,            // D3D device
		m_fontSize,               // Height
		0,                     // Width
		FW_NORMAL,             
		1,                     // MipLevels, 0 = autogen mipmaps
		FALSE,                 // Italic
		DEFAULT_CHARSET,       // CharSet
		OUT_DEFAULT_PRECIS,    // OutputPrecision
		DEFAULT_QUALITY,       // Quality
		DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
		"Arial",              // pFaceName
		&m_font);              // ppFont

	SetRect(&m_rectanglePosition[0], 2, 0, 0, 0);
	SetRect(&m_rectanglePosition[1], 2, m_fontSize * 1, 0, 0);
	SetRect(&m_rectanglePosition[2], 2, m_fontSize * 2, 0, 0);
	SetRect(&m_rectanglePosition[3], 2, m_fontSize * 3, 0, 0);

	return true;
}

void DebugScreen::updateRender(float elapsedTime, D3DXVECTOR3 entityPos)
{
	//Calculate FPS (Frame per second)
	if (m_coolDown.CoolDown_time(elapsedTime, 1.0f))
	{
		m_lastFrameRate = m_frameRate;
		m_frameRate = 0;
	}
	m_frameRate++;

	//Update Player/Camera position
	m_entityPos = entityPos;
}

void DebugScreen::updateLogic(float elapsedTime)
{
	//Calculate FPS (Frame per second for logic)
	if (m_coolDownCPU.CoolDown_time(elapsedTime, 1.0f))
	{
		m_lastFrameRateCPU = m_frameRateCPU;
		m_frameRateCPU = 0;
	}
	m_frameRateCPU++;
}

void DebugScreen::DebugScreen_draw()
{
	//FPS
	m_font->DrawText(NULL, ("Frames Per Second (GPU): " + to_string(m_lastFrameRate)).c_str(), -1, &m_rectanglePosition[0], DT_NOCLIP, D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));
	m_font->DrawText(NULL, ("Frames Per Second (CPU): " + to_string(m_lastFrameRateCPU)).c_str(), -1, &m_rectanglePosition[1], DT_NOCLIP, D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));

	//Entity
	m_font->DrawText(NULL, ("x: " + to_string(m_entityPos.x) + " y: " + to_string(m_entityPos.y) + " z: " + to_string(m_entityPos.z)).c_str(), -1, &m_rectanglePosition[2], DT_NOCLIP, D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));
}