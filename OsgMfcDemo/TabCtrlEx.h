#pragma once


// CTabCtrlEx

class CTabCtrlEx : public CTabCtrl
{
	DECLARE_DYNAMIC(CTabCtrlEx)

public:
	CTabCtrlEx();
	virtual ~CTabCtrlEx();

	virtual BOOL Create(_In_ DWORD dwStyle, _In_ const RECT& rect, _In_ CWnd* pParentWnd, _In_ UINT nID);
	virtual BOOL CreateEx(_In_ DWORD dwExStyle, _In_ DWORD dwStyle, _In_ const RECT& rect, _In_ CWnd* pParentWnd, _In_ UINT nID);
protected:
	virtual BOOL PreSubclassWindow(CREATESTRUCT& cs);
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);  
protected:
	DECLARE_MESSAGE_MAP()
};


