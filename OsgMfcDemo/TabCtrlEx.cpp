// TabCtrlEx.cpp : 实现文件
//

#include "stdafx.h"
#include "OsgMfcDemo.h"
#include "TabCtrlEx.h"


// CTabCtrlEx

IMPLEMENT_DYNAMIC(CTabCtrlEx, CTabCtrl)

CTabCtrlEx::CTabCtrlEx()
{
}

CTabCtrlEx::~CTabCtrlEx()
{
}


// CTabCtrlEx 消息处理程序
BEGIN_MESSAGE_MAP(CTabCtrlEx, CTabCtrl)
END_MESSAGE_MAP()

BOOL CTabCtrlEx::Create( _In_ DWORD dwStyle, _In_ const RECT &rect, _In_ CWnd *pParentWnd, _In_ UINT nID )
{
    dwStyle |= TCS_OWNERDRAWFIXED;
    BOOL ret= CTabCtrl::Create(dwStyle,rect,pParentWnd,nID);
	return ret;
}

BOOL CTabCtrlEx::CreateEx( _In_ DWORD dwExStyle, _In_ DWORD dwStyle, _In_ const RECT &rect, _In_ CWnd *pParentWnd, _In_ UINT nID )
{
    dwStyle |= TCS_OWNERDRAWFIXED;
    return CTabCtrl::CreateEx(dwExStyle,dwStyle,rect,pParentWnd,nID);
}

BOOL CTabCtrlEx::PreSubclassWindow(CREATESTRUCT &cs)
{
    ModifyStyle(0, TCS_OWNERDRAWFIXED);
    return CTabCtrl::PreCreateWindow(cs);
}

void CTabCtrlEx::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    if(lpDrawItemStruct->CtlType == ODT_TAB)
    {
        CRect rect = lpDrawItemStruct->rcItem;
        INT nTabIndex = lpDrawItemStruct->itemID;
        if (nTabIndex < 0) return;

        TCHAR label[64];
        TC_ITEM tci;
        tci.mask = TCIF_TEXT|TCIF_IMAGE;
        tci.pszText = label;
        tci.cchTextMax = 63;
        GetItem(nTabIndex, &tci );

        CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        if (!pDC) return;
        int nSavedDC = pDC->SaveDC();

        //填充背景色
        COLORREF rcBack;
        if (lpDrawItemStruct->itemState & CDIS_SELECTED  )
            rcBack = RGB(255, 255,255);
        else if(lpDrawItemStruct->itemState & (CDIS_DISABLED | CDIS_GRAYED) )
            rcBack = RGB(0, 255, 0);
        else
            rcBack = GetSysColor(COLOR_BTNFACE);
        pDC->FillSolidRect(rect, rcBack);

        rect.top += ::GetSystemMetrics(SM_CYEDGE);

        pDC->SetBkMode(TRANSPARENT);

        //绘制图片
        CImageList *pImageList = GetImageList();
        if (pImageList && tci.iImage >= 0)
        {
            rect.left += pDC->GetTextExtent(_T(" ")).cx;       // Margin

            // Get height of image so we
            IMAGEINFO info;
            pImageList->GetImageInfo(tci.iImage, &info);
            CRect ImageRect(info.rcImage);
            INT nYpos = rect.top;

            pImageList->Draw(pDC, tci.iImage, CPoint(rect.left, nYpos), ILD_TRANSPARENT);
            rect.left += ImageRect.Width();
        }

        //绘制字体
        COLORREF txtColor;
        if (lpDrawItemStruct->itemState & CDIS_SELECTED  )
        {
            rect.top -= ::GetSystemMetrics(SM_CYEDGE);

            txtColor = RGB(0,0,255);
        }
        else if(lpDrawItemStruct->itemState & (CDIS_DISABLED | CDIS_GRAYED) )
            txtColor = RGB(128, 128, 128);
        else
            txtColor = GetSysColor(COLOR_WINDOWTEXT);
        pDC->SetTextColor(txtColor);
		int r=rect.right;
		rect.right-=15;
        pDC->DrawText(label, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		rect.right=r;
		rect.left=rect.right-17;
		rect.top+=3;
		rect.bottom-=6;
		pDC->DrawFrameControl(&rect,DFCS_CAPTIONCLOSE,DFCS_BUTTONPUSH);
        pDC->RestoreDC(nSavedDC);

    }
}

