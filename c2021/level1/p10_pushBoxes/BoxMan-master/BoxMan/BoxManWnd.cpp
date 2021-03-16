// BoxManWnd.cpp : ʵ���ļ�
//
//#pragma comment(lib,"Winmm.lib") 
#include "stdafx.h"
#include "BoxMan.h"
#include "BoxManMain.h"
#include "BoxManWnd.h"
#include "Help.h"
#include "LoadMap.h"
//#include "Mmsystem.h"


// CBoxManWnd

IMPLEMENT_DYNAMIC(CBoxManWnd, CWnd)

CBoxManWnd::CBoxManWnd()
: m_pSubMenu(NULL)
{


}

CBoxManWnd::~CBoxManWnd()
{
}


BEGIN_MESSAGE_MAP(CBoxManWnd, CWnd)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_INITMENU()
	ON_COMMAND(ID_MENU_GAME_LEVEL, &CBoxManWnd::OnMenuGameLevel)
	ON_COMMAND(ID_MENU_GAME_MUSIC, &CBoxManWnd::OnMenuGameMusic)
	ON_COMMAND(ID_MENU_GAME_HELP, &CBoxManWnd::OnMenuGameHelp)
	ON_COMMAND(ID_APP_EXIT, &CBoxManWnd::OnAppExit)
END_MESSAGE_MAP()



// CBoxManWnd ��Ϣ�������



void CBoxManWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	theBoxMan.DispatchMsg(nChar);
	//CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
	//theBoxMan.WinOrNot();


}

void CBoxManWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	CRect m_rcClient;
	GetClientRect(&m_rcClient);
	CDC dcMemory;
	CBitmap bitmap;

	if (!dc.IsPrinting())
	{
		if (dcMemory.CreateCompatibleDC(&dc))
		{
			if (bitmap.CreateCompatibleBitmap(&dc,m_rcClient.right,m_rcClient.bottom))
			{
				dcMemory.SelectObject(&bitmap);
				theBoxMan.DrawGameArea(&dcMemory);
				dc.BitBlt(m_rcClient.left,m_rcClient.top,m_rcClient.right,m_rcClient.bottom,&dcMemory,0,0,SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}




}

void CBoxManWnd::OnInitMenu(CMenu* pMenu)
{
	CWnd::OnInitMenu(pMenu);

	if((m_pSubMenu=pMenu->GetSubMenu(0))==0)
	{
		AfxMessageBox("��ʼ���˵�ʧ��!");
		PostQuitMessage(0);
	}
	if(m_bSound)
		m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC,MF_CHECKED|MF_BYCOMMAND);
	// TODO: �ڴ˴������Ϣ����������
}

void CBoxManWnd::OnMenuGameLevel()
{
	// TODO: �ڴ���������������
	CLoadMap dlg;
	dlg.strMaxNum.Format("��ǰ������:%d",MAX_MISSION_NUM );
	if (dlg.DoModal()==IDOK)
	{
		m_iMissionNum=dlg.m_LoadMapNum;
		theBoxMan.LoadMap(m_iMissionNum);
		Invalidate(true);
	}
}

void CBoxManWnd::OnMenuGameMusic()
{
	// TODO: �ڴ���������������
	

	if (m_pSubMenu)
	{
		if (m_bSound==true)
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC,MF_UNCHECKED|MF_BYCOMMAND);
		else
			m_pSubMenu->CheckMenuItem(ID_MENU_GAME_MUSIC,MF_CHECKED|MF_BYCOMMAND);

	}
	m_bSound=!m_bSound;
}

void CBoxManWnd::OnMenuGameHelp()
{
	// TODO: �ڴ���������������
	CHelp dlg;
	//CRect a;
	//GetClientRect(&a);
	//dlg.m_HelpCtrl.MoveWindow(&a,1);
	dlg.DoModal();
}

void CBoxManWnd::OnAppExit()
{
	// TODO: �ڴ���������������
	PostQuitMessage(0);
}

