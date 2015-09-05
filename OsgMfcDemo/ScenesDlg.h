#pragma once

// CScenesDlg 对话框

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
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
};
