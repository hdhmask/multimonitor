
// MultiMornitorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MultiMornitor.h"
#include "MultiMornitorDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMultiMornitorDlg ��ȭ ����




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


// CMultiMornitorDlg �޽��� ó����

BOOL CMultiMornitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMultiMornitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
		strTemp.Format(_T("%d��° ���͸�ũ rect(%d, %d, %d, %d)"), i, m_vRect[i].top, m_vRect[i].bottom, m_vRect[i].left, m_vRect[i].right);
		//GetDlgItem(IDC_EDIT_RESULT)-> ->SetWindowText(strTemp);
		strResultSum += strTemp;
	}
	GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(strResultSum);

	strTemp.Format(_T("���÷��� ����: %d \n"), m_vRect.size());
	GetDlgItem(IDC_EDIT_RESULT2)->SetWindowText(strTemp);

	strTemp.Format(_T("Ǯ������ ���͸�ũ rect(%d, %d, %d, %d)"), m_rcFull.top, m_rcFull.bottom, m_rcFull.left, m_rcFull.right);
 	GetDlgItem(IDC_EDIT_RESULT3)->SetWindowText(strTemp);

}

void CMultiMornitorDlg::OnBnClickedButton2()
{
	m_TWatermark.EndWatermark();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMultiMornitorDlg::OnBnClickedButton3()
{
	m_TWatermark.StartWatermark("TMWatermark.ini");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMultiMornitorDlg::OnBnClickedButton4()
{
	m_TWatermark.StartWatermark("TMWatermark.ini", TRUE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
