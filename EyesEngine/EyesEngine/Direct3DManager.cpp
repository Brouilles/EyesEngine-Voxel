/////////////////////////////INCLUDE/////////////////////////
#include "Direct3DManager.h"
/////////////////////////////////////////////////////////////

/*
**Class Direct3DManager
*/

Direct3DManager::Direct3DManager() : m_D3D9(nullptr), m_D3Ddevice(nullptr)
{}

Direct3DManager::~Direct3DManager()
{
	Direct3DManager_deallocated();
}

void Direct3DManager::Direct3DManager_initialized(HWND hWnd, FW_Debug debug, bool fullscreen, int windowHeight, int windowWidth)
{
	HRESULT result;

	//DirectX Interface
	m_D3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_D3D9 == NULL)
		debug.FW_error("Game_initialized: Direct3DCreate9(D3D_SDK_VERSION) FAILED", FW_debugType::WINDOW, FW_debugType::LOGS);

	//Filling D3DPRESENT_PARAMETERS
	D3DPRESENT_PARAMETERS D3Dpp;
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));
	D3Dpp.hDeviceWindow = hWnd;
	D3Dpp.BackBufferHeight = windowHeight;
	D3Dpp.BackBufferWidth = windowWidth;
	D3Dpp.Windowed = !fullscreen;
	D3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3Dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	D3Dpp.EnableAutoDepthStencil = TRUE;
	D3Dpp.AutoDepthStencilFormat = D3DFMT_D16;
	D3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //Disable FPS limit
	//D3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//Get configuration
	debug.FW_success("///////// COMPUTER HARDWARE /////////", FW_debugType::LOGS, FW_debugType::NOTHING);
	D3DADAPTER_IDENTIFIER9 adapterId;
	m_D3D9->GetAdapterIdentifier(0, 0, &adapterId);

	char aboutHardware[512];

	/*memset(aboutHardware, 0, sizeof(aboutHardware));
	memset(manufacturer, 0, sizeof(manufacturer));*/

	strcpy_s(aboutHardware, adapterId.Driver); //Driver DLL
	debug.FW_success(aboutHardware, FW_debugType::LOGS, FW_debugType::NOTHING);

	strcpy_s(aboutHardware, adapterId.Description); //GPU
	debug.FW_success(aboutHardware, FW_debugType::LOGS, FW_debugType::NOTHING);

	debug.FW_success("/////////	END	/////////", FW_debugType::LOGS, FW_debugType::NOTHING);

	//Create Device
	char *token;
	if (strtok_s(aboutHardware, "AMD", &token) == NULL)
	{
		debug.FW_success("Game_initialized: AMD so D3DCREATE_SOFTWARE_VERTEXPROCESSING", FW_debugType::NOTHING, FW_debugType::LOGS);
		m_D3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3Dpp, &m_D3Ddevice); //D3DCREATE_SOFTWARE_VERTEXPROCESSING
	}
	else
	{
		debug.FW_success("Game_initialized: D3DCREATE_HARDWARE_VERTEXPROCESSING", FW_debugType::NOTHING, FW_debugType::LOGS);
		m_D3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3Dpp, &m_D3Ddevice);
	}

	/*
	m_D3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vertexProcessing, &D3Dpp, &m_D3Ddevice); //D3DCREATE_MIXED_VERTEXPROCESSING 
	/*if (FAILED(m_D3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &D3Dpp, &m_D3Ddevice)))
	{
		debug.FW_warning("Game_initialized: CreateDevice(D3DCREATE_HARDWARE_VERTEXPROCESSING) FAILED", FW_debugType::WINDOW, FW_debugType::LOGS);
		if (FAILED(m_D3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3Dpp, &m_D3Ddevice)))
			debug.FW_error("Game_initialized: CreateDevice(D3DCREATE_SOFTWARE_VERTEXPROCESSING) FAILED", FW_debugType::WINDOW, FW_debugType::LOGS);
		else
			debug.FW_success("Game_initialized: CreateDevice(D3DCREATE_SOFTWARE_VERTEXPROCESSING)", FW_debugType::NOTHING, FW_debugType::LOGS);
	}
	else
		debug.FW_success("Game_initialized: CreateDevice(D3DCREATE_HARDWARE_VERTEXPROCESSING)", FW_debugType::NOTHING, FW_debugType::LOGS);*/
	
	//D3Device render
	m_D3Ddevice->SetRenderState(D3DRS_ZENABLE, TRUE); // z-buffer 

	m_D3Ddevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
	m_D3Ddevice->SetRenderState(D3DRS_LIGHTING, FALSE); //Light
	// 0xffffffff-bof 0x00202020-Night






	//m_D3Ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);    // Enable Alpha blend
	/*m_D3Ddevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3Ddevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_D3Ddevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_D3Ddevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_D3Ddevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_D3Ddevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_D3Ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_D3Ddevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);*/

	//m_D3Ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); //WireFrame render

	debug.FW_success("Game_initialized: Direct3DManager_initialized", FW_debugType::LOGS, FW_debugType::NOTHING);
}

bool Direct3DManager::Direct3DManager_deallocated()
{
	m_D3Ddevice->Release();
	m_D3D9->Release();

	return true;
}

void Direct3DManager::Direct3DManager_restore()
{
	m_D3Ddevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	m_D3Ddevice->BeginScene();
}

void Direct3DManager::Direct3DManager_clear()
{
	m_D3Ddevice->EndScene();
	m_D3Ddevice->Present(NULL, NULL, NULL, NULL);
}

//Methods
LPDIRECT3DDEVICE9 Direct3DManager::Direct3DManager_getD3Ddevice()
{
	return m_D3Ddevice;
}