// WorkSheetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "WorkSheetView.h"
//#include "Includes_app.h"

// CWorkSheetView

IMPLEMENT_DYNCREATE(CWorkSheetView, CBCGPChartExampleView)

CWorkSheetView::CWorkSheetView()
: CBCGPChartExampleView(CWorkSheetView::IDD)
{

}

CWorkSheetView::~CWorkSheetView()
{

}

void CWorkSheetView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WORK_LIST, m_worksheetList);
}


BEGIN_MESSAGE_MAP(CWorkSheetView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CWorkSheetView 诊断

#ifdef _DEBUG
void CWorkSheetView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CWorkSheetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG



// CWorkSheetView 消息处理程序


void CWorkSheetView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	InitWorksheetForm();

}



BOOL CWorkSheetView::InitWorksheetForm()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_worksheetList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_worksheetList.SetExtendedStyle(m_worksheetList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_worksheetList.SetRowHeigt(20);


	// 为CRP列表视图控件添加四列
	m_worksheetList.InsertColumn(0, _T("样本号"), LVCFMT_CENTER, rect.Width() / 7, 0);
	m_worksheetList.InsertColumn(1, _T("患者ID"), LVCFMT_CENTER, rect.Width() / 7, 1);
	m_worksheetList.InsertColumn(2, _T("测试模式"), LVCFMT_CENTER, rect.Width() / 7, 2);
	m_worksheetList.InsertColumn(3, _T("试管架"), LVCFMT_CENTER, rect.Width() / 7, 3);
	m_worksheetList.InsertColumn(4, _T("试管"), LVCFMT_CENTER, rect.Width() / 7, 4);
	m_worksheetList.InsertColumn(5, _T("状态"), LVCFMT_CENTER, rect.Width() / 7, 5);
	m_worksheetList.InsertColumn(6, _T("评语"), LVCFMT_CENTER, rect.Width() / 7, 6);

	// 在CRP列表视图控件中插入列表项，并设置列表子项文本
	m_worksheetList.InsertItem(0, _T("101"));
	m_worksheetList.SetItemText(0, 1, _T("Auto54321"));
	m_worksheetList.SetItemText(0, 2, _T("CBC+RET"));
	m_worksheetList.SetItemText(0, 3, _T("999999"));
	m_worksheetList.SetItemText(0, 4, _T("1"));
	m_worksheetList.SetItemText(0, 5, _T("已测"));

	m_worksheetList.InsertItem(0, _T("102"));
	m_worksheetList.SetItemText(0, 1, _T("54321"));
	m_worksheetList.SetItemText(0, 2, _T("CBC+RET"));
	m_worksheetList.SetItemText(0, 3, _T("999999"));
	m_worksheetList.SetItemText(0, 4, _T("1"));
	m_worksheetList.SetItemText(0, 5, _T("待测"));

	return TRUE;
}

void CWorkSheetView::UpdateWorksheetForm()
{
	m_worksheetList.DeleteAllItems();

}

BOOL CWorkSheetView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}
