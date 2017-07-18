// QualityRadarView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityRadarView.h"
#include "afxdialogex.h"


// CQualityRadarView 对话框

IMPLEMENT_DYNAMIC(CQualityRadarView, CDialogEx)

CQualityRadarView::CQualityRadarView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQualityRadarView::IDD, pParent)
{
	VERIFY(textfont.CreateFont(
		15,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		GB2312_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		L"宋体"));                 // lpszFacename
}

CQualityRadarView::~CQualityRadarView()
{
}

void CQualityRadarView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADARCHART1, m_RadarChart1);
	DDX_Control(pDX, IDC_RADARCHART2, m_RadarChart2);
	DDX_Control(pDX, IDC_RADARCHART3, m_RadarChart3);
	DDX_Control(pDX, IDC_RADARCHART4, m_RadarChart4);
	DDX_Control(pDX, IDC_RADARCHART5, m_RadarChart5);
	DDX_Control(pDX, IDC_RADARCHART6, m_RadarChart6);
	DDX_Control(pDX, IDC_RADARCHART7, m_RadarChart7);
	DDX_Control(pDX, IDC_RADARCHART8, m_RadarChart8);
	DDX_Control(pDX, IDC_QUALITYMATERIAL_LIST, m_QualityMaterialList);
}


BEGIN_MESSAGE_MAP(CQualityRadarView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CQualityRadarView 消息处理程序


void CQualityRadarView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(255,255,255));
}


BOOL CQualityRadarView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J质控雷达图（文件 %02u）", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X质控雷达图（文件 %02u）", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R质控雷达图（文件 %02u）", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_STATIC0, item_temp);
	GetDlgItem(IDC_STATIC0)->SetFont(&textfont);

	OnInitRadarChart1();
	OnInitRadarChart2();
	OnInitRadarChart3();
	OnInitRadarChart4();
	OnInitRadarChart5();
	OnInitQualityMaterialList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CQualityRadarView::OnInitRadarChart1()
{
	CBCGPChartVisualObject* pChart = m_RadarChart1.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));

	pSeries1->AddDataPoint("WBC", 15.);
	pSeries1->AddDataPoint("LYM%", 10.);
	pSeries1->AddDataPoint("NEU%", 8.);
	pSeries1->AddDataPoint("MONO%", 22.);
	pSeries1->AddDataPoint("EOS%", 22.);
	pSeries1->AddDataPoint("BASO%",18.);

	pSeries2->AddDataPoint(9.);
	pSeries2->AddDataPoint(15.);
	pSeries2->AddDataPoint(19.);
	pSeries2->AddDataPoint(21.);
	pSeries2->AddDataPoint(23.);

	pChart->SetThemeOpacity(30);

	CBCGPChartAxisPolarX* pXAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarX, pChart->GetChartAxis(BCGP_CHART_X_POLAR_AXIS));
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxisPolarY* pYAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarY, pChart->GetChartAxis(BCGP_CHART_Y_POLAR_AXIS));
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	pYAxis->m_bRadialGridLines = FALSE;
	
	OnUpdateChart(1);

}

void CQualityRadarView::OnInitRadarChart2()
{
	CBCGPChartVisualObject* pChart = m_RadarChart2.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));

	pSeries1->AddDataPoint("PLT", 15.);
	pSeries1->AddDataPoint("MPV", 10.);
	pSeries1->AddDataPoint("PDW", 8.);
	pSeries1->AddDataPoint("PCT", 22.);
	pSeries1->AddDataPoint("P-LCR", 22.);

	pSeries2->AddDataPoint(9.);
	pSeries2->AddDataPoint(15.);
	pSeries2->AddDataPoint(19.);
	pSeries2->AddDataPoint(21.);
	pSeries2->AddDataPoint(23.);


	pChart->SetThemeOpacity(30);

	CBCGPChartAxisPolarX* pXAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarX, pChart->GetChartAxis(BCGP_CHART_X_POLAR_AXIS));
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxisPolarY* pYAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarY, pChart->GetChartAxis(BCGP_CHART_Y_POLAR_AXIS));
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	pYAxis->m_bRadialGridLines = FALSE;

	OnUpdateChart(2);
}

void CQualityRadarView::OnInitRadarChart3()
{
	CBCGPChartVisualObject* pChart = m_RadarChart3.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));

	pSeries1->AddDataPoint("RBC", 15.);
	pSeries1->AddDataPoint("HGB", 10.);
	pSeries1->AddDataPoint("HCT", 8.);
	pSeries1->AddDataPoint("MCV", 22.);
	pSeries1->AddDataPoint("MCH", 22.);

	pSeries2->AddDataPoint(9.);
	pSeries2->AddDataPoint(15.);
	pSeries2->AddDataPoint(19.);
	pSeries2->AddDataPoint(21.);
	pSeries2->AddDataPoint(23.);


	pChart->SetThemeOpacity(30);

	CBCGPChartAxisPolarX* pXAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarX, pChart->GetChartAxis(BCGP_CHART_X_POLAR_AXIS));
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxisPolarY* pYAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarY, pChart->GetChartAxis(BCGP_CHART_Y_POLAR_AXIS));
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	pYAxis->m_bRadialGridLines = FALSE;

	OnUpdateChart(3);
}


