#if !defined(CTMWATERMARKMANAGE_H)
#define CTMWATERMARKMANAGE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ERR_SETUPLIB_LOADING_FAIL			520
#define ERR_SETUPLIB_FUNC_FAIL				521

class CTMWatermarkManage
{
public:
	CTMWatermarkManage(void);
	~CTMWatermarkManage(void);

public:
	// 워터마크모듈 초기화함수
	DWORD TMW_Init(void);

	// INI설정파일 설정함수(pid)
	DWORD TMW_SetConfigByPid(DWORD dwPid, LPCTSTR szIniFilename);
	// 워터마크 이미지파일 설정함수(pid)
	DWORD TMW_SetWatermarkImageByPid(DWORD dwPid, LPCTSTR szWatermarkImageFilename);
	// 워터마크 타겟 윈도우 투명도 조절함수(pid)
	DWORD TMW_SetTransparentByPid(DWORD dwPid, BYTE byAlpha);
	// 유저네임 설정함수(pid)
	DWORD TMW_SetUsernameByPid(DWORD dwPid, LPCTSTR szUsername);
	// 보안문구 설정함수(pid)
	DWORD TMW_SetCopyrightByPid(DWORD dwPid, LPCTSTR szCopyright);
	// 워터마크 보안 시작함수(pid)
	DWORD TMW_StartWatermarkByPid(DWORD dwPid);
	// 워터마크 보안 종료함수(pid)
	DWORD TMW_EndWatermarkByPid(DWORD dwPid);

	// INI설정파일 설정함수(hWnd)
	DWORD TMW_SetConfigByHWnd(HWND hWnd, LPCTSTR szIniFilename);
	// 워터마크 이미지파일 설정함수(hWnd)
	DWORD TMW_SetWatermarkImageByHWnd(HWND hWnd, LPCTSTR szWatermarkImageFilename);
	// 워터마크 타겟 윈도우 투명도 조절함수(hWnd)
	DWORD TMW_SetTransparentByHWnd(HWND hWnd, BYTE byAlpha);
	// 유저네임 설정함수(hWnd)
	DWORD TMW_SetUsernameByHWnd(HWND hWnd, LPCTSTR szUsername);
	// 보안문구 설정함수(hWnd)
	DWORD TMW_SetCopyrightByHWnd(HWND hWnd, LPCTSTR szCopyright);
	// 워터마크 보안 시작함수(hWnd)
	DWORD TMW_StartWatermarkByHWnd(HWND hWnd);
	// 워터마크 보안 종료함수(hWnd)
	DWORD TMW_EndWatermarkByHWnd(HWND hWnd);

	// INI설정파일 설정함수(URL)
	DWORD TMW_SetConfigByURL(LPCTSTR szURL, LPCTSTR szIniFilename);
	// 워터마크 이미지파일 설정함수(szURL)
	DWORD TMW_SetWatermarkImageByURL(LPCTSTR szURL, LPCTSTR szWatermarkImageFilename);
	// 워터마크 타겟 윈도우 투명도 조절함수(szURL)
	DWORD TMW_SetTransparentByURL(LPCTSTR szURL, BYTE byAlpha);
	// 유저네임 설정함수(URL)
	DWORD TMW_SetUsernameByURL(LPCTSTR szURL, LPCTSTR szUsername);
	// 보안문구 설정함수(URL)
	DWORD TMW_SetCopyrightByURL(LPCTSTR szURL, LPCTSTR szCopyright);
	// 워터마크 보안 시작함수(szURL)
	DWORD TMW_StartWatermarkByURL(LPCTSTR szURL);
	// 워터마크 보안 종료함수(szURL)
	DWORD TMW_EndWatermarkByURL(LPCTSTR szURL);

	// 워터마크모듈 종료함수
	DWORD TMW_Final(void);

protected:
	typedef DWORD (*FN_TMW_Init)(void);

	typedef DWORD (*FN_TMW_SetConfigByPid)(DWORD dwPid, LPCTSTR szIniFilename);
	typedef DWORD (*FN_TMW_SetWatermarkImageByPid)(DWORD dwPid, LPCTSTR szWatermarkImageFilename);
	typedef DWORD (*FN_TMW_SetTransparentByPid)(DWORD dwPid, BYTE byAlpha);
	typedef DWORD (*FN_TMW_SetUsernameByPid)(DWORD dwPid, LPCTSTR szUsername);
	typedef DWORD (*FN_TMW_SetCopyrightByPid)(DWORD dwPid, LPCTSTR szCopyright);
	typedef DWORD (*FN_TMW_StartWatermarkByPid)(DWORD dwPid);
	typedef DWORD (*FN_TMW_EndWatermarkByPid)(DWORD dwPid);

