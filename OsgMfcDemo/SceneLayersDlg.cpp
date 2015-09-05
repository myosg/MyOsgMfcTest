// SceneLayersDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OsgMfcDemo.h"
#include "SceneLayersDlg.h"
#include "afxdialogex.h"
#include "GroupSize.h"


// CSceneLayersDlg 对话框

IMPLEMENT_DYNAMIC(CSceneLayersDlg, CDialogEx)

CSceneLayersDlg::CSceneLayersDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSceneLayersDlg::IDD, pParent)
{

}

CSceneLayersDlg::~CSceneLayersDlg()
{
}

void CSceneLayersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSceneLayersDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSceneLayersDlg 消息处理程序


void CSceneLayersDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	GROUPSIZE(IDC_STA_GSRC,IDC_TREE_LAYERS);
}
