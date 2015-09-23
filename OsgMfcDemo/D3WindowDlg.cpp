// D3WindowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OsgMfcDemo.h"
#include "D3WindowDlg.h"
#include "afxdialogex.h"
#include "Common.h"


// CD3WindowDlg 对话框

IMPLEMENT_DYNAMIC(CD3WindowDlg, CDialogEx)

CD3WindowDlg::CD3WindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CD3WindowDlg::IDD, pParent)
{
	this->SetBackgroundColor(RGB(0,0,0));
	m_osgRender=NULL;
	m_osgScene=NULL;
}

CD3WindowDlg::~CD3WindowDlg()
{
	if (m_osgRender)
	{
		delete m_osgRender;
		m_osgRender=NULL;
	}
}

void CD3WindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CD3WindowDlg, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CD3WindowDlg 消息处理程序


int CD3WindowDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	StartRender();
	return 0;
}


BOOL CD3WindowDlg::StartRender()
{
	if (m_hWnd==NULL)
	{
		return FALSE;
	}
	if (m_osgRender)
	{
		return TRUE;
	}
	m_osgRender=new COsgRender(m_hWnd);
	m_osgRender->InitOSG();
	m_osgRender->StartGrahics();
	Refresh();
	return TRUE;
}


void CD3WindowDlg::Refresh()
{
	if (m_osgRender)
	{
		list<COsgSceneFile*>* files=m_osgScene->OsgSceneFileList();
		for (list<COsgSceneFile*>::iterator it=files->begin(); it!=files->end(); it++)
		{
			m_osgRender->AddNode((*it)->OsgNode());
		}
		//m_osgRender->RefreshGrahics();
	}
}

void CD3WindowDlg::Refresh( COsgSceneFile*scenefile )
{
	if (m_osgRender)
	{
		m_osgRender->AddNode(scenefile->OsgNode());
		//m_osgRender->RefreshGrahics();
	}
}
