#include "StdAfx.h"

#include <windows.h>
#include <tchar.h>
#include "TMWatermarkManage.h"
#include "TMWatermark.h"

#ifndef _WIN64
#define TMWATERMARKDLLNAME _T("TMWatermark.dll")
#define TMWATERMARKDLLNAME_UP _T("TMWatermarkUp.dll")
#else
#define TMWATERMARKDLLNAME _T("TMWatermark64.dll")
#define TMWATERMARKDLLNAME_UP _T("TMWatermark64Up.dll")
#endif

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

CTMWatermarkManage::CTMWatermarkManage(void)
: m_hTMWatermarkDLL(NULL)
, m_fnTMW_Init(NULL)
, m_fnTMW_SetConfigByPid(NULL), m_fnTMW_SetWatermarkImageByPid(NULL), m_fnTMW_SetTransparentByPid(NULL), m_fnTMW_SetUsernameByPid(NULL)
, m_fnTMW_SetCopyrightByPid(NULL), m_fnTMW_StartWatermarkByPid(NULL), m_fnTMW_EndWatermarkByPid(NULL)
, m_fnTMW_SetConfigByHWnd(NULL), m_fnTMW_SetWatermarkImageByHWnd(NULL), m_fnTMW_SetTransparentByHWnd(NULL), m_fnTMW_SetUsernameByHWnd(NULL)
, m_fnTMW_SetCopyrightByHWnd(NULL), m_fnTMW_StartWatermarkByHWnd(NULL), m_fnTMW_EndWatermarkByHWnd(NULL)
, m_fnTMW_SetConfigByURL(NULL), m_fnTMW_SetWatermarkImageByURL(NULL), m_fnTMW_SetTransparentByURL(NULL), m_fnTMW_SetUsernameByURL(NULL)
, m_fnTMW_SetCopyrightByURL(NULL), m_fnTMW_StartWatermarkByURL(NULL), m_fnTMW_EndWatermarkByURL(NULL)
, m_fnTMW_Final(NULL)
{
}

CTMWatermarkManage::~CTMWatermarkManage(void)
{
}

