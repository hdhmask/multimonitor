
// MultiMornitorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MultiMornitor.h"
#include "MultiMornitorDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMultiMornitorDlg 대화 상자




CMultiMornitorDlg::CMultiMornitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiMornitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiMornitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMultiMornitorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CMultiMornitorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMultiMornitorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMultiMornitorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMultiMornitorDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMultiMornitorDlg 메시지 처리기

BOOL CMultiMornitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMultiMornitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMultiMornitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMultiMornitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
RECT m_rcFull;

BOOL CMultiMornitorDlg::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
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

void CMultiMornitorDlg::OnBnClickedButton1()
{
	m_vRect.clear();
	m_rcFull.top = 0;
	m_rcFull.bottom = 0;
	m_rcFull.left = 0;
	m_rcFull.right = 0;
	//memset(m_rcFull, 0, sizeof(m_rcFull));
	::EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&m_vRect);
	
	CString strResultSum;
	CString strTemp;
	for(UINT i = 0; i < m_vRect.size(); i++)
	{
		strTemp.Format(_T("%d번째 워터마크 rect(%d, %d, %d, %d)"), i, m_vRect[i].top, m_vRect[i].bottom, m_vRect[i].left, m_vRect[i].right);
		//GetDlgItem(IDC_EDIT_RESULT)-> ->SetWindowText(strTemp);
		strResultSum += strTemp;
	}
	GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(strResultSum);

	strTemp.Format(_T("디스플레이 갯수: %d \n"), m_vRect.size());
	GetDlgItem(IDC_EDIT_RESULT2)->SetWindowText(strTemp);

	strTemp.Format(_T("풀사이즈 워터마크 rect(%d, %d, %d, %d)"), m_rcFull.top, m_rcFull.bottom, m_rcFull.left, m_rcFull.right);
 	GetDlgItem(IDC_EDIT_RESULT3)->SetWindowText(strTemp);

}

void CMultiMornitorDlg::OnBnClickedButton2()
{
	m_TWatermark.EndWatermark();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMultiMornitorDlg::OnBnClickedButton3()
{
	m_TWatermark.StartWatermark("TMWatermark.ini");
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMultiMornitorDlg::OnBnClickedButton4()
{
	m_TWatermark.StartWatermark("TMWatermark.ini", TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
