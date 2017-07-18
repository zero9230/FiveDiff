// QualityControlView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityControlView.h"
#include "ControlChooese.h"


// CQualityControlView
CQualityTestView	m_QualityTestPage;

IMPLEMENT_DYNCREATE(CQualityControlView, CBCGPChartExampleView)

CQualityControlView::CQualityControlView()
: CBCGPChartExampleView(CQualityControlView::IDD)
{

}

CQualityControlView::~CQualityControlView()
{

}

void CQualityControlView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQualityControlView, CBCGPChartExampleView)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CQualityControlView 诊断

#ifdef _DEBUG
void CQualityControlView::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CQualityControlView::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG


// CQualityControlView 消息处理程序


void CQualityControlView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CBCGPChartExampleView::OnPaint()
}


void CQualityControlView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	CRect rectTab;
	GetDlgItem(IDC_QUALITYCONTROL_TAB)->GetWindowRect(&rectTab);
	ScreenToClient(&rectTab);

	m_QualityTab.Create(CBCGPTabWnd::STYLE_3D, rectTab, this, 1, CBCGPTabWnd::LOCATION_TOP);


	m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
	m_QualityChartPage.Create(IDD_QUALITY_CONTROL_CHART, &m_QualityTab);
	m_QualityTargetPage.Create(IDD_QUALITY_TARGETVALUE, &m_QualityTab);
	m_QualityTestPage.Create(IDD_QUALITY_TESTVIEW, &m_QualityTab);

	m_QualityTab.AddTab(&m_RadarPage, L"雷达图", 0);
	m_QualityTab.AddTab(&m_QualityChartPage, L"质控图", 1);
	m_QualityTab.AddTab(&m_QualityTargetPage, L"靶值", 2);
	m_QualityTab.AddTab(&m_QualityTestPage, L"质控计数", 3);

	CRect rc;
	m_QualityTab.GetClientRect(rc);
	m_QualityTab.SetResizeMode(CBCGPTabWnd::RESIZE_VERT);
	rc.top += 27;
	rc.bottom -= 5;
	rc.left += 5;
	rc.right -= 10;

	m_RadarPage.MoveWindow(&rc);
	m_QualityChartPage.MoveWindow(&rc);
	m_QualityTargetPage.MoveWindow(&rc);
	m_QualityTestPage.MoveWindow(&rc);


	//m_QualityTab.InsertItem(0,_T("雷达图"));
	//m_QualityTab.InsertItem(1,_T("质控图"));
	//m_QualityTab.InsertItem(2,_T("靶值"));
	//m_QualityTab.InsertItem(3,_T("质控计数"));
	//m_QualityTab.InsertItem(3,_T("其他2"));
	//创建两个对话框
	//m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
	//m_QualityChartPage.Create(IDD_QUALITY_CONTROL_CHART, &m_QualityTab);
	//m_QualityTargetPage.Create(IDD_QUALITY_TARGETVALUE, &m_QualityTab);
	//m_QualityTestPage.Create(IDD_QUALITY_TESTVIEW, &m_QualityTab);
	//设定在Tab内显示的范围
	//CRect rc;
	//m_QualityTab.GetClientRect(rc);
	//rc.top += 20;
	//rc.bottom -= 0;
	//rc.left += 0;
	//rc.right -= 0;
	//m_RadarPage.MoveWindow(&rc);
	//m_QualityChartPage.MoveWindow(&rc);
	//m_QualityTargetPage.MoveWindow(&rc);
	//m_QualityTestPage.MoveWindow(&rc);

	//把对话框对象指针保存起来
	//pDialog[0] = &m_RadarPage;
	//pDialog[1] = &m_QualityChartPage;
	//pDialog[2] = &m_QualityTargetPage;
	//pDialog[3] = &m_QualityTestPage;
	//显示初始页面
	//pDialog[0]->ShowWindow(SW_SHOW);
	//pDialog[1]->ShowWindow(SW_HIDE);
	//pDialog[2]->ShowWindow(SW_HIDE);
	//pDialog[3]->ShowWindow(SW_HIDE);

	// TODO:  在此添加专用代码和/或调用基类
}

HBRUSH CQualityControlView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CBCGPChartExampleView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_QUALITY_TAB:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CQualityControlView::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	//把当前的页面隐藏起来
	//pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//得到新的页面索引
	//m_CurSelTab = m_QualityTab.GetCurSel();
	//把新的页面显示出来
	//pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}



BOOL CQualityControlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此添加专用代码和/或调用基类

	//CLoginDlg	m_LoginDlg;
	//if (m_LoginDlg.DoModal() != IDOK)
	//{
	//return FALSE;
	//}
	CControlChooese m_ControlChoose;
	m_ControlChoose.DoModal();

	return CBCGPChartExampleView::PreCreateWindow(cs);
}