void CQualityRadarView::OnInitRadarChart4()
{
	CBCGPChartVisualObject* pChart = m_RadarChart4.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));

	pSeries1->AddDataPoint("MCHC", 15.);
	pSeries1->AddDataPoint("RDW-CV", 10.);
	pSeries1->AddDataPoint("RDW-SD", 8.);
	pSeries1->AddDataPoint("ALY%", 22.);
	pSeries1->AddDataPoint("LIC%", 22.);
	pSeries1->AddDataPoint("LIC#", 22.);

	pSeries2->AddDataPoint(9.);
	pSeries2->AddDataPoint(15.);
	pSeries2->AddDataPoint(19.);
	pSeries2->AddDataPoint(21.);
	pSeries2->AddDataPoint(23.);


	pChart->SetThemeOpacity(30);

	CBCGPChartAxisPolarX* pXAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarX, pChart->GetChartAxis(BCGP_CHART_X_POLAR_AXIS));
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxisPolarY* pYAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarY, pChart->GetChartAxis(BCGP_CHART_Y_POLAR_AXIS));
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	pYAxis->m_bRadialGridLines = FALSE;

	OnUpdateChart(4);
}

void CQualityRadarView::OnInitRadarChart5()
{
	CBCGPChartVisualObject* pChart = m_RadarChart5.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));

	pSeries1->AddDataPoint("LYM#", 15.);
	pSeries1->AddDataPoint("NEU#", 10.);
	pSeries1->AddDataPoint("MONO#", 8.);
	pSeries1->AddDataPoint("EOS#", 22.);
	pSeries1->AddDataPoint("BASO#", 22.);
	pSeries1->AddDataPoint("ALY#", 22.);

	pSeries2->AddDataPoint(9.);
	pSeries2->AddDataPoint(15.);
	pSeries2->AddDataPoint(19.);
	pSeries2->AddDataPoint(21.);
	pSeries2->AddDataPoint(23.);


	pChart->SetThemeOpacity(30);

	CBCGPChartAxisPolarX* pXAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarX, pChart->GetChartAxis(BCGP_CHART_X_POLAR_AXIS));
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxisPolarY* pYAxis = DYNAMIC_DOWNCAST(CBCGPChartAxisPolarY, pChart->GetChartAxis(BCGP_CHART_Y_POLAR_AXIS));
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	pYAxis->m_bRadialGridLines = FALSE;

	OnUpdateChart(5);
}

void CQualityRadarView::OnUpdateChart(int num)
{
	UpdateData();
	CBCGPChartVisualObject* pChart;
	//m_wndDataLabelAngle.EnableWindow(m_bShowDataLabels);
	switch (num)
	{
	case 1:
		pChart = m_RadarChart1.GetChart();
		break;
	case 2:
		pChart = m_RadarChart2.GetChart();
		break;
	case 3:
		 pChart = m_RadarChart3.GetChart();
		break;
	case 4:
		pChart = m_RadarChart4.GetChart();
		break;
	case 5:
		pChart = m_RadarChart5.GetChart();
	default:
		break;
	}
	ASSERT_VALID(pChart);

	pChart->ShowDataMarkers();
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	//double dblDataLabelAngle = (m_nDataLabelAngle - 2) * 45;

	//pChart->ShowDataLabels(m_bShowDataLabels, TRUE, TRUE, dblDataLabelAngle);

	for (int i = 0; i < pChart->GetSeriesCount(); i++)
	{
		CBCGPChartPolarSeries* pSeries = DYNAMIC_DOWNCAST(CBCGPChartPolarSeries, pChart->GetSeries(i));
		ASSERT_VALID(pSeries);

		BCGPChartFormatSeries style = pSeries->GetSeriesFormat();

		style.m_curveType = BCGPChartFormatSeries::CCT_SPLINE;

		style.SetSeriesOutlineDashStyle((CBCGPStrokeStyle::BCGP_DASH_STYLE)0);//设置线的样式
		style.SetSeriesLineWidth(1);//设置线的粗细
		// Don't close and don't fill second series:
		pSeries->CloseShape(i == 0, i == 0);

		pSeries->SetSeriesFormat(style);
	}
	pChart->Redraw();
}

BOOL CQualityRadarView::OnInitQualityMaterialList()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_QualityMaterialList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_QualityMaterialList.SetExtendedStyle(m_QualityMaterialList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_QualityMaterialList.SetRowHeigt(20);

	m_QualityMaterialList.DeleteAllItems();//清空列表刷新

	m_QualityMaterialList.DeleteColumn(0);
	m_QualityMaterialList.DeleteColumn(1);
	m_QualityMaterialList.DeleteColumn(2);
	m_QualityMaterialList.DeleteColumn(3);


	// 为WBC列表视图控件添加四列   
	m_QualityMaterialList.InsertColumn(0, _T("材料"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_QualityMaterialList.InsertColumn(1, _T("级别（批号）"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_QualityMaterialList.InsertColumn(2, _T("批号"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_QualityMaterialList.InsertColumn(3, _T("失效期"), LVCFMT_CENTER, rect.Width() /4, 3);

	// 在WBC列表视图控件中插入列表项，并设置列表子项文本   

	m_QualityMaterialList.InsertItem(0, _T("LYM%"));
	m_QualityMaterialList.SetItemText(0, 0, _T("质控图"));
	m_QualityMaterialList.SetItemText(0, 1, _T("级别2（当前）"));
	m_QualityMaterialList.SetItemText(0, 2, _T("QC-30340802"));
	m_QualityMaterialList.SetItemText(0, 3, _T("2016/07/20"));

	//AfxMessageBox(_T("1213"));
	return TRUE;
}

HBRUSH CQualityRadarView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC0:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CQualityRadarView::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}
