#include "StdAfx.h"
#include "WatermarkProc.h"

HWND CWatermarkProc::m_hWatermarkWindow = NULL;
//HWND m_hWatermarkWindow = NULL;
BOOL CWatermarkProc::bLoopRunning = FALSE;

//동기화 변수 얻기
CRITICAL_SECTION& CWatermarkProc::GetSync()
{
	static CRITICAL_SECTION cs;
	static BOOL bInit = FALSE;
	if(bInit == FALSE)
	{
		::InitializeCriticalSection(&cs);
		bInit = TRUE;
	}
	return cs;
}

//동기화 시작
VOID CWatermarkProc::StartSync(void)
{
	::EnterCriticalSection(&GetSync());
}

//동기화 끝
VOID CWatermarkProc::EndSync(void)
{
	::LeaveCriticalSection(&GetSync());
}

CWatermarkProc::CWatermarkProc(void) : m_hWatermarkThread(NULL), m_nCount(0)//, m_pWatermarkMutex(NULL)
{
	m_rt.top = 0;
	m_rt.bottom = 0;
	m_rt.left = 0;
	m_rt.right = 0;
	memset(m_szIniFilename, sizeof(m_szIniFilename), 0);
	
	//m_pWatermarkMutex = new CMutex(FALSE,_T("Global\\FULLWATERMARKPROCSYNC123!@#"));
}

CWatermarkProc::~CWatermarkProc(void)
{
	if(m_hWatermarkWindow != NULL)
	{
		StartSync();
		m_Watermark.TMW_EndWatermarkByHWnd(m_hWatermarkWindow);
		EndSync();
		//m_Watermark.TMW_Final();
		SendMessage(m_hWatermarkWindow, WM_DESTROY, NULL, NULL);
		WaitForSingleObject(m_hWatermarkThread, 3000);
		CloseHandle(m_hWatermarkThread);
		m_hWatermarkWindow = NULL;
	}
}

int CWatermarkProc::Start(RECT rt, LPCTSTR szIniFilename, int nCount)
{
	m_rt = rt;
	_tcscpy_s(m_szIniFilename, MAX_PATH, szIniFilename);
    m_nCount = nCount;

	if(m_hWatermarkThread == NULL)
	{
		m_hWatermarkThread = ::CreateThread(NULL, 0, WatermarkThread, this, 0, NULL);
		if(m_hWatermarkThread == NULL)
			return -1;
	}
	return 0;
}

void CWatermarkProc::End()
{
	if(m_hWatermarkWindow != NULL)
	{
		StartSync();
		m_Watermark.TMW_EndWatermarkByHWnd(m_hWatermarkWindow);
		EndSync();
		//m_Watermark.TMW_Final();
		SendMessage(m_hWatermarkWindow, WM_DESTROY, NULL, NULL);
		WaitForSingleObject(m_hWatermarkThread, 3000);
		CloseHandle(m_hWatermarkThread);
		m_hWatermarkWindow = NULL;
	}
}

DWORD CWatermarkProc::WatermarkThread(LPVOID lpThreadParameter)
{
	CWatermarkProc *pThis = (CWatermarkProc*)lpThreadParameter;

	//if(pThis->m_pWatermarkMutex->Lock(MUTEX_TIMEOUT))
	StartSync();
	//{
		DWORD dwVal = pThis->m_Watermark.TMW_Init();

		TCHAR szWindowClass[256] = {0, };
		wsprintf(szWindowClass, _T("TWatermark_%d"), pThis->m_nCount);

		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= (HINSTANCE)&__ImageBase;
		wcex.hIcon			= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= szWindowClass;
		wcex.hIconSm		= NULL;
		::RegisterClassEx(&wcex);

		TCHAR szOwnerWindowClass[256] = {0, };
		wsprintf(szOwnerWindowClass, _T("TWatermarkOwner_%d"), pThis->m_nCount);

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= OwnerWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= (HINSTANCE)&__ImageBase;
		wcex.hIcon			= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= szOwnerWindowClass;
		wcex.hIconSm		= NULL;
		::RegisterClassEx(&wcex);

		HWND hOwner = CreateWindowEx(WS_EX_NOACTIVATE, szOwnerWindowClass, _T(""), WS_POPUP
			, pThis->m_rt.left, pThis->m_rt.top, pThis->m_rt.right - pThis->m_rt.left, pThis->m_rt.bottom - pThis->m_rt.top, NULL, NULL, (HINSTANCE)&__ImageBase, NULL);
		m_hWatermarkWindow = CreateWindowEx(WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED | WS_EX_TRANSPARENT, szWindowClass, _T(""), WS_POPUP
			, pThis->m_rt.left, pThis->m_rt.top, pThis->m_rt.right - pThis->m_rt.left, pThis->m_rt.bottom - pThis->m_rt.top, hOwner, NULL, (HINSTANCE)&__ImageBase, NULL);
		
		::ShowWindow(m_hWatermarkWindow, SW_SHOW);
		::UpdateWindow(m_hWatermarkWindow);

		pThis->m_Watermark.TMW_SetConfigByHWnd(m_hWatermarkWindow, pThis->m_szIniFilename);
		pThis->m_Watermark.TMW_StartWatermarkByHWnd(m_hWatermarkWindow);

		bLoopRunning = TRUE;

		//pThis->m_pWatermarkMutex->Unlock();
	//}	
	EndSync();

	MSG msg;
	while(::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
		if(bLoopRunning == FALSE)
			break;
	}

	return (int)msg.wParam;
}

LRESULT CWatermarkProc::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static UINT nTaskbarCreated = 0;
	static UINT nTaskbarButtonCreated = 0;
	static CRect rectTemp;
	static BOOL bEnumDisplayCalled = FALSE;
	if(message == nTaskbarCreated || message == nTaskbarButtonCreated)
	{
		::ShowWindow(hWnd, SW_HIDE);
		return 1;
	}

	switch (message)
	{
	case WM_CREATE:
		::SetTimer(hWnd, 1, 3000, NULL);
		nTaskbarCreated = ::RegisterWindowMessage(_T("TaskbarCreated"));
		nTaskbarButtonCreated = ::RegisterWindowMessage(_T("TaskbarButtonCreated"));
		break;
	case WM_TIMER:
		switch (wParam) 
		{
		case 1:
			::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE);
			::ShowWindow(hWnd, SW_SHOW);
			break;
		}

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		bLoopRunning = FALSE;
		if(m_hWatermarkWindow != NULL)
		{
			DestroyWindow(m_hWatermarkWindow);
			m_hWatermarkWindow = NULL;
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CWatermarkProc::OwnerWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
