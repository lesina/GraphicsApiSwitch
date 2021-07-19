#pragma once

#include "../CommonUtils.h"
#include "../Box.h"
#include "D3D12/D3D12RenderBackend.h"
#include "Camera.h"

class RenderApiManager
{
	enum ERenderAPI
	{
		erapi_D3D12 = 0,
		erapi_OpengGL4,

		erapi_NumberOfSupportedApi
	};

public:
	static RenderApiManager* GetInstance();

	void InitRender(
		HWND hwnd,
		int nClientWidth,
		int nClientHeight
	);

	void Process(
		std::vector<Box>* Boxes
	);
	void SwitchRenderAPINext();
	void SwitchRenderAPIPrev();
	void OnResize(
		int nClientWidth,
		int nClientHeight
	);

	void UpdateCamera(
		float fRadiusDiff,
		float fThetaDiff,
		float fPhiDiff
	);

private:
	RenderApiManager();

	RenderApiManager(
		const RenderApiManager& rhs
	) = delete;

	RenderApiManager& operator=(
		const RenderApiManager& rhs
		) = delete;

	~RenderApiManager();

	void InitOpenGL();

	static RenderApiManager* m_pInstance;

	ERenderAPI m_CurrentRenderApi;

	D3D12RenderBackend* d3d12RenderBackend;

	Camera* m_Camera;
};

