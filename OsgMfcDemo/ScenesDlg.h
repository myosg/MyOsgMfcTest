#pragma once
#include "OsgManager.h"
#include "afxcmn.h"
// CScenesDlg 对话框
extern class COsgManager;
class CScenesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScenesDlg)
public:
	CScenesDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScenesDlg();

// 对话框数据
	enum { IDD = IDD_PANEL_SCENES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	COsgManager*m_osgManager;
public:
	void BindingOsgManager(COsgManager* manager);
	void Refresh();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnNMRClickTreeScene(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSceneNew();
	CTreeCtrl m_treeScenes;
	afx_msg void OnSceneOpen();
};
