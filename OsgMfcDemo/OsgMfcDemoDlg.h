
// OsgMfcDemoDlg.h : 头文件
//

#pragma once
#include "OsgManager.h"
#include "FileSourceDlg.h"
#include "ScenesDlg.h"
#include "SceneLayersDlg.h"
#include "D3WindowsDlg.h"


// COsgMfcDemoDlg 对话框
class COsgMfcDemoDlg : public CDialogEx
{
// 构造
public:
	COsgMfcDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OSGMFCDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	COsgManager m_osgManager;
	CFileSourceDlg m_fileSourceDlg;
	CScenesDlg m_scenesDlg;
	CSceneLayersDlg m_sceneLayersDlg;
	CD3WindowsDlg m_d3WindowsDlg;

	int m_leftWidth;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditRect3d();
	afx_msg void OnOpen();
	afx_msg void OnImport();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	void UpdatePosition();
};
