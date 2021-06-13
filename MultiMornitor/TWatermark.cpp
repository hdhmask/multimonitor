#include "StdAfx.h"
#include "TWatermark.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

std::vector<RECT> CTWatermark::m_vWateramrkArea;
RECT CTWatermark::m_rcFull;
CWatermarkProc* CTWatermark::m_WaterProc[MORNITOR_MAX_COUNT] = {0, };
BOOL CTWatermark::m_bThreadRunning = FALSE;

CTWatermark::CTWatermark(void):m_hWatermarkThread(NULL), m_bSplitMode(FALSE)//, m_hWatermarkWindow(NULL)m_Watermark(), 
{
	m_szInipath[0] = 0;
}

CTWatermark::~CTWatermark(void)
{
	for(int i = 0; i < MORNITOR_MAX_COUNT; i++)
	{
		if(m_WaterProc[i] != NULL)
		{
			m_WaterProc[i]->End();
			delete m_WaterProc[i];
			m_WaterProc[i] = NULL;
		}
	}
}

DWORD CTWatermark::StartWatermark(LPCTSTR szIniFilename, BOOL bSplitMode)
{
	m_bThreadRunning = TRUE;
	m_bSplitMode = bSplitMode;

	_tcscpy_s(m_szInipath, MAX_PATH, szIniFilename);
	if(m_hWatermarkThread == NULL)
	{
		m_hWatermarkThread = ::CreateThread(NULL, 0, WatermarkThread, this, 0, NULL);
		if(m_hWatermarkThread == NULL)
			return -1;
	}
	return 0;
}

DWORD CTWatermark::EndWatermark()
{
	for(int i = 0; i < MORNITOR_MAX_COUNT; i++)
	{
		if(m_WaterProc[i] != NULL)
		{
			m_WaterProc[i]->End();
			delete m_WaterProc[i];
			m_WaterProc[i] = NULL;
		}
	}

	if(m_hWatermarkThread != NULL)
	{
		m_bThreadRunning = FALSE;
		WaitForSingleObject(m_hWatermarkThread, 5000);
		//::TerminateThread(m_hWatermarkThread, 0);
		CloseHandle(m_hWatermarkThread);
		m_hWatermarkThread = NULL;
		m_szInipath[0] = 0;
	}
	return 0;
}

BOOL CTWatermark::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	std::vector< RECT >* pvRect = (std::vector< RECT >*)dwData;

	MONITORINFOEX mi;
	mi.cbSize = sizeof(MONITORINFOEX);

	GetMonitorInfo(hMonitor, &mi);

	RECT rt;
	rt.top = lprcMonitor->top + 2;
	rt.bottom = lprcMonitor->bottom - 2;
	rt.left = lprcMonitor->left + 2;
	rt.right = lprcMonitor->right - 2;

	pvRect->push_back(rt);

	if(m_rcFull.top > lprcMonitor->top)
		m_rcFull.top = lprcMonitor->top + 2;
	if(m_rcFull.left > lprcMonitor->left)
		m_rcFull.left = lprcMonitor->left + 2;
	if(m_rcFull.bottom < lprcMonitor->bottom)
		m_rcFull.bottom = lprcMonitor->bottom - 2;
	if(m_rcFull.right < lprcMonitor->right)
		m_rcFull.right = lprcMonitor->right - 2;

	return TRUE;
}

