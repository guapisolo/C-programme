#pragma once


// CLoadMap �Ի���

class CLoadMap : public CDialog
{
	DECLARE_DYNAMIC(CLoadMap)

public:
	CLoadMap(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoadMap();

// �Ի�������
	enum { IDD = IDD_LOAD_MAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	UINT m_LoadMapNum;
public:
	CString strMaxNum;
};
