// TMWatermark.h : TMWatermark DLL의 기본 헤더 파일입니다.
//

#pragma once

#ifdef _TMWATERMARK_API_
#define TMWATERMARK_API extern "C" __declspec(dllexport)
#else
#define TMWATERMARK_API extern "C" __declspec(dllimport)
#endif

//에러 메시지
//성공적으로 완료됐음
#define TMW_ERROR_SUCCESS								0L
//워터마크 프로세스 실행 실패
#define TMW_ERROR_CANNOT_EXCUTE_WATERMARK_PROCESS		2L
//함수 인자값이 잘못됐음
#define TMW_ERROR_INVALID_VALUE							4L
//정의되지 않은 인자값임
#define TMW_ERROR_NOT_DEFINED_PARAMETER					6L
//초기화 하지 않았음
#define TMW_ERROR_NOT_INIT								11L
//이미지를 읽을 수 없음
#define TMW_ERROR_CANNOT_LOAD_IMAGE						12L
//파일을 찾을 수 없음
#define TMW_ERROR_FILE_NOT_FOUND						13L
//쓰레드 생성 실패
#define TMW_ERROR_CANNOT_CREATE_THREAD					14L
//이벤트 생성 실패
#define TMW_ERROR_CANNOT_CREATE_EVENT					16L
//임시파일 생성 실패
#define TMW_ERROR_TEMP_FILE_CREATE_FAIL					18L
//INI설정을 하지 않았음
#define TMW_ERROR_NOT_CONFIG							21L
//메모리가 부족함
#define TMW_ERROR_NOT_ENOUGH_MEMORY						101L
//IE에서 URL을 읽지 못함
#define TMW_ERROR_CANNOT_READ_IE_URL					201L
//윈도우버전이 2000이상이 필요함
#define TMW_ERROR_REQUIRE_WINDOWS2000					1001L
//워터마크 윈도우가 초기화되지 않았음
#define TMW_ERROR_NOT_INIT_WATERMARK_WINDOW				10001L

//워터마크 설정
//유저정보 폰트 크기
#define TMW_CONFIG_USERNAME_FONT_SIZE					1000L
//유저정보 폰트 색상
#define TMW_CONFIG_USERNAME_FONT_COLOR					1001L
//유저정보 텍스트 기울기
#define TMW_CONFIG_USERNAME_ROTATEANGLE					1002L
//유저정보 위치모드
#define TMW_CONFIG_USERNAME_LOCATION_MODE				1003L
//유저정보 위치모드가 2일 경우 배치 간격 가로 크기
#define TMW_CONFIG_USERNAME_LOCATION_WIDTH				1004L
//유저정보 위치모드가 2일 경우 배치 간격 세로 크기
#define TMW_CONFIG_USERNAME_LOCATION_HEIGHT				1005L
//보안문구 폰트 크기
#define TMW_CONFIG_COPYRIGHT_FONT_SIZE					2000L
//보안문구 폰트 색상
#define TMW_CONFIG_COPYRIGHT_FONT_COLOR					2001L
//보안문구 텍스트 기울기
#define TMW_CONFIG_COPYRIGHT_ROTATEANGLE				2002L
//보안문구 위치모드
#define TMW_CONFIG_COPYRIGHT_LOCATION_MODE				2003L
//보안문구 위치모드가 2일 경우 배치 간격 가로 크기
#define TMW_CONFIG_COPYRIGHT_LOCATION_WIDTH				2004L
//보안문구 위치모드가 2일 경우 배치 간격 세로 크기
#define TMW_CONFIG_COPYRIGHT_LOCATION_HEIGHT			2005L
//투명색 지정 여부
#define TMW_CONFIG_USE_TRANSPARENTCOLOR					3000L
//투명색 지정
#define TMW_CONFIG_TRANSPARENTCOLOR						3001L

// 워터마크모듈 초기화함수
TMWATERMARK_API DWORD TMW_Init();

