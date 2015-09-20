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
	m_osgManager=NULL;
	m_selectD3WindowDlg=NULL;
}

CD3WindowsDlg::~CD3WindowsDlg()
{
	CloseAllD3Window();
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
	RECT rect;
	rect.left=0;
	rect.top=0;
	rect.right=100;
	rect.bottom=100;
	m_tab3DWinCtrl.Create(WS_CHILDWINDOW,rect,this,IDC_TAB_3DWINS);
	m_tab3DWinCtrl.ShowWindow(SW_SHOW);
	// TODO:  在此添加您专用的创建代码
	m_d3WindowList.clear();
	return 0;
}


void CD3WindowsDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
}

CD3WindowDlg* CD3WindowsDlg::OpenOrGetD3Window( COsgScene* scene)
{
	CD3WindowDlg*p=GetD3Window(scene);
	if (p)
	{
		return p;
	}
	return OpenNewD3Window(scene);
}

void CD3WindowsDlg::CloseD3Window( COsgScene* scene )
{
	int i=-1;
	for (list<CD3WindowDlg*>::iterator it=m_d3WindowList.begin();it!=m_d3WindowList.end();it++)
	{
		CD3WindowDlg*p=*it;
		i++;
		if (p->OsgScene()==scene)
		{
			m_tab3DWinCtrl.DeleteItem(i);
			m_d3WindowList.erase(it);
			delete p;
			m_osgManager->SceneLayersDlg()->Refresh();
			return;
		}
	}
}

CD3WindowDlg* CD3WindowsDlg::OpenNewD3Window( COsgScene* scene )
{
	if (m_tab3DWinCtrl.GetSafeHwnd())
	{
		CD3WindowDlg*p=new CD3WindowDlg();
		p->OsgScene(scene);
		p->Create(IDD_3D_WINDOW,&m_tab3DWinCtrl);
		int index=m_d3WindowList.size();
		m_tab3DWinCtrl.InsertItem(index,scene->Name());
		m_d3WindowList.push_back(p);
		m_tab3DWinCtrl.SetCurSel(index);
		UpdateView();
		m_osgManager->SceneLayersDlg()->Refresh();
		return p;
	}
	return NULL;
}

CD3WindowDlg* CD3WindowsDlg::GetD3Window( COsgScene* scene)
{
	int i=-1;
	for (list<CD3WindowDlg*>::iterator it=m_d3WindowList.begin();it!=m_d3WindowList.end();it++)
	{
		CD3WindowDlg*p=*it;
		i++;
		if (p->OsgScene()==scene)
		{
			int sel=m_tab3DWinCtrl.GetCurSel();
			m_tab3DWinCtrl.SetCurSel(i);
			if (i!=sel)
			{
				m_osgManager->SceneLayersDlg()->Refresh();
			}
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
	 m_osgManager->SceneLayersDlg()->Refresh();
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
			m_selectD3WindowDlg=p;
		}
		else
		{
			p->ShowWindow(SW_HIDE);
		}
	}
}

void CD3WindowsDlg::CloseAllD3Window()
{
	list<CD3WindowDlg*>::iterator it=m_d3WindowList.begin();
	while (it!=m_d3WindowList.end())
	{
		CD3WindowDlg*p=*it;
		it = m_d3WindowList.erase(it);
		delete p;
	}
	if (m_tab3DWinCtrl.GetSafeHwnd())
	{
		m_tab3DWinCtrl.DeleteAllItems();
	}
}

void CD3WindowsDlg::BindingOsgManager( COsgManager* manager )
{
	m_osgManager=manager;
}

void CD3WindowsDlg::Refresh()
{

}




