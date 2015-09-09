// D3WindowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OsgMfcDemo.h"
#include "D3WindowDlg.h"
#include "afxdialogex.h"


// CD3WindowDlg 对话框

IMPLEMENT_DYNAMIC(CD3WindowDlg, CDialogEx)

CD3WindowDlg::CD3WindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CD3WindowDlg::IDD, pParent)
{
	this->SetBackgroundColor(RGB(255,255,255));
}

CD3WindowDlg::~CD3WindowDlg()
{
}

void CD3WindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CD3WindowDlg, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CD3WindowDlg::InitOsg()
{
	
	list<COsgSceneFile*>::iterator it=m_osgScene->OsgSceneFileList()->begin();
	COsgSceneFile* f=(*it);

	char *chr=new char[f->OsgFile()->FilePathName().GetLength()+1];
	WideCharToMultiByte(CP_ACP,0,f->OsgFile()->FilePathName().GetBuffer(),-1,chr,f->OsgFile()->FilePathName().GetLength()+1,NULL,NULL);

	m_osg->InitOSG(chr);
	m_thread = new CRenderingThread(m_osg);
	m_thread->start();
}


// CD3WindowDlg 消息处理程序


int CD3WindowDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_osg=new cOSG(m_hWnd);
	return 0;
}
