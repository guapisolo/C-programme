// BoxMan.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "BoxMan.h"
#include "BoxManWnd.h"
#include "BoxManMain.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBoxManApp

BEGIN_MESSAGE_MAP(CBoxManApp, CWinApp)

END_MESSAGE_MAP()


// CBoxManApp ����

CBoxManApp::CBoxManApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

CBoxManApp::~CBoxManApp()
{
	delete m_pBoxManWnd;
	m_pBoxManWnd=NULL;
}
// Ψһ��һ�� CBoxManApp ����

CBoxManApp theApp;
CBoxManMain theBoxMan;
int m_iMissionNum;
int MAX_MISSION_NUM;
CBoxManWnd* m_pBoxManWnd;
bool m_bSound;



// CBoxManApp ��ʼ��

BOOL CBoxManApp::InitInstance()
{
	
	m_pBoxManWnd=new CBoxManWnd();
	WNDCLASS wc;
	ZeroMemory(&wc,sizeof(wc));
	wc.hInstance=AfxGetInstanceHandle();
	wc.lpfnWndProc=::DefWindowProc;
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor=LoadCursor(IDC_WAIT);
	wc.hIcon=LoadIcon(IDR_MAINFRAME);
	wc.lpszMenuName=MAKEINTRESOURCE(IDR_MAINFRAME);
	wc.lpszClassName="MyBoxMan";

	if (!AfxRegisterClass(&wc))
	{
		AfxMessageBox("ע�ᴰ����ʧ�ܣ�");
		return FALSE;
	}
	UINT uWidth=400+DEFAULT_FRAME_X;
	UINT uHeight=400+DEFAULT_FRAME_Y;
	UINT uXPos=GetSystemMetrics(SM_CXSCREEN)/2-uWidth/2;
	UINT uYPos=GetSystemMetrics(SM_CYSCREEN)/2-uHeight/2;
	if (!m_pBoxManWnd->CreateEx(NULL,wc.lpszClassName,"������",WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,uXPos,uYPos,uWidth,uHeight,NULL,NULL))
	{
		AfxMessageBox("����������ʧ�ܣ�");
		return false;
	}
	m_pMainWnd=m_pBoxManWnd;
	theBoxMan.MyInit();
	m_pBoxManWnd->ShowWindow(SW_NORMAL);
	return TRUE;
}
