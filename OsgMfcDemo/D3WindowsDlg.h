#pragma once
#include "afxcmn.h"
#include "D3WindowDlg.h"


// CD3WindowsDlg 对话框

class CD3WindowsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CD3WindowsDlg)

public:
	CD3WindowsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CD3WindowsDlg();

// 对话框数据
	enum { IDD = IDD_3D_WINS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTabCtrl m_tab3DWinCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	CD3WindowDlg*AddNewD3Window();
};