// INI설정파일 설정함수(pid)
TMWATERMARK_API DWORD TMW_SetConfigByPid(DWORD dwPid, LPCTSTR szIniFilename);
// 워터마크 이미지파일 설정함수(pid)
TMWATERMARK_API DWORD TMW_SetWatermarkImageByPid(DWORD dwPid, LPCTSTR szWatermarkImageFilename);
// 워터마크 타겟 윈도우 투명도 조절함수(pid)
TMWATERMARK_API DWORD TMW_SetTransparentByPid(DWORD dwPid, BYTE byAlpha);
// 정수값 설정 변경 함수(pid)
TMWATERMARK_API DWORD TMW_SetLongValueByPid(DWORD dwPid, DWORD dwKind, LONG nValue);
// 유저네임 설정함수(pid)
TMWATERMARK_API DWORD TMW_SetUsernameByPid(DWORD dwPid, LPCTSTR szUsername);
// 보안문구 설정함수(pid)
TMWATERMARK_API DWORD TMW_SetCopyrightByPid(DWORD dwPid, LPCTSTR szCopyright);
// 워터마크 보안 시작함수(pid)
TMWATERMARK_API DWORD TMW_StartWatermarkByPid(DWORD dwPid);
// 워터마크 보안 종료함수(pid)
TMWATERMARK_API DWORD TMW_EndWatermarkByPid(DWORD dwPid);

// INI설정파일 설정함수(hWnd)
TMWATERMARK_API DWORD TMW_SetConfigByHWnd(HWND hWnd, LPCTSTR szIniFilename);
// 워터마크 이미지파일 설정함수(hWnd)
TMWATERMARK_API DWORD TMW_SetWatermarkImageByHWnd(HWND hWnd, LPCTSTR szWatermarkImageFilename);
// 워터마크 타겟 윈도우 투명도 조절함수(hWnd)
TMWATERMARK_API DWORD TMW_SetTransparentByHWnd(HWND hWnd, BYTE byAlpha);
// 정수값 설정 변경 함수(hWnd)
TMWATERMARK_API DWORD TMW_SetLongValueByHWnd(HWND hWnd, DWORD dwKind, LONG nValue);
// 유저네임 설정함수(hWnd)
TMWATERMARK_API DWORD TMW_SetUsernameByHWnd(HWND hWnd, LPCTSTR szUsername);
// 보안문구 설정함수(hWnd)
TMWATERMARK_API DWORD TMW_SetCopyrightByHWnd(HWND hWnd, LPCTSTR szCopyright);
// 워터마크 보안 시작함수(hWnd)
TMWATERMARK_API DWORD TMW_StartWatermarkByHWnd(HWND hWnd);
// 워터마크 보안 종료함수(hWnd)
TMWATERMARK_API DWORD TMW_EndWatermarkByHWnd(HWND hWnd);

// INI설정파일 설정함수(URL)
TMWATERMARK_API DWORD TMW_SetConfigByURL(LPCTSTR szURL, LPCTSTR szIniFilename);
// 워터마크 이미지파일 설정함수(URL)
TMWATERMARK_API DWORD TMW_SetWatermarkImageByURL(LPCTSTR szURL, LPCTSTR szWatermarkImageFilename);
// 워터마크 타겟 윈도우 투명도 조절함수(URL)
TMWATERMARK_API DWORD TMW_SetTransparentByURL(LPCTSTR szURL, BYTE byAlpha);
// 정수값 설정 변경 함수(URL)
TMWATERMARK_API DWORD TMW_SetLongValueByURL(LPCTSTR szURL, DWORD dwKind, LONG nValue);
// 유저네임 설정함수(URL)
TMWATERMARK_API DWORD TMW_SetUsernameByURL(LPCTSTR szURL, LPCTSTR szUsername);
// 보안문구 설정함수(URL)
TMWATERMARK_API DWORD TMW_SetCopyrightByURL(LPCTSTR szURL, LPCTSTR szCopyright);
// 워터마크 보안 시작함수(URL)
TMWATERMARK_API DWORD TMW_StartWatermarkByURL(LPCTSTR szURL);
// 워터마크 보안 종료함수(URL)
TMWATERMARK_API DWORD TMW_EndWatermarkByURL(LPCTSTR szURL);

// 워터마크모듈 종료함수
TMWATERMARK_API DWORD TMW_Final();