DWORD CTWatermark::WatermarkThread(LPVOID lpThreadParameter)
{
	CTWatermark *pThis = (CTWatermark*)lpThreadParameter;

	BOOL bCalledWatermark = FALSE;
	BOOL bDisplayChanged = FALSE;
	std::vector<RECT> vWateramrkAreaTemp;
	UINT nMornitorCountTemp = 0;
	RECT rtTemp = {0, };
	
	for(int i = 0; i < MORNITOR_MAX_COUNT; i++)
	{
		m_WaterProc[i] = NULL;
	}

	while(m_bThreadRunning)
	{
		m_vWateramrkArea.clear();
		m_rcFull.top = 0;
		m_rcFull.bottom = 0;
		m_rcFull.left = 0;
		m_rcFull.right = 0;

		::EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&m_vWateramrkArea);
		
		//���÷��� ���� üũ ��ƾ
		bDisplayChanged = FALSE;
		
		if(pThis->m_bSplitMode == FALSE)
		{
			RECT rt = {0, };
			rt.top = m_rcFull.top;
			rt.bottom = m_rcFull.bottom;
			rt.left = m_rcFull.left;
			rt.right = m_rcFull.right;
			
			if(bCalledWatermark == FALSE)
			{
				m_WaterProc[0] = new CWatermarkProc();
				m_WaterProc[0]->Start(rt, pThis->m_szInipath, 0);
				bCalledWatermark = TRUE;
				//save before rect
				rtTemp.top = rt.top;
				rtTemp.bottom = rt.bottom;
				rtTemp.left = rt.left;
				rtTemp.right = rt.right;
				Sleep(WATERMARK_RENEW_DELAY);
				continue;
			}
			else
			{
				//compare size
				if(rtTemp.top != rt.top)
					bDisplayChanged = TRUE;
				if(rtTemp.bottom != rt.bottom)
					bDisplayChanged = TRUE;
				if(rtTemp.left != rt.left)
					bDisplayChanged = TRUE;
				if(rtTemp.right != rt.right)
					bDisplayChanged = TRUE;

				//if size is changed
				if(bDisplayChanged == TRUE)
				{
					if(m_WaterProc[0] != NULL)
					{
						m_WaterProc[0]->End();
						delete m_WaterProc[0];
						m_WaterProc[0] = NULL;
					}
					m_WaterProc[0] = new CWatermarkProc();
					m_WaterProc[0]->Start(rt, pThis->m_szInipath, 0);
						
					//last size update
					rtTemp.top = rt.top;
					rtTemp.bottom = rt.bottom;
					rtTemp.left = rt.left;
					rtTemp.right = rt.right;
				}
			}
			Sleep(WATERMARK_RENEW_DELAY);
			continue;
		}
		
		UINT nMornitorCount = m_vWateramrkArea.size();
		//����� ���� ���͸�ũ ���� ��
		//ó�� ȣ���
		if(bCalledWatermark == FALSE)
		{
			for(UINT i = 0; i < nMornitorCount; i++)
			{
				RECT rt = m_vWateramrkArea[i];
				m_WaterProc[i] = new CWatermarkProc();
				m_WaterProc[i]->Start(rt, pThis->m_szInipath, i);
				//Sleep(1000);
			}
			bCalledWatermark = TRUE;
			nMornitorCountTemp = nMornitorCount;
			vWateramrkAreaTemp.resize((int)(m_vWateramrkArea.size()));
			std::copy( m_vWateramrkArea.begin(), m_vWateramrkArea.end(), vWateramrkAreaTemp.begin() );
			Sleep(WATERMARK_RENEW_DELAY);
			continue;
		}
		else
		{
			//����� ���ŵ� ��� ���� ����̴�. 
			if(nMornitorCountTemp != nMornitorCount)
				bDisplayChanged = TRUE;
			else //����� ������ ��� �ػ󵵸� ���Ѵ�. (�ϳ��� ����Ǹ� �����Ѵ�. )
			{
				for(UINT i = 0; i < nMornitorCount; i++)
				{
					if(vWateramrkAreaTemp[i].top != m_vWateramrkArea[i].top)
					{
						bDisplayChanged = TRUE;
						break;
					}
					if(vWateramrkAreaTemp[i].bottom != m_vWateramrkArea[i].bottom)
					{
						bDisplayChanged = TRUE;
						break;
					}
					if(vWateramrkAreaTemp[i].left != m_vWateramrkArea[i].left)
					{
						bDisplayChanged = TRUE;
						break;
					}
					if(vWateramrkAreaTemp[i].right != m_vWateramrkArea[i].right)
					{
						bDisplayChanged = TRUE;
						break;
					}
				}
			}
		}
		//���÷��� ���� ������ ������ ���
		if(bDisplayChanged == TRUE)
		{
			//(���� ���͸�ũ ������ ��ü ���� üũ �� ����)
			for(int i = 0; i < MORNITOR_MAX_COUNT; i++)
			{
				if(m_WaterProc[i] != NULL)
				{
					m_WaterProc[i]->End();
					delete m_WaterProc[i];
					m_WaterProc[i] = NULL;
				}
			}
			//��ü �����
			for(UINT i = 0; i < nMornitorCount; i++)
			{
				RECT rt = m_vWateramrkArea[i];
				m_WaterProc[i] = new CWatermarkProc();
				m_WaterProc[i]->Start(rt, pThis->m_szInipath, i);
				//Sleep(1000);
			}
			
			//����� ī��Ʈ �� ������ ����
			nMornitorCountTemp = nMornitorCount;
			vWateramrkAreaTemp.resize((int)(m_vWateramrkArea.size()));
			std::copy( m_vWateramrkArea.begin(), m_vWateramrkArea.end(), vWateramrkAreaTemp.begin() );
		}
		Sleep(WATERMARK_RENEW_DELAY);
	}

	//recheck
	for(int i = 0; i < MORNITOR_MAX_COUNT; i++)
	{
		if(m_WaterProc[i] != NULL)
		{
			m_WaterProc[i]->End();
			delete m_WaterProc[i];
			m_WaterProc[i] = NULL;
		}
	}

	return 0;
}