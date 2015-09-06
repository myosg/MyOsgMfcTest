// D3WindowsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OsgMfcDemo.h"
#include "D3WindowsDlg.h"
#include "afxdialogex.h"
#include "GroupSize.h"


// CD3WindowsDlg 对话框

IMPLEMENT_DYNAMIC(CD3WindowsDlg, CDialogEx)

CD3WindowsDlg::CD3WindowsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CD3WindowsDlg::IDD, pParent)
{
}

CD3WindowsDlg::~CD3WindowsDlg()
{
}

void CD3WindowsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_3DWINS, m_tab3DWinCtrl);
}


BEGIN_MESSAGE_MAP(CD3WindowsDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_3DWINS, &CD3WindowsDlg::OnTcnSelchangeTab3dwins)
END_MESSAGE_MAP()


// CD3WindowsDlg 消息处理程序


void CD3WindowsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	FULLSIZE(IDC_TAB_3DWINS,0,0,0,5);
	UpdateView();
}


int CD3WindowsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_d3WindowList.clear();
	return 0;
}


void CD3WindowsDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	OpenOrGetD3Window(_T("测试窗口1"));
	OpenOrGetD3Window(_T("测试窗口2"));
}

CD3WindowDlg* CD3WindowsDlg::OpenOrGetD3Window( CString sceneName )
{
	CD3WindowDlg*p=GetD3Window(sceneName);
	if (p)
	{
		return p;
	}
	return OpenNewD3Window(sceneName);
}

void CD3WindowsDlg::CloseD3Window( CString sceneName )
{
	int i=-1;
	for (list<CD3WindowDlg*>::iterator it=m_d3WindowList.begin();it!=m_d3WindowList.end();it++)
	{
		CD3WindowDlg*p=*it;
		i++;
		if (p->D3WindowName().Compare(sceneName)==0)
		{
			m_tab3DWinCtrl.DeleteItem(i);
			m_d3WindowList.erase(it);
			delete p;
			return;
		}
	}
}

CD3WindowDlg* CD3WindowsDlg::OpenNewD3Window( CString sceneName )
{
	if (m_tab3DWinCtrl.GetSafeHwnd())
	{
		CD3WindowDlg*p=new CD3WindowDlg();
		p->D3WindowName(sceneName);
		p->Create(IDD_3D_WINDOW,&m_tab3DWinCtrl);
		int index=m_d3WindowList.size();
		m_tab3DWinCtrl.InsertItem(index,sceneName);
		m_d3WindowList.push_back(p);
		m_tab3DWinCtrl.SetCurSel(index);
		UpdateView();
		return p;
	}
	return NULL;
}

CD3WindowDlg* CD3WindowsDlg::GetD3Window( CString sceneName )
{
	int i=-1;
	for (list<CD3WindowDlg*>::iterator it=m_d3WindowList.begin();it!=m_d3WindowList.end();it++)
	{
		CD3WindowDlg*p=*it;
		i++;
		if (p->D3WindowName().Compare(sceneName)==0)
		{
			m_tab3DWinCtrl.SetCurSel(i);
			return p;
		}
	}
	return NULL;
}


void CD3WindowsDlg::OnTcnSelchangeTab3dwins(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	 UpdateView();
}

void CD3WindowsDlg::UpdateView()
{
	if (!m_tab3DWinCtrl.GetSafeHwnd())
	{
		return;
	}
	int sel=m_tab3DWinCtrl.GetCurSel(); 
	int i=-1;
	for (list<CD3WindowDlg*>::iterator it=m_d3WindowList.begin();it!=m_d3WindowList.end();it++)
	{
		CD3WindowDlg*p=*it;
		i++;
		if (i==sel)
		{
			p->ShowWindow(SW_SHOW);
			RECT rect;
			m_tab3DWinCtrl.GetClientRect(&rect);
			rect.top+=22; 
			rect.bottom-=2; 
			rect.left+=1; 
			rect.right-=3; 
			p->MoveWindow(&rect);
		}
		else
		{
			p->ShowWindow(SW_HIDE);
		}
	}
}


