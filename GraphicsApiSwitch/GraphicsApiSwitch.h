#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "CommonUtils.h"

class GraphicsApiSwitchApp
{
public:
	GraphicsApiSwitchApp(
		HINSTANCE hInstance
	);

	GraphicsApiSwitchApp(
		const GraphicsApiSwitchApp& rhs
	) = delete;

	GraphicsApiSwitchApp& operator=(
		const GraphicsApiSwitchApp& rhs
		) = delete;

	~GraphicsApiSwitchApp();

	bool Initialize();

	static GraphicsApiSwitchApp* GetApp();

	HINSTANCE AppInst() const;
	HWND      MainWnd() const;

	int Run();

	LRESULT MsgProc(
		HWND hwnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam
	);

private:
	void Update();
	void Draw();

	void OnKeyboardInput();

	bool InitMainWindow();

	static GraphicsApiSwitchApp* m_App;

	HINSTANCE m_hAppInst;
	HWND m_hMainWnd;

	int m_nClientWidth;
	int m_nClientHeight;

	const int m_nMinClientWidth;
	const int m_nMinClientHeight;

	std::wstring m_szTitle;
	std::wstring m_szWindowClass;

	bool m_bAppPaused;
};