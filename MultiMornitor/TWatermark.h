#pragma once

//#include "TMWatermarkManage.h"
#include <vector>
//#include <iterator>
#include "WatermarkProc.h"
#define MORNITOR_MAX_COUNT 20
#define WATERMARK_RENEW_DELAY 1000

class CTWatermark
{
public:
	CTWatermark(void);
	~CTWatermark(void);

	DWORD StartWatermark(LPCTSTR szIniFilename, BOOL bSplitMode = FALSE);
	DWORD EndWatermark();
	
	static std::vector<RECT> m_vWateramrkArea;
	static RECT m_rcFull;
	static CWatermarkProc* m_WaterProc[MORNITOR_MAX_COUNT];
	static BOOL	m_bThreadRunning;
	
	BOOL m_bSplitMode;
private:
	//CTMWatermarkManage m_Watermark;
	HANDLE m_hWatermarkThread;
	//HWND m_hWatermarkWindow;
	TCHAR m_szInipath[MAX_PATH];

	static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	//static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//static LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//static LRESULT CALLBACK OwnerWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//static LRESULT CALLBACK OwnerWndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static DWORD CALLBACK WatermarkThread(LPVOID lpThreadParameter);
};
