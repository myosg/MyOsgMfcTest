// FileSourceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OsgMfcDemo.h"
#include "FileSourceDlg.h"
#include "afxdialogex.h"
#include "GroupSize.h"


// CFileSourceDlg 对话框

IMPLEMENT_DYNAMIC(CFileSourceDlg, CDialogEx)

CFileSourceDlg::CFileSourceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileSourceDlg::IDD, pParent)
{
	m_osgManager=NULL;
}

CFileSourceDlg::~CFileSourceDlg()
{
}

void CFileSourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_SOURCE, m_treeSource);
}


BEGIN_MESSAGE_MAP(CFileSourceDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_CREATE()
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE_SOURCE, &CFileSourceDlg::OnTvnBegindragTreeSource)
END_MESSAGE_MAP()

// CFileSourceDlg 消息处理程序


void CFileSourceDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	GROUPSIZE(IDC_STA_GSRC,IDC_TREE_SOURCE);
}


void CFileSourceDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
}

int CFileSourceDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}

void CFileSourceDlg::BindingOsgManager( COsgManager* manager )
{
	m_osgManager=manager;
}

void CFileSourceDlg::Refresh()
{
	if (m_osgManager&&m_treeSource.GetSafeHwnd())
	{
		COsgFileSource* src=m_osgManager->FileSource();
		HTREEITEM hroot= m_treeSource.GetRootItem();
		if (!hroot)
		{
			CString str=_T("所有本地文件");
			hroot=m_treeSource.InsertItem(str);
		}
		list<COsgFile*> temp;
		
		if(m_treeSource.ItemHasChildren(hroot))
		{
			//获得孩子节点  
			HTREEITEM hChild=m_treeSource.GetChildItem(hroot);  
			//遍历hRoot下一层的所有孩子节点  
			while(hChild)  
			{  
				COsgFile* file=(COsgFile*)m_treeSource.GetItemData(hChild);
				HTREEITEM item=m_treeSource.GetNextItem(hChild,TVGN_NEXT);  
				if(!src->Contains(file->FilePathName()))
				{
					m_treeSource.DeleteItem(hChild);
				}
				else
				{
					temp.push_back(file);
				}
				hChild=item;
			}  
		}
		for (int i = 0; i < src->Count(); i++)
		{
			COsgFile*file =src->Get(i);
			list<COsgFile*>::iterator it=temp.begin();
			BOOL ret=FALSE;
			while (it!=temp.end())
			{
				COsgFile*t=*it;
				if (t->EqualByFilePathName(*file))
				{
					ret= TRUE;
					break;
				}
				it++;
			}
			if (ret)
			{
				continue;
			}
			HTREEITEM hChild=m_treeSource.InsertItem(file->FilePathName(),hroot); 
			m_treeSource.SetItemData(hChild,(DWORD_PTR)file);
			m_treeSource.SelectItem(hChild);
		}
		m_treeSource.Expand(hroot,TVE_EXPAND);
	}
}

COsgFile* CFileSourceDlg::GetOsgFile( HTREEITEM item )
{
	return (COsgFile*)m_treeSource.GetItemData(item);
}


void CFileSourceDlg::OnTvnBegindragTreeSource(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
// 	COleDataSource data;
// 	data.DoDragDrop();
}