// 워터마크모듈 초기화함수
DWORD CTMWatermarkManage::TMW_Init(void)
{
	TCHAR szFileName[MAX_PATH] = {0};
	TCHAR szFileNameUp[MAX_PATH] = {0};
	DWORD dwLen;
	DWORD dwResult;

	if(m_hTMWatermarkDLL != NULL)
		return TMW_ERROR_SUCCESS;

	dwLen = GetModuleFileName((HMODULE)&__ImageBase, szFileName, MAX_PATH);
	GetModuleFileName((HMODULE)&__ImageBase, szFileNameUp, MAX_PATH);

	for(;dwLen>0; dwLen--)
	{
		if(szFileName[dwLen] == _T('\\'))
		{
			szFileName[dwLen+1] = 0;
			_tcscat_s(szFileName, MAX_PATH, TMWATERMARKDLLNAME);
			szFileNameUp[dwLen+1] = 0;
			_tcscat_s(szFileNameUp, MAX_PATH, TMWATERMARKDLLNAME_UP);
			break;
		}
	}

	if(CopyFile(szFileNameUp, szFileName, FALSE) == TRUE)
		DeleteFile(szFileNameUp);

	//dbghelp.dll가 현재 폴더에 이상한 버전이 있는 경우가 있어서 System에서 직접 읽어온다
	TCHAR szSystemDllName[MAX_PATH];
	::SHGetSpecialFolderPath(NULL, szSystemDllName, CSIDL_SYSTEM, 0);
	_tcscat_s(szSystemDllName, MAX_PATH, _T("\\dbghelp.dll"));
	::LoadLibrary(szSystemDllName);

	m_hTMWatermarkDLL = (HMODULE)::LoadLibrary(szFileName);
	if(m_hTMWatermarkDLL == NULL)
	{
		m_hTMWatermarkDLL = (HMODULE)::LoadLibrary(TMWATERMARKDLLNAME);
		if(m_hTMWatermarkDLL == NULL)
		{
			if(!::SHGetSpecialFolderPath(NULL, szFileName, CSIDL_PROGRAM_FILESX86, 0))
				::SHGetSpecialFolderPath(NULL, szFileName, CSIDL_PROGRAM_FILES, 0);
			_tcscat_s(szFileName, MAX_PATH, _T("\\Teruten\\TMWatermark\\"));
			_tcscat_s(szFileName, MAX_PATH, TMWATERMARKDLLNAME);
			m_hTMWatermarkDLL = (HMODULE)::LoadLibrary(szFileName);
			if(m_hTMWatermarkDLL == NULL)
				return ERR_SETUPLIB_LOADING_FAIL;
		}
	}

	m_fnTMW_Init = (FN_TMW_Init)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_Init"));

	m_fnTMW_SetConfigByPid = (FN_TMW_SetConfigByPid)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetConfigByPid"));
	m_fnTMW_SetWatermarkImageByPid = (FN_TMW_SetWatermarkImageByPid)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetWatermarkImageByPid"));
	m_fnTMW_SetTransparentByPid = (FN_TMW_SetTransparentByPid)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetTransparentByPid"));
	m_fnTMW_SetUsernameByPid = (FN_TMW_SetUsernameByPid)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetUsernameByPid"));
	m_fnTMW_SetCopyrightByPid = (FN_TMW_SetCopyrightByPid)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetCopyrightByPid"));
	m_fnTMW_StartWatermarkByPid = (FN_TMW_StartWatermarkByPid)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_StartWatermarkByPid"));
	m_fnTMW_EndWatermarkByPid = (FN_TMW_EndWatermarkByPid)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_EndWatermarkByPid"));

	m_fnTMW_SetConfigByHWnd = (FN_TMW_SetConfigByHWnd)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetConfigByHWnd"));
	m_fnTMW_SetWatermarkImageByHWnd = (FN_TMW_SetWatermarkImageByHWnd)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetWatermarkImageByHWnd"));
	m_fnTMW_SetTransparentByHWnd = (FN_TMW_SetTransparentByHWnd)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetTransparentByHWnd"));
	m_fnTMW_SetUsernameByHWnd = (FN_TMW_SetUsernameByHWnd)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetUsernameByHWnd"));
	m_fnTMW_SetCopyrightByHWnd = (FN_TMW_SetCopyrightByHWnd)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetCopyrightByHWnd"));
	m_fnTMW_StartWatermarkByHWnd = (FN_TMW_StartWatermarkByHWnd)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_StartWatermarkByHWnd"));
	m_fnTMW_EndWatermarkByHWnd = (FN_TMW_EndWatermarkByHWnd)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_EndWatermarkByHWnd"));

	m_fnTMW_SetConfigByURL = (FN_TMW_SetConfigByURL)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetConfigByURL"));
	m_fnTMW_SetWatermarkImageByURL = (FN_TMW_SetWatermarkImageByURL)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetWatermarkImageByURL"));
	m_fnTMW_SetTransparentByURL = (FN_TMW_SetTransparentByURL)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetTransparentByURL"));
	m_fnTMW_SetUsernameByURL = (FN_TMW_SetUsernameByURL)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetUsernameByURL"));
	m_fnTMW_SetCopyrightByURL = (FN_TMW_SetCopyrightByURL)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_SetCopyrightByURL"));
	m_fnTMW_StartWatermarkByURL = (FN_TMW_StartWatermarkByURL)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_StartWatermarkByURL"));
	m_fnTMW_EndWatermarkByURL = (FN_TMW_EndWatermarkByURL)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_EndWatermarkByURL"));

	m_fnTMW_Final = (FN_TMW_Final)::GetProcAddress(m_hTMWatermarkDLL, _T("TMW_Final"));

	if(m_fnTMW_Init == NULL
		|| m_fnTMW_SetConfigByPid == NULL || m_fnTMW_SetWatermarkImageByPid == NULL || m_fnTMW_SetTransparentByPid == NULL
		|| m_fnTMW_SetUsernameByPid == NULL || m_fnTMW_SetCopyrightByPid == NULL || m_fnTMW_StartWatermarkByPid == NULL || m_fnTMW_EndWatermarkByPid == NULL
		|| m_fnTMW_SetConfigByHWnd == NULL || m_fnTMW_SetWatermarkImageByHWnd == NULL || m_fnTMW_SetTransparentByHWnd == NULL
		|| m_fnTMW_SetUsernameByHWnd == NULL || m_fnTMW_SetCopyrightByHWnd == NULL || m_fnTMW_StartWatermarkByHWnd == NULL || m_fnTMW_EndWatermarkByHWnd == NULL
		|| m_fnTMW_SetConfigByURL == NULL || m_fnTMW_SetWatermarkImageByURL == NULL || m_fnTMW_SetTransparentByURL == NULL
		|| m_fnTMW_SetUsernameByURL == NULL || m_fnTMW_SetCopyrightByURL == NULL || m_fnTMW_StartWatermarkByURL == NULL || m_fnTMW_EndWatermarkByURL == NULL
		|| m_fnTMW_Final == NULL)
		return ERR_SETUPLIB_FUNC_FAIL;

	dwResult = m_fnTMW_Init();
	return dwResult;
}

