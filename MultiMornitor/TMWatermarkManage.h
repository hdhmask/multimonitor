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
	// ���͸�ũ��� �ʱ�ȭ�Լ�
	DWORD TMW_Init(void);

	// INI�������� �����Լ�(pid)
	DWORD TMW_SetConfigByPid(DWORD dwPid, LPCTSTR szIniFilename);
	// ���͸�ũ �̹������� �����Լ�(pid)
	DWORD TMW_SetWatermarkImageByPid(DWORD dwPid, LPCTSTR szWatermarkImageFilename);
	// ���͸�ũ Ÿ�� ������ ���� �����Լ�(pid)
	DWORD TMW_SetTransparentByPid(DWORD dwPid, BYTE byAlpha);
	// �������� �����Լ�(pid)
	DWORD TMW_SetUsernameByPid(DWORD dwPid, LPCTSTR szUsername);
	// ���ȹ��� �����Լ�(pid)
	DWORD TMW_SetCopyrightByPid(DWORD dwPid, LPCTSTR szCopyright);
	// ���͸�ũ ���� �����Լ�(pid)
	DWORD TMW_StartWatermarkByPid(DWORD dwPid);
	// ���͸�ũ ���� �����Լ�(pid)
	DWORD TMW_EndWatermarkByPid(DWORD dwPid);

	// INI�������� �����Լ�(hWnd)
	DWORD TMW_SetConfigByHWnd(HWND hWnd, LPCTSTR szIniFilename);
	// ���͸�ũ �̹������� �����Լ�(hWnd)
	DWORD TMW_SetWatermarkImageByHWnd(HWND hWnd, LPCTSTR szWatermarkImageFilename);
	// ���͸�ũ Ÿ�� ������ ���� �����Լ�(hWnd)
	DWORD TMW_SetTransparentByHWnd(HWND hWnd, BYTE byAlpha);
	// �������� �����Լ�(hWnd)
	DWORD TMW_SetUsernameByHWnd(HWND hWnd, LPCTSTR szUsername);
	// ���ȹ��� �����Լ�(hWnd)
	DWORD TMW_SetCopyrightByHWnd(HWND hWnd, LPCTSTR szCopyright);
	// ���͸�ũ ���� �����Լ�(hWnd)
	DWORD TMW_StartWatermarkByHWnd(HWND hWnd);
	// ���͸�ũ ���� �����Լ�(hWnd)
	DWORD TMW_EndWatermarkByHWnd(HWND hWnd);

	// INI�������� �����Լ�(URL)
	DWORD TMW_SetConfigByURL(LPCTSTR szURL, LPCTSTR szIniFilename);
	// ���͸�ũ �̹������� �����Լ�(szURL)
	DWORD TMW_SetWatermarkImageByURL(LPCTSTR szURL, LPCTSTR szWatermarkImageFilename);
	// ���͸�ũ Ÿ�� ������ ���� �����Լ�(szURL)
	DWORD TMW_SetTransparentByURL(LPCTSTR szURL, BYTE byAlpha);
	// �������� �����Լ�(URL)
	DWORD TMW_SetUsernameByURL(LPCTSTR szURL, LPCTSTR szUsername);
	// ���ȹ��� �����Լ�(URL)
	DWORD TMW_SetCopyrightByURL(LPCTSTR szURL, LPCTSTR szCopyright);
	// ���͸�ũ ���� �����Լ�(szURL)
	DWORD TMW_StartWatermarkByURL(LPCTSTR szURL);
	// ���͸�ũ ���� �����Լ�(szURL)
	DWORD TMW_EndWatermarkByURL(LPCTSTR szURL);

	// ���͸�ũ��� �����Լ�
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

	// ���͸�ũ��� �ʱ�ȭ�Լ�
	FN_TMW_Init m_fnTMW_Init;

	// INI�������� �����Լ�(pid)
	FN_TMW_SetConfigByPid m_fnTMW_SetConfigByPid;
	// ���͸�ũ �̹������� �����Լ�(pid)
	FN_TMW_SetWatermarkImageByPid m_fnTMW_SetWatermarkImageByPid;
	// ���͸�ũ Ÿ�� ������ ���� �����Լ�(pid)
	FN_TMW_SetTransparentByPid m_fnTMW_SetTransparentByPid;
	// �������� �����Լ�(pid)
	FN_TMW_SetUsernameByPid m_fnTMW_SetUsernameByPid;
	// ���ȹ��� �����Լ�(pid)
	FN_TMW_SetCopyrightByPid m_fnTMW_SetCopyrightByPid;
	// ���͸�ũ ���� �����Լ�(pid)
	FN_TMW_StartWatermarkByPid m_fnTMW_StartWatermarkByPid;
	// ���͸�ũ ���� �����Լ�(pid)
	FN_TMW_EndWatermarkByPid m_fnTMW_EndWatermarkByPid;

	// INI�������� �����Լ�(hWnd)
	FN_TMW_SetConfigByHWnd m_fnTMW_SetConfigByHWnd;
	// ���͸�ũ �̹������� �����Լ�(hWnd)
	FN_TMW_SetWatermarkImageByHWnd m_fnTMW_SetWatermarkImageByHWnd;
	// ���͸�ũ Ÿ�� ������ ���� �����Լ�(hWnd)
	FN_TMW_SetTransparentByHWnd m_fnTMW_SetTransparentByHWnd;
	// �������� �����Լ�(hWnd)
	FN_TMW_SetUsernameByHWnd m_fnTMW_SetUsernameByHWnd;
	// ���ȹ��� �����Լ�(hWnd)
	FN_TMW_SetCopyrightByHWnd m_fnTMW_SetCopyrightByHWnd;
	// ���͸�ũ ���� �����Լ�(hWnd)
	FN_TMW_StartWatermarkByHWnd m_fnTMW_StartWatermarkByHWnd;
	// ���͸�ũ ���� �����Լ�(hWnd)
	FN_TMW_EndWatermarkByHWnd m_fnTMW_EndWatermarkByHWnd;

	// INI�������� �����Լ�(URL)
	FN_TMW_SetConfigByURL m_fnTMW_SetConfigByURL;
	// ���͸�ũ �̹������� �����Լ�(URL)
	FN_TMW_SetWatermarkImageByURL m_fnTMW_SetWatermarkImageByURL;
	// ���͸�ũ Ÿ�� ������ ���� �����Լ�(URL)
	FN_TMW_SetTransparentByURL m_fnTMW_SetTransparentByURL;
	// �������� �����Լ�(URL)
	FN_TMW_SetUsernameByURL m_fnTMW_SetUsernameByURL;
	// ���ȹ��� �����Լ�(URL)
	FN_TMW_SetCopyrightByURL m_fnTMW_SetCopyrightByURL;
	// ���͸�ũ ���� �����Լ�(URL)
	FN_TMW_StartWatermarkByURL m_fnTMW_StartWatermarkByURL;
	// ���͸�ũ ���� �����Լ�(URL)
	FN_TMW_EndWatermarkByURL m_fnTMW_EndWatermarkByURL;

	// ���͸�ũ��� �����Լ�
	FN_TMW_Final m_fnTMW_Final;

	// ���͸�ũ DLL�ڵ�
	HMODULE m_hTMWatermarkDLL;

};

#endif
