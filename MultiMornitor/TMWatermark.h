// TMWatermark.h : TMWatermark DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifdef _TMWATERMARK_API_
#define TMWATERMARK_API extern "C" __declspec(dllexport)
#else
#define TMWATERMARK_API extern "C" __declspec(dllimport)
#endif

//���� �޽���
//���������� �Ϸ����
#define TMW_ERROR_SUCCESS								0L
//���͸�ũ ���μ��� ���� ����
#define TMW_ERROR_CANNOT_EXCUTE_WATERMARK_PROCESS		2L
//�Լ� ���ڰ��� �߸�����
#define TMW_ERROR_INVALID_VALUE							4L
//���ǵ��� ���� ���ڰ���
#define TMW_ERROR_NOT_DEFINED_PARAMETER					6L
//�ʱ�ȭ ���� �ʾ���
#define TMW_ERROR_NOT_INIT								11L
//�̹����� ���� �� ����
#define TMW_ERROR_CANNOT_LOAD_IMAGE						12L
//������ ã�� �� ����
#define TMW_ERROR_FILE_NOT_FOUND						13L
//������ ���� ����
#define TMW_ERROR_CANNOT_CREATE_THREAD					14L
//�̺�Ʈ ���� ����
#define TMW_ERROR_CANNOT_CREATE_EVENT					16L
//�ӽ����� ���� ����
#define TMW_ERROR_TEMP_FILE_CREATE_FAIL					18L
//INI������ ���� �ʾ���
#define TMW_ERROR_NOT_CONFIG							21L
//�޸𸮰� ������
#define TMW_ERROR_NOT_ENOUGH_MEMORY						101L
//IE���� URL�� ���� ����
#define TMW_ERROR_CANNOT_READ_IE_URL					201L
//����������� 2000�̻��� �ʿ���
#define TMW_ERROR_REQUIRE_WINDOWS2000					1001L
//���͸�ũ �����찡 �ʱ�ȭ���� �ʾ���
#define TMW_ERROR_NOT_INIT_WATERMARK_WINDOW				10001L

//���͸�ũ ����
//�������� ��Ʈ ũ��
#define TMW_CONFIG_USERNAME_FONT_SIZE					1000L
//�������� ��Ʈ ����
#define TMW_CONFIG_USERNAME_FONT_COLOR					1001L
//�������� �ؽ�Ʈ ����
#define TMW_CONFIG_USERNAME_ROTATEANGLE					1002L
//�������� ��ġ���
#define TMW_CONFIG_USERNAME_LOCATION_MODE				1003L
//�������� ��ġ��尡 2�� ��� ��ġ ���� ���� ũ��
#define TMW_CONFIG_USERNAME_LOCATION_WIDTH				1004L
//�������� ��ġ��尡 2�� ��� ��ġ ���� ���� ũ��
#define TMW_CONFIG_USERNAME_LOCATION_HEIGHT				1005L
//���ȹ��� ��Ʈ ũ��
#define TMW_CONFIG_COPYRIGHT_FONT_SIZE					2000L
//���ȹ��� ��Ʈ ����
#define TMW_CONFIG_COPYRIGHT_FONT_COLOR					2001L
//���ȹ��� �ؽ�Ʈ ����
#define TMW_CONFIG_COPYRIGHT_ROTATEANGLE				2002L
//���ȹ��� ��ġ���
#define TMW_CONFIG_COPYRIGHT_LOCATION_MODE				2003L
//���ȹ��� ��ġ��尡 2�� ��� ��ġ ���� ���� ũ��
#define TMW_CONFIG_COPYRIGHT_LOCATION_WIDTH				2004L
//���ȹ��� ��ġ��尡 2�� ��� ��ġ ���� ���� ũ��
#define TMW_CONFIG_COPYRIGHT_LOCATION_HEIGHT			2005L
//����� ���� ����
#define TMW_CONFIG_USE_TRANSPARENTCOLOR					3000L
//����� ����
#define TMW_CONFIG_TRANSPARENTCOLOR						3001L

// ���͸�ũ��� �ʱ�ȭ�Լ�
TMWATERMARK_API DWORD TMW_Init();

