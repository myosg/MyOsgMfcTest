
// OsgMfcDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OsgMfcDemo.h"
#include "OsgMfcDemoDlg.h"
#include "afxdialogex.h"
#include "OsgFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
    public:
        CAboutDlg();

// 对话框数据
        enum { IDD = IDD_ABOUTBOX };

    protected:
        virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV 支持

// 实现
    protected:
        DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COsgMfcDemoDlg 对话框



COsgMfcDemoDlg::COsgMfcDemoDlg(CWnd *pParent /*=NULL*/)
    : CDialogEx(COsgMfcDemoDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COsgMfcDemoDlg::DoDataExchange(CDataExchange *pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COsgMfcDemoDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_COMMAND(ID_EDIT_RECT3D, &COsgMfcDemoDlg::OnEditRect3d)
    ON_COMMAND(ID_OPEN, &COsgMfcDemoDlg::OnOpen)
    ON_COMMAND(ID_IMPORT, &COsgMfcDemoDlg::OnImport)
	ON_WM_SIZING()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// COsgMfcDemoDlg 消息处理程序

BOOL COsgMfcDemoDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu *pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    ShowWindow(SW_MAXIMIZE);

    // TODO: 在此添加额外的初始化代码
	m_leftWidth=250;

	m_fileSourceDlg.Create(IDD_PANEL_SOURCE,this);
	m_fileSourceDlg.ShowWindow(SW_SHOW);

	m_d3WindowsDlg.Create(IDD_3D_WINS,this);
	m_d3WindowsDlg.ShowWindow(SW_SHOW);

	m_scenesDlg.Create(IDD_PANEL_SCENES,this);
	m_scenesDlg.ShowWindow(SW_SHOW);

	m_sceneLayersDlg.Create(IDD_PANEL_LAYERS,this);
	m_sceneLayersDlg.ShowWindow(SW_SHOW);

	m_osgManager.FileSourceDlg(&m_fileSourceDlg);
	m_osgManager.ScenesDlg(&m_scenesDlg);
	m_osgManager.D3WindowsDlg(&m_d3WindowsDlg);
	m_osgManager.SceneLayersDlg(&m_sceneLayersDlg);

	m_fileSourceDlg.BindingOsgManager(&m_osgManager);
	m_scenesDlg.BindingOsgManager(&m_osgManager);
	m_d3WindowsDlg.BindingOsgManager(&m_osgManager);
	m_sceneLayersDlg.BindingOsgManager(&m_osgManager);

	UpdatePosition();

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void COsgMfcDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
        CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COsgMfcDemoDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
        CDialogEx::OnPaint();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COsgMfcDemoDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

//打开
void COsgMfcDemoDlg::OnOpen()
{
    // TODO: 在此添加命令处理程序代码
    CFileDialog dialog(TRUE,_T(".osg"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                       _T("模型文件|*.osg;*.osgt;*.ive|所有文件|*.*||"),NULL);
    if(dialog.DoModal()==IDOK)
    {
        CString fileName=dialog.GetPathName();
		if (m_osgManager.FileSource()->Contains(fileName))
		{
			MessageBox(_T("已存在该文件！"));
			return;
		}
        COsgFile *osg=new COsgFile(fileName);
        m_osgManager.FileSource()->Add(osg);
		m_fileSourceDlg.Refresh();
    }
}
//导入
void COsgMfcDemoDlg::OnImport()
{
    // TODO: 在此添加命令处理程序代码

}

void COsgMfcDemoDlg::OnEditRect3d()
{
    // TODO: 在此添加命令处理程序代码
	
}




void COsgMfcDemoDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
}


void COsgMfcDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	UpdatePosition();
}

void COsgMfcDemoDlg::UpdatePosition()
{
	RECT rect;
	this->GetClientRect(&rect);
	int height=rect.bottom-rect.top;
	//更新文件资源列表位置
	if (m_fileSourceDlg.GetSafeHwnd()!=NULL)
	{
		//RECT srcRect;
		//m_fileSourceDlg.GetClientRect(&srcRect);
		m_fileSourceDlg.MoveWindow(0,0,m_leftWidth,height*2/5);
	}
	if (m_scenesDlg.GetSafeHwnd()!=NULL)
	{
		m_scenesDlg.MoveWindow(0,height*2/5,m_leftWidth,height/5);
	}

	if (m_sceneLayersDlg.GetSafeHwnd()!=NULL)
	{
		m_sceneLayersDlg.MoveWindow(0,height*3/5,m_leftWidth,height*2/5);
	}

	if (m_d3WindowsDlg.GetSafeHwnd()!=NULL)
	{
		m_d3WindowsDlg.MoveWindow(m_leftWidth+5,0,rect.right-rect.left-m_leftWidth-5,height);
	}
}
