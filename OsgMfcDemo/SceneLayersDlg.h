#pragma once


// CSceneLayersDlg 对话框

class CSceneLayersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSceneLayersDlg)

public:
	CSceneLayersDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSceneLayersDlg();

// 对话框数据
	enum { IDD = IDD_PANEL_LAYERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
