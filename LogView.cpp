// LogView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "LogView.h"
//#include "Includes_app.h"

// CLogView

IMPLEMENT_DYNCREATE(CLogView, CBCGPChartExampleView)

CLogView::CLogView()
: CBCGPChartExampleView(CLogView::IDD), m_Logtype(0)
{

}

CLogView::~CLogView()
{
}

void CLogView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_LogList);
	DDX_Radio(pDX, IDC_REAGENT_RADIO1, m_Logtype);
}

BEGIN_MESSAGE_MAP(CLogView, CFormView)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_REAGENT_RADIO1, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_CALIBRATION_RADIO2, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_USER_RADIO3, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_DEVELOPMENT_RADIO4, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_ERROR_RADIO5, &CLogView::OnBnClickedLogtypeRadio1)
	ON_BN_CLICKED(IDC_STARTUP_RADIO6, &CLogView::OnBnClickedLogtypeRadio1)
END_MESSAGE_MAP()


// CLogView 诊断

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogView::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLogView 消息处理程序

void CLogView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	InitLogForm();
}


BOOL CLogView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}


BOOL CLogView::InitLogForm()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_LogList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_LogList.SetExtendedStyle(m_LogList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_LogList.SetRowHeigt(20);


	// 为CRP列表视图控件添加四列
	m_LogList.InsertColumn(0, _T("日期/时间"), LVCFMT_CENTER, rect.Width() /6 , 0);
	m_LogList.InsertColumn(1, _T("操作者"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_LogList.InsertColumn(2, _T("描述"), LVCFMT_CENTER, rect.Width() / 2, 2);
	m_LogList.InsertColumn(3, _T("描述"), LVCFMT_CENTER, rect.Width() / 6, 3);


	// 在CRP列表视图控件中插入列表项，并设置列表子项文本
	m_LogList.InsertItem(0, _T("04/11/2016 15:02:30"));
	m_LogList.SetItemText(0, 1, _T("Technican"));
	m_LogList.SetItemText(0, 2, _T("Modification: Forced WBC=128.78, RBC=154.13, HGB=42.37, HCT=174.16, PLT=192.12, RDW=0.35,LMNE=0.95 BY Technican"));
	m_LogList.SetItemText(0, 3, _T(""));
	m_LogList.InsertItem(1, _T("04/11/2016 15:02:30"));
	m_LogList.SetItemText(1, 1, _T("Technican"));
	m_LogList.SetItemText(1, 2, _T("Modification: Forced WBC=128.78, RBC=154.13, HGB=42.37, HCT=174.16, PLT=192.12, RDW=0.35,LMNE=0.95 BY Technican"));
	m_LogList.SetItemText(1, 3, _T(""));



	return TRUE;
}


void CLogView::OnBnClickedLogtypeRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	switch(m_Logtype)
	{
	case 0:
		MessageBox(L"1");
		break;
	case 1:
		MessageBox(L"2");
		break;
	case 2:
		MessageBox(L"3");
		break;
	case 3:
		MessageBox(L"4");
		break;
	case 4:
		MessageBox(L"5");
		break;
	case 5:
		MessageBox(L"6");
		break;
	default: 
		break;
	
	}
}
