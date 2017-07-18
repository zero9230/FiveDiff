// DoctorInfoView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "DoctorInfoView.h"
//#include "Includes_app.h"

// CDoctorInfoView

IMPLEMENT_DYNCREATE(CDoctorInfoView, CBCGPChartExampleView)

CDoctorInfoView::CDoctorInfoView()
: CBCGPChartExampleView(CDoctorInfoView::IDD)
{


}

CDoctorInfoView::~CDoctorInfoView()
{

}

void CDoctorInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_DoctorInfoList);
}

BEGIN_MESSAGE_MAP(CDoctorInfoView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CDoctorInfoView 诊断

#ifdef _DEBUG
void CDoctorInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDoctorInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDoctorInfoView 消息处理程序
BOOL CDoctorInfoView::InitDoctorInfoForm()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_DoctorInfoList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_DoctorInfoList.SetExtendedStyle(m_DoctorInfoList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_DoctorInfoList.SetRowHeigt(20);


	// 为CRP列表视图控件添加四列
	m_DoctorInfoList.InsertColumn(0, _T("NO."), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_DoctorInfoList.InsertColumn(1, _T("医师"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_DoctorInfoList.InsertColumn(2, _T("备注"), LVCFMT_CENTER, rect.Width() /2 , 2);

	// 在CRP列表视图控件中插入列表项，并设置列表子项文本
	m_DoctorInfoList.InsertItem(0, _T("123456"));
	m_DoctorInfoList.SetItemText(0, 1, _T("NANCY"));
	m_DoctorInfoList.SetItemText(0, 2, _T("空"));


	return TRUE;
}

void CDoctorInfoView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	InitDoctorInfoForm();
}


BOOL CDoctorInfoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}
