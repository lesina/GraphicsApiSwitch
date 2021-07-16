#include "RenderApiManager.h"

RenderApiManager* RenderApiManager::m_pInstance = nullptr;

RenderApiManager::RenderApiManager()
	: m_CurrentRenderApi(ERenderAPI::erapi_D3D11)
{
}

RenderApiManager::~RenderApiManager()
{
}

void RenderApiManager::Process()
{
	switch (m_CurrentRenderApi)
	{
	case ERenderAPI::erapi_D3D11:
		break;
	case ERenderAPI::erapi_Opengl:
		break;
	default:
		break;
	}
}

void RenderApiManager::InitRender()
{
	InitD3D11();
	InitOpenGL();
}

void RenderApiManager::InitD3D11()
{
	ASSERT_NOT_IMPLEMENTED;
}

void RenderApiManager::InitOpenGL()
{
	ASSERT_NOT_IMPLEMENTED;
}

RenderApiManager* RenderApiManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new RenderApiManager();
	}

	return m_pInstance;
}

void RenderApiManager::SwitchRenderAPINext()
{
	static UINT32 nNumberOfSupportedApi = static_cast<UINT32>(ERenderAPI::erapi_NumberOfSupportedApi);
	UINT32 nNewRenderApi = (static_cast<UINT32>(m_CurrentRenderApi) + 1) % nNumberOfSupportedApi;
	m_CurrentRenderApi = static_cast<ERenderAPI>(nNewRenderApi);
}

void RenderApiManager::SwitchRenderAPIPrev()
{
	static UINT32 nNumberOfSupportedApi = static_cast<UINT32>(ERenderAPI::erapi_NumberOfSupportedApi);
	UINT32 nNewRenderApi = (static_cast<UINT32>(m_CurrentRenderApi) - 1) % nNumberOfSupportedApi;
	m_CurrentRenderApi = static_cast<ERenderAPI>(nNewRenderApi);
}