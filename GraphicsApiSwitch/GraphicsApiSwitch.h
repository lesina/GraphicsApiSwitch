#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "Box.h"
#include "CommonUtils.h"
#include "InputHandler.h"
#include "Render/RenderApiManager.h"

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
	static InputHandler* GetInputHandler();
	static RenderApiManager* GetRenderApiManager();

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

	bool InitMainWindow();
	void InitRender();

	void ProcessInputCommands();

	void OnMouseMove(
		WPARAM btnState,
		int x,
		int y
	);
	void OnMouseDown(
		WPARAM btnState,
		int x,
		int y
	);
	void OnMouseUp(
		WPARAM btnState,
		int x,
		int y
	);

	static GraphicsApiSwitchApp* m_App;
	static InputHandler* m_pInputHandler;
	static RenderApiManager* m_pRenderApiManager;

	HINSTANCE m_hAppInst;
	HWND m_hMainWnd;

	int m_nClientWidth;
	int m_nClientHeight;
	const int m_nMinClientWidth;
	const int m_nMinClientHeight;

	std::wstring m_szTitle;
	std::wstring m_szWindowClass;

	bool m_bAppPaused;

	POINT m_LastMousePos;

	std::vector<Box>* m_Boxes;
};