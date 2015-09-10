#pragma once
#include "OsgScene.h"
#include "OsgRender.h"


// CD3WindowDlg 对话框

class CD3WindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CD3WindowDlg)

public:
	CD3WindowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CD3WindowDlg();

// 对话框数据
	enum { IDD = IDD_3D_WINDOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	COsgScene* m_osgScene;
	COsgRender* m_osgRender;
	CRenderingThread* m_thread;
public:
	COsgScene* OsgScene() const { return m_osgScene; }
	void OsgScene(COsgScene* val) { m_osgScene = val; }
	BOOL StartRender();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
