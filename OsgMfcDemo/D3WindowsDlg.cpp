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
END_MESSAGE_MAP()


// CD3WindowsDlg 消息处理程序


void CD3WindowsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	FULLSIZE(IDC_TAB_3DWINS,0,0,0,5);
}


int CD3WindowsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	return 0;
}


void CD3WindowsDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	m_tab3DWinCtrl.InsertItem(0,_T("测试窗口"));
}
