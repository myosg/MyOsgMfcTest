#pragma once
#include "afxcmn.h"
#include <list>
#include "D3WindowDlg.h"
using namespace std;

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

private:
	list<CD3WindowDlg*> m_d3WindowList;

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTabCtrl m_tab3DWinCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	CD3WindowDlg*OpenOrGetD3Window(CString sceneName);
	CD3WindowDlg*OpenNewD3Window(CString sceneName);
	CD3WindowDlg*GetD3Window(CString sceneName);
	void CloseD3Window(CString sceneName);
	afx_msg void OnTcnSelchangeTab3dwins(NMHDR *pNMHDR, LRESULT *pResult);
	void UpdateView();
};
