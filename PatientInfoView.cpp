// PatientInfoView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "PatientInfoView.h"
//#include "Includes_app.h"

// CPatientInfoView

IMPLEMENT_DYNCREATE(CPatientInfoView, CBCGPChartExampleView)

CPatientInfoView::CPatientInfoView()
: CBCGPChartExampleView(CPatientInfoView::IDD)
{

}

CPatientInfoView::~CPatientInfoView()
{
}

void CPatientInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_PatientInfoList);
}

BEGIN_MESSAGE_MAP(CPatientInfoView, CFormView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPatientInfoView 诊断

#ifdef _DEBUG
void CPatientInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPatientInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPatientInfoView 消息处理程序


BOOL CPatientInfoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}


void CPatientInfoView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	InitPaitientInfoForm();
}



BOOL CPatientInfoView::InitPaitientInfoForm()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_PatientInfoList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_PatientInfoList.SetExtendedStyle(m_PatientInfoList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_PatientInfoList.SetRowHeigt(20);


	// 为CRP列表视图控件添加四列
	m_PatientInfoList.InsertColumn(0, _T("患者ID号"), LVCFMT_CENTER, rect.Width() / 8, 0);
	m_PatientInfoList.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, rect.Width() / 8, 1);
	m_PatientInfoList.InsertColumn(2, _T("别名"), LVCFMT_CENTER, rect.Width() / 8, 2);
	m_PatientInfoList.InsertColumn(3, _T("性别"), LVCFMT_CENTER, rect.Width() / 8, 3);
	m_PatientInfoList.InsertColumn(4, _T("出生日期"), LVCFMT_CENTER, rect.Width() / 8, 4);
	m_PatientInfoList.InsertColumn(5, _T("病区"), LVCFMT_CENTER, rect.Width() / 8, 5);
	m_PatientInfoList.InsertColumn(6, _T("医师"), LVCFMT_CENTER, rect.Width() / 8, 6);
	m_PatientInfoList.InsertColumn(7, _T("患者评语"), LVCFMT_CENTER, rect.Width() / 8, 6);

	// 在CRP列表视图控件中插入列表项，并设置列表子项文本
	m_PatientInfoList.InsertItem(0, _T("123456"));
	m_PatientInfoList.SetItemText(0, 1, _T("NANCY"));
	m_PatientInfoList.SetItemText(0, 2, _T("HELLEN"));
	m_PatientInfoList.SetItemText(0, 3, _T("女"));
	m_PatientInfoList.SetItemText(0, 4, _T("1991/01/1"));
	m_PatientInfoList.SetItemText(0, 5, _T("1"));
	m_PatientInfoList.SetItemText(0, 7, _T("HPC test"));

	return TRUE;
}
