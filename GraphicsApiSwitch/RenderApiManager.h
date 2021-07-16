#pragma once

#include "CommonUtils.h"

class RenderApiManager
{
	enum ERenderAPI
	{
		erapi_D3D11 = 0,
		erapi_Opengl,
		
		erapi_NumberOfSupportedApi
	};

public:
	static RenderApiManager* GetInstance();

	void InitRender();
	void Process();
	void SwitchRenderAPINext();
	void SwitchRenderAPIPrev();

private:
	RenderApiManager();

	RenderApiManager(
		const RenderApiManager& rhs
	) = delete;

	RenderApiManager& operator=(
		const RenderApiManager& rhs
		) = delete;

	~RenderApiManager();

	void InitD3D11();
	void InitOpenGL();

	static RenderApiManager* m_pInstance;

	ERenderAPI m_CurrentRenderApi;
};

