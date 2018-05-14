// LineColorListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "CMyBCGPListCtrl.h"
//#include "CMyBCGPHeaderCtrl.h"
//#include "Includes_app.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineColorListCtrl

CMyBCGPListCtrl::CMyBCGPListCtrl()
{
	m_color = RGB(0, 0, 0);
}

CMyBCGPListCtrl::~CMyBCGPListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyBCGPListCtrl, CBCGPListCtrl)
	//{{AFX_MSG_MAP(CLineColorListCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyBCGPListCtrl message handlers


void CMyBCGPListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;
	*pResult = CDRF_DODEFAULT;

	if (CDDS_PREPAINT == pNMCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else
	{
		if (CDDS_ITEMPREPAINT == pNMCD->nmcd.dwDrawStage)
		{
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
		}
		else
		{
			if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pNMCD->nmcd.dwDrawStage)
			{
				COLORREF clrNewTextColor, clrNewBkColor;
				int nItem = static_cast<int>(pNMCD->nmcd.dwItemSpec);
				//设置背景色
				if (nItem % 2 == 0)
				{
					clrNewBkColor = RGB(100, 100, 0);
				}
				else
				{
					clrNewBkColor = RGB(255, 255, 255);
				}
				//设置前景色
				clrNewTextColor = RGB(0, 0, 0);

				pNMCD->clrText = clrNewTextColor;
				pNMCD->clrTextBk = clrNewBkColor;
				*pResult = CDRF_DODEFAULT;
			}
		}
	}*/
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;
	*pResult = CDRF_DODEFAULT;

	if (CDDS_PREPAINT == pNMCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else
	{
		if (CDDS_ITEMPREPAINT == pNMCD->nmcd.dwDrawStage)
		{
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
		}
		else
		{
			if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pNMCD->nmcd.dwDrawStage)
			{
				TEXT_BK tb;

				if (MapItemColor.Lookup(pNMCD->nmcd.dwItemSpec, tb))
					// 根据在 SetItemColor(DWORD iItem, COLORREF color) 设置的     
					// ITEM号和COLORREF 在摸板中查找，然后进行颜色赋值。     
				{
					pNMCD->clrText = tb.colText;
					pNMCD->clrTextBk = tb.colTextBk;
					*pResult = CDRF_DODEFAULT;
				}
			}
		}
	}

}

void CMyBCGPListCtrl::ClearColor()
{
	MapItemColor.RemoveAll();
}

void CMyBCGPListCtrl::SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor)
{
	TEXT_BK tb;
	tb.colText = TextColor;
	tb.colTextBk = TextBkColor;


	MapItemColor.SetAt(iItem, tb);//设置某行的颜色。   
	this->RedrawItems(iItem, iItem);//重新染色   

	//this->SetCheck(iItem,1);   
	this->SetFocus();    //设置焦点   
	UpdateWindow();
}


void CMyBCGPListCtrl::SetAllItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor)
{
	//INT_PTR ncount = this->GetItemCount();
	TEXT_BK tb;
	tb.colText = TextColor;
	tb.colTextBk = TextBkColor;

	if (iItem > 0)
	{
		for (DWORD numItem = 0; numItem < iItem; numItem++)
		{
			//iItem = i;   
			MapItemColor.SetAt(numItem, tb);
			this->RedrawItems(numItem, numItem);
		}
	}

	return;

}


void CMyBCGPListCtrl::SetRowHeigt(int nHeight)
{
	m_nItemHeight = nHeight;
	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void CMyBCGPListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (m_nItemHeight>0)
	{
		lpMeasureItemStruct->itemHeight = m_nItemHeight;
	}
}

void CMyBCGPListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void CMyBCGPListCtrl::DrawItem(LPDRAWITEMSTRUCT lpMeasureItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpMeasureItemStruct->hDC);
	LVITEM lvi = { 0 };
	lvi.mask = LVIF_STATE;//|LVIF_IMAGE; 
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED;
	lvi.iItem = lpMeasureItemStruct->itemID;
	BOOL bGet = GetItem(&lvi);
	//高亮显示
	BOOL bHighlight = ((lvi.state & LVIS_DROPHILITED) || ((lvi.state & LVIS_SELECTED) &&
		((GetFocus() == this) || (GetStyle() & LVS_SHOWSELALWAYS))));
	// 画文本背景 
	CRect rcBack = lpMeasureItemStruct->rcItem;
	pDC->SetBkMode(TRANSPARENT);
	if (bHighlight) //如果被选中
	{
		pDC->SetTextColor(RGB(255, 255, 255)); //文本为白色
		pDC->FillRect(rcBack, &CBrush(RGB(30, 144, 255)));
	}
	else
	{
		if (lpMeasureItemStruct->itemID % 2 == 0)
		{
			pDC->SetTextColor(RGB(0, 0, 0));       //文本为黑色
			pDC->FillRect(rcBack, &CBrush(RGB(240, 255, 240)));//背景色为浅绿色
			//pDC->FillRect(rcBack, &CBrush(RGB(0, 0, 0)));
		}
		else
		{
			pDC->SetTextColor(RGB(0, 0, 0));       //文本为黑色
			pDC->FillRect(rcBack, &CBrush(RGB(255, 255, 255)));
		}
	}
	if (lpMeasureItemStruct->itemAction & ODA_DRAWENTIRE)
	{
		//写文本 
		CString szText;
		int nCollumn = GetHeaderCtrl().GetItemCount();//列数
		for (int i = 0; i < GetHeaderCtrl().GetItemCount(); i++)
		{ //循环得到文本 
			CRect rcItem;
			if (!GetSubItemRect(lpMeasureItemStruct->itemID, i, LVIR_LABEL, rcItem))
				continue;
			szText = GetItemText(lpMeasureItemStruct->itemID, i);
			rcItem.left += 5; rcItem.right -= 1;
			pDC->DrawText(szText, lstrlen(szText), &rcItem, DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
		}
	}

	// TODO:  添加您的代码以绘制指定项
/*	TCHAR lpBuffer[256];

	LV_ITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_PARAM;
	lvi.iItem = lpMeasureItemStruct->itemID;
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer;
	lvi.cchTextMax = sizeof(lpBuffer);
	VERIFY(GetItem(&lvi));

	LV_COLUMN lvc, lvcprev;
	::ZeroMemory(&lvc, sizeof(lvc));
	::ZeroMemory(&lvcprev, sizeof(lvcprev));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;
	lvcprev.mask = LVCF_WIDTH | LVCF_FMT;

	CDC* pDC;
	pDC = CDC::FromHandle(lpMeasureItemStruct->hDC);
	CRect rtClient;
	GetClientRect(&rtClient);
	for (int nCol = 0; GetColumn(nCol, &lvc); nCol++)
	{
		if (nCol > 0)
		{
			// Get Previous Column Width in order to move the next display item
			GetColumn(nCol - 1, &lvcprev);
			lpMeasureItemStruct->rcItem.left += lvcprev.cx;
			lpMeasureItemStruct->rcItem.right += lpMeasureItemStruct->rcItem.left;
		}

		CRect rcItem;
		if (!GetSubItemRect(lpMeasureItemStruct->itemID, nCol, LVIR_LABEL, rcItem))
			continue;

		::ZeroMemory(&lvi, sizeof(lvi));
		lvi.iItem = lpMeasureItemStruct->itemID;
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.iSubItem = nCol;
		lvi.pszText = lpBuffer;
		lvi.cchTextMax = sizeof(lpBuffer);
		VERIFY(GetItem(&lvi));
		CRect rcTemp;
		rcTemp = rcItem;

		if (nCol == 0)
		{
			rcTemp.left -= 2;
		}

		if (lpMeasureItemStruct->itemState & ODS_SELECTED)
		{
			pDC->FillSolidRect(&rcTemp, GetSysColor(COLOR_HIGHLIGHT));
			pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
		{
			COLORREF color;
			color = GetBkColor();
			pDC->FillSolidRect(rcTemp, color);

			if (FindColColor(nCol, color))
			{
				pDC->FillSolidRect(rcTemp, color);
			}
			if (FindItemColor(nCol, lpMeasureItemStruct->itemID, color))
			{
				pDC->FillSolidRect(rcTemp, color);
			}

			//pDC->SetTextColor(m_color);
		}

		pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));

		UINT   uFormat = DT_CENTER;
		if (m_Header.m_Format[nCol] == '0')
		{
			uFormat = DT_LEFT;
		}
		else if (m_Header.m_Format[nCol] == '1')
		{
			uFormat = DT_CENTER;
		}
		else if (m_Header.m_Format[nCol] == '2')
		{
			uFormat = DT_RIGHT;
		}
		TEXTMETRIC metric;
		pDC->GetTextMetrics(&metric);
		int ofst;
		ofst = rcItem.Height() - metric.tmHeight;
		rcItem.OffsetRect(0, ofst / 2);
		pDC->SetTextColor(m_color);
		COLORREF color;
		if (FindColTextColor(nCol, color))
		{
			pDC->SetTextColor(color);
		}
		if (FindItemTextColor(nCol, lpMeasureItemStruct->itemID, color))
		{
			pDC->SetTextColor(color);
		}
		CFont nFont, *nOldFont;
		nFont.CreateFont(m_fontHeight, m_fontWith, 0, 0, 0, FALSE, FALSE, 0, 0, 0, 0, 0, 0, _TEXT("宋体"));//创建字体 
		nOldFont = pDC->SelectObject(&nFont);
		DrawText(lpMeasureItemStruct->hDC, lpBuffer, strlen(lpBuffer),
			&rcItem, uFormat);

		pDC->SelectStockObject(SYSTEM_FONT);
	}
	*/
}

// 设置表头高度
void CMyBCGPListCtrl::SetHeaderHeight(float Height) //设置表头高度
{
	m_Header.m_Height = Height;
}