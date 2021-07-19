#include "RenderApiManager.h"

RenderApiManager* RenderApiManager::m_pInstance = nullptr;

RenderApiManager::RenderApiManager()
	:
	m_CurrentRenderApi(ERenderAPI::erapi_D3D12),
	d3d12RenderBackend(nullptr)
{
	m_Camera = new Camera();
}

RenderApiManager::~RenderApiManager()
{
}

void RenderApiManager::Process(
	std::vector<Box>* Boxes
)
{
	switch (m_CurrentRenderApi)
	{
	case ERenderAPI::erapi_D3D12:
		d3d12RenderBackend->Draw(m_Camera->GetRadius(), m_Camera->GetPhi(), m_Camera->GetTheta(), Boxes);
		break;
	case ERenderAPI::erapi_OpengGL4:
		break;
	default:
		break;
	}
}

void RenderApiManager::InitRender(
	HWND hwnd,
	int nClientWidth,
	int nClientHeight
)
{
	d3d12RenderBackend = new D3D12RenderBackend(hwnd, nClientWidth, nClientHeight);
	InitOpenGL();
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

void RenderApiManager::OnResize(
	int nClientWidth,
	int nClientHeight
)
{
	switch (m_CurrentRenderApi)
	{
	case ERenderAPI::erapi_D3D12:
		if (d3d12RenderBackend)
			d3d12RenderBackend->OnResize(nClientWidth, nClientHeight);
		break;
	case ERenderAPI::erapi_OpengGL4:
		break;
	default:
		break;
	}
}

void RenderApiManager::UpdateCamera(
	float fRadiusDiff,
	float fThetaDiff,
	float fPhiDiff
)
{
	m_Camera->Update(fRadiusDiff, fThetaDiff, fPhiDiff);
}