	typedef DWORD (*FN_TMW_SetConfigByHWnd)(HWND hWnd, LPCTSTR szIniFilename);
	typedef DWORD (*FN_TMW_SetWatermarkImageByHWnd)(HWND hWnd, LPCTSTR szWatermarkImageFilename);
	typedef DWORD (*FN_TMW_SetTransparentByHWnd)(HWND hWnd, BYTE byAlpha);
	typedef DWORD (*FN_TMW_SetUsernameByHWnd)(HWND hWnd, LPCTSTR szUsername);
	typedef DWORD (*FN_TMW_SetCopyrightByHWnd)(HWND hWnd, LPCTSTR szCopyright);
	typedef DWORD (*FN_TMW_StartWatermarkByHWnd)(HWND hWnd);
	typedef DWORD (*FN_TMW_EndWatermarkByHWnd)(HWND hWnd);

	typedef DWORD (*FN_TMW_SetConfigByURL)(LPCTSTR szURL, LPCTSTR szIniFilename);
	typedef DWORD (*FN_TMW_SetWatermarkImageByURL)(LPCTSTR szURL, LPCTSTR szWatermarkImageFilename);
	typedef DWORD (*FN_TMW_SetTransparentByURL)(LPCTSTR szURL, BYTE byAlpha);
	typedef DWORD (*FN_TMW_SetUsernameByURL)(LPCTSTR szURL, LPCTSTR szUsername);
	typedef DWORD (*FN_TMW_SetCopyrightByURL)(LPCTSTR szURL, LPCTSTR szCopyright);
	typedef DWORD (*FN_TMW_StartWatermarkByURL)(LPCTSTR szURL);
	typedef DWORD (*FN_TMW_EndWatermarkByURL)(LPCTSTR szURL);

	typedef DWORD (*FN_TMW_Final)(void);

	// 워터마크모듈 초기화함수
	FN_TMW_Init m_fnTMW_Init;

	// INI설정파일 설정함수(pid)
	FN_TMW_SetConfigByPid m_fnTMW_SetConfigByPid;
	// 워터마크 이미지파일 설정함수(pid)
	FN_TMW_SetWatermarkImageByPid m_fnTMW_SetWatermarkImageByPid;
	// 워터마크 타겟 윈도우 투명도 조절함수(pid)
	FN_TMW_SetTransparentByPid m_fnTMW_SetTransparentByPid;
	// 유저네임 설정함수(pid)
	FN_TMW_SetUsernameByPid m_fnTMW_SetUsernameByPid;
	// 보안문구 설정함수(pid)
	FN_TMW_SetCopyrightByPid m_fnTMW_SetCopyrightByPid;
	// 워터마크 보안 시작함수(pid)
	FN_TMW_StartWatermarkByPid m_fnTMW_StartWatermarkByPid;
	// 워터마크 보안 종료함수(pid)
	FN_TMW_EndWatermarkByPid m_fnTMW_EndWatermarkByPid;

	// INI설정파일 설정함수(hWnd)
	FN_TMW_SetConfigByHWnd m_fnTMW_SetConfigByHWnd;
	// 워터마크 이미지파일 설정함수(hWnd)
	FN_TMW_SetWatermarkImageByHWnd m_fnTMW_SetWatermarkImageByHWnd;
	// 워터마크 타겟 윈도우 투명도 조절함수(hWnd)
	FN_TMW_SetTransparentByHWnd m_fnTMW_SetTransparentByHWnd;
	// 유저네임 설정함수(hWnd)
	FN_TMW_SetUsernameByHWnd m_fnTMW_SetUsernameByHWnd;
	// 보안문구 설정함수(hWnd)
	FN_TMW_SetCopyrightByHWnd m_fnTMW_SetCopyrightByHWnd;
	// 워터마크 보안 시작함수(hWnd)
	FN_TMW_StartWatermarkByHWnd m_fnTMW_StartWatermarkByHWnd;
	// 워터마크 보안 종료함수(hWnd)
	FN_TMW_EndWatermarkByHWnd m_fnTMW_EndWatermarkByHWnd;

	// INI설정파일 설정함수(URL)
	FN_TMW_SetConfigByURL m_fnTMW_SetConfigByURL;
	// 워터마크 이미지파일 설정함수(URL)
	FN_TMW_SetWatermarkImageByURL m_fnTMW_SetWatermarkImageByURL;
	// 워터마크 타겟 윈도우 투명도 조절함수(URL)
	FN_TMW_SetTransparentByURL m_fnTMW_SetTransparentByURL;
	// 유저네임 설정함수(URL)
	FN_TMW_SetUsernameByURL m_fnTMW_SetUsernameByURL;
	// 보안문구 설정함수(URL)
	FN_TMW_SetCopyrightByURL m_fnTMW_SetCopyrightByURL;
	// 워터마크 보안 시작함수(URL)
	FN_TMW_StartWatermarkByURL m_fnTMW_StartWatermarkByURL;
	// 워터마크 보안 종료함수(URL)
	FN_TMW_EndWatermarkByURL m_fnTMW_EndWatermarkByURL;

	// 워터마크모듈 종료함수
	FN_TMW_Final m_fnTMW_Final;

	// 워터마크 DLL핸들
	HMODULE m_hTMWatermarkDLL;

};

#endif
