
// MultiMornitor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMultiMornitorApp:
// �� Ŭ������ ������ ���ؼ��� MultiMornitor.cpp�� �����Ͻʽÿ�.
//

class CMultiMornitorApp : public CWinAppEx
{
public:
	CMultiMornitorApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMultiMornitorApp theApp;