// INI설정파일 설정함수(pid)
DWORD CTMWatermarkManage::TMW_SetConfigByPid(DWORD dwPid, LPCTSTR szIniFilename)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetConfigByPid(dwPid, szIniFilename);
	return dwResult;
}

// INI설정파일 설정함수(hWnd)
DWORD CTMWatermarkManage::TMW_SetConfigByHWnd(HWND hWnd, LPCTSTR szIniFilename)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetConfigByHWnd(hWnd, szIniFilename);
	return dwResult;
}

// INI설정파일 설정함수(URL)
DWORD CTMWatermarkManage::TMW_SetConfigByURL(LPCTSTR szURL, LPCTSTR szIniFilename)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetConfigByURL(szURL, szIniFilename);
	return dwResult;
}

// 워터마크 이미지파일 설정함수(pid)
DWORD CTMWatermarkManage::TMW_SetWatermarkImageByPid(DWORD dwPid, LPCTSTR szWatermarkImageFilename)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetWatermarkImageByPid(dwPid, szWatermarkImageFilename);
	return dwResult;
}

// 워터마크 이미지파일 설정함수(hWnd)
DWORD CTMWatermarkManage::TMW_SetWatermarkImageByHWnd(HWND hWnd, LPCTSTR szWatermarkImageFilename)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetWatermarkImageByHWnd(hWnd, szWatermarkImageFilename);
	return dwResult;
}

// 워터마크 이미지파일 설정함수(URL)
DWORD CTMWatermarkManage::TMW_SetWatermarkImageByURL(LPCTSTR szURL, LPCTSTR szWatermarkImageFilename)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetWatermarkImageByURL(szURL, szWatermarkImageFilename);
	return dwResult;
}

// 유저네임 설정함수(pid)
DWORD CTMWatermarkManage::TMW_SetUsernameByPid(DWORD dwPid, LPCTSTR szUsername)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetUsernameByPid(dwPid, szUsername);
	return dwResult;
}

// 유저네임 설정함수(hWnd)
DWORD CTMWatermarkManage::TMW_SetUsernameByHWnd(HWND hWnd, LPCTSTR szUsername)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetUsernameByHWnd(hWnd, szUsername);
	return dwResult;
}

// 유저네임 설정함수(URL)
DWORD CTMWatermarkManage::TMW_SetUsernameByURL(LPCTSTR szURL, LPCTSTR szUsername)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetUsernameByURL(szURL, szUsername);
	return dwResult;
}

// 보안문구 설정함수(pid)
DWORD CTMWatermarkManage::TMW_SetCopyrightByPid(DWORD dwPid, LPCTSTR szCopyright)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetCopyrightByPid(dwPid, szCopyright);
	return dwResult;
}

