// BoxMan.h : BoxMan Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "BoxManWnd.h"

// CBoxManApp:
// �йش����ʵ�֣������ BoxMan.cpp
//

class CBoxManApp : public CWinApp
{
public:
	CBoxManApp();
	~CBoxManApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

};

extern CBoxManApp theApp;
extern 	int m_iMissionNum;
extern CBoxManWnd* m_pBoxManWnd;
extern bool m_bSound;
