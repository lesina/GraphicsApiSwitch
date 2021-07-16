// GraphicsApiSwitch.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "GraphicsApiSwitch.h"

LRESULT CALLBACK
MainWndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return GraphicsApiSwitchApp::GetApp()->MsgProc(hwnd, msg, wParam, lParam);
}

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow
)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		GraphicsApiSwitchApp theApp(hInstance);
		if (!theApp.Initialize())
			return 0;

		return theApp.Run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}


GraphicsApiSwitchApp* GraphicsApiSwitchApp::m_App = nullptr;
GraphicsApiSwitchApp* GraphicsApiSwitchApp::GetApp()
{
	return m_App;
}

HINSTANCE GraphicsApiSwitchApp::AppInst()const
{
	return m_hAppInst;
}

HWND GraphicsApiSwitchApp::MainWnd()const
{
	return m_hMainWnd;
}

GraphicsApiSwitchApp::GraphicsApiSwitchApp(
	HINSTANCE hInstance
) :	m_hAppInst(hInstance),
	m_hMainWnd(nullptr),
	m_nClientHeight(600),
	m_nClientWidth(800),
	m_nMinClientWidth(200),
	m_nMinClientHeight(200),
	m_szTitle(L"GraphicsApiSwitch"),
	m_szWindowClass(L"GraphicsApiSwitch"),
	m_bAppPaused(false)
{
	// Only one GraphicsApiSwitchApp can be constructed.
	assert(m_App == nullptr);
	m_App = this;
}

GraphicsApiSwitchApp::~GraphicsApiSwitchApp()
{
}

bool GraphicsApiSwitchApp::Initialize()
{
	if (!InitMainWindow())
		return false;

	return true;
}

bool GraphicsApiSwitchApp::InitMainWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = m_szWindowClass.c_str();

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, m_nClientWidth, m_nClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	m_hMainWnd = CreateWindow(m_szWindowClass.c_str(), m_szTitle.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, m_hAppInst, 0);
	if (!m_hMainWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);

	return true;
}

LRESULT GraphicsApiSwitchApp::MsgProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (msg)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			m_bAppPaused = true;
		}
		else
		{
			m_bAppPaused = false;
		}
		return 0;

		// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		m_nClientWidth = LOWORD(lParam);
		m_nClientHeight = HIWORD(lParam);
		return 0;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		m_bAppPaused = true;
		return 0;

		// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	case WM_EXITSIZEMOVE:
		m_bAppPaused = false;
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = m_nMinClientWidth;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = m_nMinClientHeight;
		return 0;

	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}

		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int GraphicsApiSwitchApp::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!m_bAppPaused)
			{
				Update();
				Draw();
			}
			else
			{
				Sleep(100);
			}
		}
	}

	return (int)msg.wParam;
}

void GraphicsApiSwitchApp::Update()
{
	ASSERT_NOT_IMPLEMENTED;
}

void GraphicsApiSwitchApp::Draw()
{
	ASSERT_NOT_IMPLEMENTED;
}

void GraphicsApiSwitchApp::OnKeyboardInput()
{
	ASSERT_NOT_IMPLEMENTED;
}