// 보안문구 설정함수(hWnd)
DWORD CTMWatermarkManage::TMW_SetCopyrightByHWnd(HWND hWnd, LPCTSTR szCopyright)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetCopyrightByHWnd(hWnd, szCopyright);
	return dwResult;
}

// 보안문구 설정함수(URL)
DWORD CTMWatermarkManage::TMW_SetCopyrightByURL(LPCTSTR szURL, LPCTSTR szCopyright)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetCopyrightByURL(szURL, szCopyright);
	return dwResult;
}

// 워터마크 보안 시작함수(pid)
DWORD CTMWatermarkManage::TMW_StartWatermarkByPid(DWORD dwPid)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_StartWatermarkByPid(dwPid);
	return dwResult;
}

// 워터마크 보안 시작함수(hWnd)
DWORD CTMWatermarkManage::TMW_StartWatermarkByHWnd(HWND hWnd)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_StartWatermarkByHWnd(hWnd);
	return dwResult;
}

// 워터마크 보안 시작함수(URL)
DWORD CTMWatermarkManage::TMW_StartWatermarkByURL(LPCTSTR szURL)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_StartWatermarkByURL(szURL);
	return dwResult;
}

// 워터마크모듈 종료함수
DWORD CTMWatermarkManage::TMW_Final(void)
{
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_SUCCESS;		//종료의 경우에는 로딩되지 않았으면 성공으로 리턴한다.
	DWORD dwResult = m_fnTMW_Final();

	m_fnTMW_Init = NULL;
	m_fnTMW_SetConfigByPid = NULL;
	m_fnTMW_SetConfigByHWnd = NULL;
	m_fnTMW_SetWatermarkImageByPid = NULL;
	m_fnTMW_SetWatermarkImageByHWnd = NULL;
	m_fnTMW_StartWatermarkByPid = NULL;
	m_fnTMW_StartWatermarkByHWnd = NULL;
	m_fnTMW_Final = NULL;
	m_fnTMW_SetTransparentByPid = NULL;
	m_fnTMW_SetTransparentByHWnd = NULL;
	m_fnTMW_EndWatermarkByPid = NULL;
	m_fnTMW_EndWatermarkByHWnd = NULL;

	FreeLibrary(m_hTMWatermarkDLL);
	m_hTMWatermarkDLL = NULL;
	return dwResult;
}

// 워터마크 타겟 윈도우 투명도 조절함수(pid)
DWORD CTMWatermarkManage::TMW_SetTransparentByPid(DWORD dwPid, BYTE byAlpha)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetTransparentByPid(dwPid, byAlpha);
	return dwResult;
}

// 워터마크 타겟 윈도우 투명도 조절함수(hWnd)
DWORD CTMWatermarkManage::TMW_SetTransparentByHWnd(HWND hWnd, BYTE byAlpha)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetTransparentByHWnd(hWnd, byAlpha);
	return dwResult;
}

// 워터마크 타겟 윈도우 투명도 조절함수(URL)
DWORD CTMWatermarkManage::TMW_SetTransparentByURL(LPCTSTR szURL, BYTE byAlpha)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_SetTransparentByURL(szURL, byAlpha);
	return dwResult;
}

// 워터마크 보안 종료함수(pid)
DWORD CTMWatermarkManage::TMW_EndWatermarkByPid(DWORD dwPid)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_EndWatermarkByPid(dwPid);
	return dwResult;
}

// 워터마크 보안 종료함수(hWnd)
DWORD CTMWatermarkManage::TMW_EndWatermarkByHWnd(HWND hWnd)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_EndWatermarkByHWnd(hWnd);
	return dwResult;
}

// 워터마크 보안 종료함수(URL)
DWORD CTMWatermarkManage::TMW_EndWatermarkByURL(LPCTSTR szURL)
{
	DWORD dwResult;
	if(m_hTMWatermarkDLL == NULL)
		return TMW_ERROR_NOT_INIT;
	dwResult = m_fnTMW_EndWatermarkByURL(szURL);
	return dwResult;
}
