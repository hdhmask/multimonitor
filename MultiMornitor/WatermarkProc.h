#pragma once

#include "TMWatermarkManage.h"
#define MUTEX_TIMEOUT 3000
class CWatermarkProc
{
public:
	CWatermarkProc(void);
	~CWatermarkProc(void);

	int Start(RECT rt, LPCTSTR szIniFilename, int nCount = 0);
	void End();
		
	//����ȭ ���� ���
	static CRITICAL_SECTION& GetSync();

	//����ȭ ����
	static VOID StartSync(void);

	//����ȭ ��
	static VOID EndSync(void);

	//CMutex *m_pWatermarkMutex;
	CTMWatermarkManage m_Watermark;
	HANDLE m_hWatermarkThread;

	RECT m_rt;
	TCHAR m_szIniFilename[MAX_PATH];
	int m_nCount;

	static HWND m_hWatermarkWindow;
	static BOOL bLoopRunning;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK OwnerWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static DWORD CALLBACK WatermarkThread(LPVOID lpThreadParameter);
};
