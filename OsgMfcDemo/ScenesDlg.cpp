// ScenesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OsgMfcDemo.h"
#include "ScenesDlg.h"
#include "afxdialogex.h"
#include "GroupSize.h"


// CScenesDlg 对话框

IMPLEMENT_DYNAMIC(CScenesDlg, CDialogEx)

CScenesDlg::CScenesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScenesDlg::IDD, pParent)
{

}

CScenesDlg::~CScenesDlg()
{
}

void CScenesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScenesDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()
// CScenesDlg 消息处理程序


int CScenesDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}


void CScenesDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	GROUPSIZE(IDC_STA_GSRC,IDC_TREE_SCENE);
}


void CScenesDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
}
