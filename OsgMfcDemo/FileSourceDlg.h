#pragma once
#include "OsgManager.h"
#include "afxcmn.h"
#include <map>

using namespace std;

// CFileSourceDlg 对话框
extern class COsgManager;
class CFileSourceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileSourceDlg)
public:
	CFileSourceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileSourceDlg();

// 对话框数据
	enum { IDD = IDD_PANEL_SOURCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	COsgManager*m_osgManager;
	COsgFile* GetOsgFile(HTREEITEM item);
public:
	void BindingOsgManager(COsgManager* manager);
	void Refresh();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CTreeCtrl m_treeSource;
	afx_msg void OnTvnBegindragTreeSource(NMHDR *pNMHDR, LRESULT *pResult);
};
