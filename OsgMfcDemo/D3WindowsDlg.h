#pragma once
#include "afxcmn.h"
#include <list>
#include "D3WindowDlg.h"
#include "OsgScene.h"
#include "OsgManager.h"
#include "TabCtrlEx.h"
using namespace std;

// CD3WindowsDlg 对话框
extern class COsgManager;
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
	COsgManager* m_osgManager;
	CD3WindowDlg*m_selectD3WindowDlg;
public:
	CD3WindowDlg* SelectD3WindowDlg() const { return m_selectD3WindowDlg; }
	void SelectD3WindowDlg(CD3WindowDlg* val) { m_selectD3WindowDlg = val; }

	CD3WindowDlg*OpenOrGetD3Window(COsgScene* scene);
	CD3WindowDlg*OpenNewD3Window(COsgScene* scene);
	CD3WindowDlg*GetD3Window(COsgScene* scene);
	void CloseD3Window(COsgScene* scene);
	void CloseAllD3Window();
	void UpdateView();
	void BindingOsgManager(COsgManager* manager);
	void Refresh();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTabCtrlEx m_tab3DWinCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTcnSelchangeTab3dwins(NMHDR *pNMHDR, LRESULT *pResult);
};