// INI�������� �����Լ�(pid)
TMWATERMARK_API DWORD TMW_SetConfigByPid(DWORD dwPid, LPCTSTR szIniFilename);
// ���͸�ũ �̹������� �����Լ�(pid)
TMWATERMARK_API DWORD TMW_SetWatermarkImageByPid(DWORD dwPid, LPCTSTR szWatermarkImageFilename);
// ���͸�ũ Ÿ�� ������ ���� �����Լ�(pid)
TMWATERMARK_API DWORD TMW_SetTransparentByPid(DWORD dwPid, BYTE byAlpha);
// ������ ���� ���� �Լ�(pid)
TMWATERMARK_API DWORD TMW_SetLongValueByPid(DWORD dwPid, DWORD dwKind, LONG nValue);
// �������� �����Լ�(pid)
TMWATERMARK_API DWORD TMW_SetUsernameByPid(DWORD dwPid, LPCTSTR szUsername);
// ���ȹ��� �����Լ�(pid)
TMWATERMARK_API DWORD TMW_SetCopyrightByPid(DWORD dwPid, LPCTSTR szCopyright);
// ���͸�ũ ���� �����Լ�(pid)
TMWATERMARK_API DWORD TMW_StartWatermarkByPid(DWORD dwPid);
// ���͸�ũ ���� �����Լ�(pid)
TMWATERMARK_API DWORD TMW_EndWatermarkByPid(DWORD dwPid);

// INI�������� �����Լ�(hWnd)
TMWATERMARK_API DWORD TMW_SetConfigByHWnd(HWND hWnd, LPCTSTR szIniFilename);
// ���͸�ũ �̹������� �����Լ�(hWnd)
TMWATERMARK_API DWORD TMW_SetWatermarkImageByHWnd(HWND hWnd, LPCTSTR szWatermarkImageFilename);
// ���͸�ũ Ÿ�� ������ ���� �����Լ�(hWnd)
TMWATERMARK_API DWORD TMW_SetTransparentByHWnd(HWND hWnd, BYTE byAlpha);
// ������ ���� ���� �Լ�(hWnd)
TMWATERMARK_API DWORD TMW_SetLongValueByHWnd(HWND hWnd, DWORD dwKind, LONG nValue);
// �������� �����Լ�(hWnd)
TMWATERMARK_API DWORD TMW_SetUsernameByHWnd(HWND hWnd, LPCTSTR szUsername);
// ���ȹ��� �����Լ�(hWnd)
TMWATERMARK_API DWORD TMW_SetCopyrightByHWnd(HWND hWnd, LPCTSTR szCopyright);
// ���͸�ũ ���� �����Լ�(hWnd)
TMWATERMARK_API DWORD TMW_StartWatermarkByHWnd(HWND hWnd);
// ���͸�ũ ���� �����Լ�(hWnd)
TMWATERMARK_API DWORD TMW_EndWatermarkByHWnd(HWND hWnd);

// INI�������� �����Լ�(URL)
TMWATERMARK_API DWORD TMW_SetConfigByURL(LPCTSTR szURL, LPCTSTR szIniFilename);
// ���͸�ũ �̹������� �����Լ�(URL)
TMWATERMARK_API DWORD TMW_SetWatermarkImageByURL(LPCTSTR szURL, LPCTSTR szWatermarkImageFilename);
// ���͸�ũ Ÿ�� ������ ���� �����Լ�(URL)
TMWATERMARK_API DWORD TMW_SetTransparentByURL(LPCTSTR szURL, BYTE byAlpha);
// ������ ���� ���� �Լ�(URL)
TMWATERMARK_API DWORD TMW_SetLongValueByURL(LPCTSTR szURL, DWORD dwKind, LONG nValue);
// �������� �����Լ�(URL)
TMWATERMARK_API DWORD TMW_SetUsernameByURL(LPCTSTR szURL, LPCTSTR szUsername);
// ���ȹ��� �����Լ�(URL)
TMWATERMARK_API DWORD TMW_SetCopyrightByURL(LPCTSTR szURL, LPCTSTR szCopyright);
// ���͸�ũ ���� �����Լ�(URL)
TMWATERMARK_API DWORD TMW_StartWatermarkByURL(LPCTSTR szURL);
// ���͸�ũ ���� �����Լ�(URL)
TMWATERMARK_API DWORD TMW_EndWatermarkByURL(LPCTSTR szURL);

// ���͸�ũ��� �����Լ�
TMWATERMARK_API DWORD TMW_Final();
