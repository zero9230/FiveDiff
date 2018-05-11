//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2014 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPChartExampleView.cpp : implementation of the CBCGPChartExampleView class
//

#include "stdafx.h"
#include "BCGPChartExample.h"

#include "MainFrm.h"
#include "BCGPChartExampleDoc.h"
#include "BCGPChartExampleView.h"
//
//#include "LogProcedure.h"
#include "Includes_app.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define MAINTAINCFG_PATH  _T("./Config/maintaincfg.ini")
//#define SYSTEMCFG_PATH	_T("./Config/systemcfg.ini")
//#define SYSTEMCFG2_PATH	_T ("./Config/systemcfg2.ini")
//#define SYSTEMCFG3_PATH	_T ("./Config/systemcfg3.ini")
//#define LOG_PATH	_T("./Config/logfile.ini")

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleView


IMPLEMENT_DYNCREATE(CBCGPChartExampleView, CBCGPFormView)

BEGIN_MESSAGE_MAP(CBCGPChartExampleView, CBCGPFormView)
	//{{AFX_MSG_MAP(CBCGPChartExampleView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CBCGPFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBCGPFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleView construction/destruction

CBCGPChartExampleView::CBCGPChartExampleView(UINT id)
	: CBCGPFormView(id == 0 ? CBCGPChartExampleView::IDD : id)
{
	EnableVisualManagerStyle();
	EnableLayout();

	SetWhiteBackground();

	m_bIsReady = FALSE;
	m_bIsDarkBackground = FALSE;
	m_bIsTexturedTheme = FALSE;
	m_bIsFlatTheme = FALSE;
}

CBCGPChartExampleView::~CBCGPChartExampleView()
{
}

BOOL CBCGPChartExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleView diagnostics

#ifdef _DEBUG
void CBCGPChartExampleView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

void CBCGPChartExampleView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}


CBCGPChartExampleDoc* CBCGPChartExampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBCGPChartExampleDoc)));
	return (CBCGPChartExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleView message handlers

void CBCGPChartExampleView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectTitle;
	GetDlgItem(IDC_TITLE)->GetWindowRect(rectTitle);
  	ScreenToClient(rectTitle);

#ifdef _BCGSUITE_INC_
	CFont* pOldFont = dc.SelectObject(&globalData.fontBold);
#else
	CFont* pOldFont = dc.SelectObject(&globalData.fontCaption);
#endif

	dc.SetTextColor(globalData.clrWindowText);
	dc.SetBkMode(TRANSPARENT);
	
    dc.DrawText(m_strTitle, rectTitle, DT_SINGLELINE | DT_END_ELLIPSIS);

	dc.SelectObject(pOldFont);
}

LRESULT CBCGPChartExampleView::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = CBCGPFormView::HandleInitDialog (wParam, lParam);

	if (GetLayout() != NULL)
	{
		UpdateData(FALSE);
		SetupLayout();
	}

	return lRes;
}

void CBCGPChartExampleView::OnInitialUpdate() 
{
	CBCGPFormView::OnInitialUpdate();

	if (m_bIsReady)
	{
		return;
	}
	
	srand((unsigned)time(NULL));
	GetParentFrame()->RecalcLayout();
	if (AfxGetMainWnd() == NULL)
	{
		return;
	}	
	CBCGPOutlookBarPane m_wndShortcutsPane1;
	CBCGPOutlookBar			m_wndShortcutsBar;

	int nID = GetDlgCtrlID() - AFX_IDW_PANE_FIRST + 1;

	//m_wndShortcutsBar.Gets;//GetFeatureName(nID, m_strTitle);
	//m_Feature = workspace.GetFeature(nID);

	CBCGPChartVisualObject* pChart = GetChart();
	if (pChart != NULL)
	{
		pChart->ShowAxisIntervalInterlacing(BCGP_CHART_X_PRIMARY_AXIS);
	}
	//((CMainFrame*)AfxGetMainWnd())->GetFeatureName(nID, m_strTitle);
	//m_Feature =((CMainFrame*)AfxGetMainWnd())->GetFeature(nID);

	//UpdateChartColorTheme(((CMainFrame*)AfxGetMainWnd())->GetColorTheme());

}

void CBCGPChartExampleView::SetupLayout()
{
	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	if (pLayout != NULL && GetCtrl() != NULL)
	{
		pLayout->AddAnchor(GetCtrl()->GetDlgCtrlID(), CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
	}
}


void CBCGPChartExampleView::SetDefaultLineWidth()
{
	CBCGPChartVisualObject* pChart = GetChart();
	if (pChart == NULL)
	{
		return;
	}

	ASSERT_VALID(pChart);

	for (int i = 0; i < pChart->GetSeriesCount(); i++)
	{
		CBCGPChartSeries* pSeries = pChart->GetSeries(i);
		ASSERT_VALID(pSeries);

		BCGPChartFormatSeries style = pSeries->GetSeriesFormat();
		style.SetSeriesLineWidth(theApp.GetDefaultLineWidth());

		pSeries->SetSeriesFormat(style);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleView printing
//打印预览，会隐藏当前页面，容易造成问题
void CBCGPChartExampleView::OnFilePrintPreview() 
{
	//CView* pCurView=pMainFrame->GetCurrentView();
#ifdef _BCGSUITE_INC_
    AFXPrintPreview(this);
#else
	BCGPPrintPreview (this);
#endif
}

BOOL CBCGPChartExampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBCGPChartExampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBCGPChartExampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CBCGPChartExampleView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CBCGPBaseVisualCtrl* pCtrl = GetCtrl();
	if (pCtrl != NULL)
	{
		// Since D2D has some print problems, active the GDI graphics manager:
		pCtrl->SetGraphicsManager(CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI);
		
		pCtrl->DoPrint(pDC, pInfo);

		// Restore default graphics manager:
		pCtrl->SetGraphicsManager(CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_DEFAULT);
	}
}

void CBCGPChartExampleView::UpdateChartColorTheme(int nTheme)
{

}

