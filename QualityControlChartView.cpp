// QualityControlChartView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityControlChartView.h"
#include "afxdialogex.h"


// CQualityControlChartView 对话框


IMPLEMENT_DYNAMIC(CQualityControlChartView, CDialogEx)

CQualityControlChartView::CQualityControlChartView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQualityControlChartView::IDD, pParent)
{
	curpage = 0;
	QcLjFileExistEdit = 0;
	qcLjGraphNum = 0;
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

	for (int i = 0; i < 26; i++)
	{
		upperlimit[i] = 0;
		lowerlimit[i] = 0;
	}

	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 31; j++)
			data[i][j] = 0.0;
}

CQualityControlChartView::~CQualityControlChartView()
{

}

void CQualityControlChartView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QUALITY_LINECHART, m_QualityLineChart);
	DDX_Control(pDX, IDC_QUALITY_LINECHART2, m_QualityLineChart2);
	DDX_Control(pDX, IDC_QUALITY_LINECHART3, m_QualityLineChart3);
	DDX_Control(pDX, IDC_QUALITY_LINECHART4, m_QualityLineChart4);
	DDX_Control(pDX, IDC_QUALITY_MATERIALLIST, m_materialInfolist);
}


BEGIN_MESSAGE_MAP(CQualityControlChartView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_GRAPH_UP, &CQualityControlChartView::OnGraphUp)
	ON_BN_CLICKED(IDC_GRAPH_DOWN, &CQualityControlChartView::OnGraphDown)
END_MESSAGE_MAP()


// CQualityControlChartView 消息处理程序


void CQualityControlChartView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


BOOL CQualityControlChartView::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CString item_temp;
	int nRow, mRow;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J质控图（文件 %02u）", Controlfile+1);
		break;
	case 1:
		item_temp.Format(L"X质控图（文件 %02u）", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R质控图（文件 %02u）", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_STATIC0,item_temp);
	GetDlgItem(IDC_STATIC0)->SetFont(&textfont);
	nRow = GetNumDea(Controltype, Controlfile);
	if (nRow == 0)
		QcLjFileExistEdit = 0;
	else
		QcLjFileExistEdit = 1;
	if (1 == QcLjFileExistEdit)
	{
		mRow = GetDetail(Controltype, Controlfile);
		qcLjGraphNum = mRow;
		if (mRow > 31)
			qcLjGraphNum = 31;
	}
	else
		qcLjGraphNum = 0;

	InitLineChart();
	InitLineChart2();
	InitLineChart3();
	InitLineChart4();
	InitmaterialInfoList();
	UpdateMSC();
	GetDlgItem(IDC_GRAPH_UP)->EnableWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CQualityControlChartView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CQualityControlChartView::InitLineChart()
{
	 pChart = m_QualityLineChart.GetChart();
	ASSERT_VALID(pChart);

	/*BCGPChartType type =
		(m_Feature == CDemoFeature::BCGP_StackedLine || m_Feature == CDemoFeature::BCGP_StackedLineSpline) ? BCGP_CT_STACKED :
		(m_Feature == CDemoFeature::BCGP_StackedLine100) ?
	BCGP_CT_100STACKED : BCGP_CT_SIMPLE;*/
	BCGPChartType type = BCGP_CT_STACKED;
	//BCGPChartType type = BCGP_CT_100STACKED;

	pChart->SetChartType(BCGPChartLine, type);

	//pChart->SetChartTitle(_T("Furniture Sales"));
	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("质控值"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("靶值上限"));
	CBCGPChartSeries* pSeries3 = pChart->CreateSeries(_T("靶值下限"));

	//CString m_arYears[5] = { "2010", "2011", "2012", "2013", "2014" };
	//pSeries1->AddDataPoint(m_arYears[4], 5.);
	//pSeries1->AddDataPoint(m_arYears[3], 8.);
	//pSeries1->AddDataPoint(m_arYears[2], 12.);
	//pSeries1->AddDataPoint(m_arYears[1], 13.);
	//pSeries1->AddDataPoint(m_arYears[0], 15.);

	//pSeries2->AddDataPoint(9.);
	//pSeries2->AddDataPoint(15.);
	//pSeries2->AddDataPoint(19.);
	//pSeries2->AddDataPoint(21.);
	//pSeries2->AddDataPoint(23.);

	CArray <double, double> m_upperarray, m_lowerarray,m_dataarray;
	m_upperarray.SetSize(31);
	m_lowerarray.SetSize(31);
	m_dataarray.SetSize(31);
	for (int i = 0; i < 31; i++)
	{
		m_upperarray.SetAtGrow(i, upperlimit[curpage*4]);
		m_lowerarray.SetAtGrow(i, lowerlimit[curpage * 4]);
		m_dataarray.SetAtGrow(i,data[curpage*4][i]);
	}
	//pSeries2->AddDataPoint(upperlimit[0]);
	pSeries1->AddDataPoints(m_dataarray);
	pSeries2->AddDataPoints(m_upperarray);
	pSeries3->AddDataPoints(m_lowerarray);
	

	CBCGPChartAxis* pYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	//if (m_QualityLineChart.GetGraphicsManager()->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI)
	//{
	//	m_wndDisplayShadow.EnableWindow(FALSE);
	//	m_wndDisplayShadow.ShowWindow(SW_HIDE);
	//	m_bDisplayShadow = FALSE;
	//}
	OnUpdateChart(1);
}


void CQualityControlChartView::InitLineChart2()
{
	pChart2 = m_QualityLineChart2.GetChart();
	ASSERT_VALID(pChart2);

	/*BCGPChartType type =
	(m_Feature == CDemoFeature::BCGP_StackedLine || m_Feature == CDemoFeature::BCGP_StackedLineSpline) ? BCGP_CT_STACKED :
	(m_Feature == CDemoFeature::BCGP_StackedLine100) ?
	BCGP_CT_100STACKED : BCGP_CT_SIMPLE;*/
	BCGPChartType type = BCGP_CT_STACKED;
	//BCGPChartType type = BCGP_CT_100STACKED;

	pChart2->SetChartType(BCGPChartLine, type);

	//pChart->SetChartTitle(_T("Furniture Sales"));
	CBCGPChartSeries* pSeries1 = pChart2->CreateSeries(_T("质控值"));
	CBCGPChartSeries* pSeries2 = pChart2->CreateSeries(_T("靶值上限"));
	CBCGPChartSeries* pSeries3 = pChart2->CreateSeries(_T("靶值下限"));

	//CString m_arYears[5] = { "2010", "2011", "2012", "2013", "2014" };
	//pSeries1->AddDataPoint(m_arYears[4], 5.);
	//pSeries1->AddDataPoint(m_arYears[3], 8.);
	//pSeries1->AddDataPoint(m_arYears[2], 12.);
	//pSeries1->AddDataPoint(m_arYears[1], 13.);
	//pSeries1->AddDataPoint(m_arYears[0], 15.);

	CArray <double, double> m_upperarray, m_lowerarray,m_dataarray;
	m_upperarray.SetSize(31);
	m_lowerarray.SetSize(31);
	m_dataarray.SetSize(31);
	for (int i = 0; i < 31; i++)
	{
		m_upperarray.SetAtGrow(i, upperlimit[curpage * 4+1]);
		m_lowerarray.SetAtGrow(i, lowerlimit[curpage * 4+1]);
		m_dataarray.SetAtGrow(i, data[curpage * 4+1][i]);
	}
	//pSeries2->AddDataPoint(upperlimit[0]);
	pSeries1->AddDataPoints(m_dataarray);
	pSeries2->AddDataPoints(m_upperarray);
	pSeries3->AddDataPoints(m_lowerarray);

	CBCGPChartAxis* pYAxis = pChart2->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	ASSERT_VALID(pYAxis);

	pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	CBCGPChartAxis* pXAxis = pChart2->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	ASSERT_VALID(pXAxis);

	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
	pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

	//if (m_QualityLineChart.GetGraphicsManager()->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI)
	//{
	//	m_wndDisplayShadow.EnableWindow(FALSE);
	//	m_wndDisplayShadow.ShowWindow(SW_HIDE);
	//	m_bDisplayShadow = FALSE;
	//}
	OnUpdateChart(2);
}

void CQualityControlChartView::InitLineChart3()
{
	pChart3 = m_QualityLineChart3.GetChart();
	ASSERT_VALID(pChart3);

	BCGPChartType type = BCGP_CT_STACKED;

	pChart3->SetChartType(BCGPChartLine, type);

	//pChart->SetChartTitle(_T("Furniture Sales"));
	if (curpage < 6)
	{
		CBCGPChartSeries* pSeries1 = pChart3->CreateSeries(_T("质控值"));
		CBCGPChartSeries* pSeries2 = pChart3->CreateSeries(_T("靶值上限"));
		CBCGPChartSeries* pSeries3 = pChart3->CreateSeries(_T("靶值下限"));

		//CString m_arYears[5] = { "2010", "2011", "2012", "2013", "2014" };
		//pSeries1->AddDataPoint(m_arYears[4], 5.);
		//pSeries1->AddDataPoint(m_arYears[3], 8.);
		//pSeries1->AddDataPoint(m_arYears[2], 12.);
		//pSeries1->AddDataPoint(m_arYears[1], 13.);
		//pSeries1->AddDataPoint(m_arYears[0], 15.);

		CArray <double, double> m_upperarray, m_lowerarray,m_dataarray;
		m_upperarray.SetSize(31);
		m_lowerarray.SetSize(31);
		m_dataarray.SetSize(31);
		for (int i = 0; i < 31; i++)
		{
			m_upperarray.SetAtGrow(i, upperlimit[curpage * 4 + 2]);
			m_lowerarray.SetAtGrow(i, lowerlimit[curpage * 4 + 2]);
			m_dataarray.SetAtGrow(i, data[curpage * 4 + 2][i]);
		}
		//pSeries2->AddDataPoint(upperlimit[0]);
		pSeries1->AddDataPoints(m_dataarray);
		pSeries2->AddDataPoints(m_upperarray);
		pSeries3->AddDataPoints(m_lowerarray);

		CBCGPChartAxis* pYAxis = pChart3->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
		ASSERT_VALID(pYAxis);

		pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

		CBCGPChartAxis* pXAxis = pChart3->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
		ASSERT_VALID(pXAxis);

		pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

		OnUpdateChart(3);
	}
	else if (curpage == 6)
	{

		return;
	}
	//if (m_QualityLineChart.GetGraphicsManager()->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI)
	//{
	//	m_wndDisplayShadow.EnableWindow(FALSE);
	//	m_wndDisplayShadow.ShowWindow(SW_HIDE);
	//	m_bDisplayShadow = FALSE;
	//}
}

void CQualityControlChartView::InitLineChart4()
{
	pChart4 = m_QualityLineChart4.GetChart();
	ASSERT_VALID(pChart4);

	/*BCGPChartType type =
	(m_Feature == CDemoFeature::BCGP_StackedLine || m_Feature == CDemoFeature::BCGP_StackedLineSpline) ? BCGP_CT_STACKED :
	(m_Feature == CDemoFeature::BCGP_StackedLine100) ?
	BCGP_CT_100STACKED : BCGP_CT_SIMPLE;*/
	BCGPChartType type = BCGP_CT_STACKED;
	//BCGPChartType type = BCGP_CT_100STACKED;

	pChart4->SetChartType(BCGPChartLine, type);

	if (curpage < 6)
	{
		//pChart->SetChartTitle(_T("Furniture Sales"));
		CBCGPChartSeries* pSeries1 = pChart4->CreateSeries(_T("质控值"));
		CBCGPChartSeries* pSeries2 = pChart4->CreateSeries(_T("靶值上限"));
		CBCGPChartSeries* pSeries3 = pChart4->CreateSeries(_T("靶值下限"));


		CArray <double, double> m_upperarray, m_lowerarray,m_dataarray;
		m_upperarray.SetSize(31);
		m_lowerarray.SetSize(31);
		m_dataarray.SetSize(31);
		for (int i = 0; i < 31; i++)
		{
			m_upperarray.SetAtGrow(i, upperlimit[curpage * 4 + 3]);
			m_lowerarray.SetAtGrow(i, lowerlimit[curpage * 4 + 3]);
			m_dataarray.SetAtGrow(i, data[curpage * 4 + 3][i]);
		}
		//pSeries2->AddDataPoint(upperlimit[0]);
		pSeries1->AddDataPoints(m_dataarray);
		pSeries2->AddDataPoints(m_upperarray);
		pSeries3->AddDataPoints(m_lowerarray);


		CBCGPChartAxis* pYAxis = pChart4->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
		ASSERT_VALID(pYAxis);

		pYAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		pYAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;

		CBCGPChartAxis* pXAxis = pChart4->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
		ASSERT_VALID(pXAxis);

		pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		pXAxis->m_minorTickMarkType = CBCGPChartAxis::TMT_CROSS;
		//if (m_QualityLineChart.GetGraphicsManager()->GetType() == CBCGPGraphicsManager::BCGP_GRAPHICS_MANAGER_GDI)
		//{
		//	m_wndDisplayShadow.EnableWindow(FALSE);
		//	m_wndDisplayShadow.ShowWindow(SW_HIDE);
		//	m_bDisplayShadow = FALSE;
		//}
		OnUpdateChart(4);
	}
	else if (curpage == 6)
	{
		return;
	}
}


void CQualityControlChartView::OnUpdateChart(int num)
{
	UpdateData();
	//m_wndMarkerShape.EnableWindow(m_bShowDataMarkers);
	//m_wndMarkerSize.EnableWindow(m_bShowDataMarkers);
	//m_wndDataLabelAngle.EnableWindow(m_bShowDataLabels);
	CBCGPChartVisualObject* pChart;
	switch (num)
	{
	case 1:
		pChart = m_QualityLineChart.GetChart();
		break;
	case 2:
		pChart = m_QualityLineChart2.GetChart();
		break;
	case 3:
		pChart = m_QualityLineChart3.GetChart();
		break;
	case 4:
		pChart = m_QualityLineChart4.GetChart();
		break;
	default:
		break;
	}
	ASSERT_VALID(pChart);
	pChart->ShowDataMarkers(TRUE,max(7, 5 * (0 + 1)),
		(BCGPChartMarkerOptions::MarkerShape)0);

	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	//double dblDataLabelAngle = (m_nDataLabelAngle - 2) * 45;

	//pChart->ShowDataLabels(m_bShowDataLabels, TRUE, TRUE, dblDataLabelAngle);

	for (int i = 0; i < pChart->GetSeriesCount(); i++)
	{
		CBCGPChartSeries* pSeries = pChart->GetSeries(i);
		ASSERT_VALID(pSeries);

		BCGPChartFormatSeries style = pSeries->GetSeriesFormat();

	/*	style.m_curveType = (m_Feature == CDemoFeature::BCGP_StackedLineSpline) ?
			BCGPChartFormatSeries::CCT_SPLINE :
			(m_Feature == CDemoFeature::BCGP_StepLine) ?
			BCGPChartFormatSeries::CCT_STEP :
			BCGPChartFormatSeries::CCT_LINE;*/
		style.m_curveType = BCGPChartFormatSeries::CCT_SPLINE;

		style.SetSeriesOutlineDashStyle((CBCGPStrokeStyle::BCGP_DASH_STYLE)0);
		style.SetSeriesLineWidth(0 + 1);

		style.m_shadowType.m_bDisplayShadow = 1;

		pSeries->SetSeriesFormat(style);
	}
	pChart->Redraw();
}



void CQualityControlChartView::UpdateLineChart()
{

}

void CQualityControlChartView::UpdateLineChart2()
{

}

void CQualityControlChartView::UpdateLineChart3()
{

}

void CQualityControlChartView::UpdateLineChart4()
{

}


bool CQualityControlChartView::InitmaterialInfoList()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_materialInfolist.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_materialInfolist.SetExtendedStyle(m_materialInfolist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_materialInfolist.SetRowHeigt(20);

	m_materialInfolist.DeleteAllItems();//清空列表刷新

	m_materialInfolist.DeleteColumn(0);
	m_materialInfolist.DeleteColumn(1);
	m_materialInfolist.DeleteColumn(2);
	m_materialInfolist.DeleteColumn(3);
	// 为WBC列表视图控件添加四列   
	m_materialInfolist.InsertColumn(0, _T("材料"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_materialInfolist.InsertColumn(1, _T("级别（批号）"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_materialInfolist.InsertColumn(2, _T("批号"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_materialInfolist.InsertColumn(3, _T("失效期"), LVCFMT_CENTER, rect.Width() / 4, 3);
	// 在WBC列表视图控件中插入列表项，并设置列表子项文本   

	m_materialInfolist.InsertItem(0, _T("LYM%"));
	m_materialInfolist.SetItemText(0, 0, _T("质控图"));
	m_materialInfolist.SetItemText(0, 1, _T("级别2（当前）"));
	m_materialInfolist.SetItemText(0, 2, _T("QC-30340802"));
	m_materialInfolist.SetItemText(0, 3, _T("2016/07/20"));
	//AfxMessageBox(_T("1213"));
	return TRUE;
}

void CQualityControlChartView::OnGraphUp()
{
	// TODO:  在此添加控件通知处理程序代码
	CString pageInfo;
	CString table_temp[] = { "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO%", "ALY%", "LIC%",
							"LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#", "LIC#", "RBC", "HGB",
							"HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	memcpy(quality_table, table_temp, sizeof(table_temp));

	if (curpage > 0)
	{
		curpage--;
	}
	if (curpage==0)
	{
		GetDlgItem(IDC_GRAPH_UP)->EnableWindow(false);
	}
	if (curpage!=6)
		GetDlgItem(IDC_GRAPH_DOWN)->EnableWindow(true);
	pageInfo.Format(L"000%d/0007", curpage + 1);
	GetDlgItem(IDC_STATIC1)->SetWindowText(quality_table[curpage * 4]);
	GetDlgItem(IDC_STATIC2)->SetWindowText(quality_table[curpage * 4 + 1]);
	GetDlgItem(IDC_STATIC3)->SetWindowText(quality_table[curpage * 4 + 2]);
	GetDlgItem(IDC_STATIC4)->SetWindowText(quality_table[curpage * 4 + 3]);
	GetDlgItem(IDC_STATIC5)->SetWindowText(pageInfo);

	InitLineChart();
	InitLineChart2();
	InitLineChart3();
	InitLineChart4();

}

void CQualityControlChartView::OnGraphDown()
{
	// TODO:  在此添加控件通知处理程序代码
	CString pageInfo;
	CString table_temp[] = { "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO%", "ALY%", "LIC%",
							"LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#", "LIC#", "RBC", "HGB",
							"HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	memcpy(quality_table, table_temp, sizeof(table_temp));
	if (curpage<6)
		curpage++;
	if (curpage==6)
	{
		GetDlgItem(IDC_GRAPH_DOWN)->EnableWindow(false);
	}
	if (curpage != 0)
		GetDlgItem(IDC_GRAPH_UP)->EnableWindow(true);
	pageInfo.Format(L"000%d/0007",curpage+1);
	GetDlgItem(IDC_STATIC1)->SetWindowText(quality_table[curpage * 4]);
	GetDlgItem(IDC_STATIC2)->SetWindowText(quality_table[curpage * 4 + 1]);
	GetDlgItem(IDC_STATIC3)->SetWindowText(quality_table[curpage * 4 + 2]);
	GetDlgItem(IDC_STATIC4)->SetWindowText(quality_table[curpage * 4 + 3]);
	GetDlgItem(IDC_STATIC5)->SetWindowText(pageInfo);

	InitLineChart();
	InitLineChart2();
	InitLineChart3();
	InitLineChart4();
}

void CQualityControlChartView::UpdateLUlimit()
{
		



}

void CQualityControlChartView::UpdateMSC()
{
	int ColCount = 4;
	float sum=0;
	float square = 0;
	float Y = 0;
	float Meantemp[4] = {0.0};
	float SDtemp[4] = {0.0};
	float CVtemp[4] = {0.0};
	CString Mean[4];
	CString SD[4];
	CString CV[4];

	for (int i = 0; i < ColCount; i++)
	{
		sum = 0;
		for (int j = 0; j < qcLjGraphNum; i++)
		{
			Y = data[i + curpage * 4][j];
			sum += Y;
		}
		Meantemp[i] = sum / qcLjGraphNum;

		if (qcLjGraphNum > 1)
		{
			sum = 0;
			square = 0;
			for (int j = 0; j < qcLjGraphNum; j++)
			{
				Y = data[i + curpage* 4][j];
				square += (Y - Meantemp[i])*(Y - Meantemp[i]);
			}
			SDtemp[i] = sqrt(square / (qcLjGraphNum - 1));

			if (Meantemp[i] < 0.00001)//保证除法的除数不为0
				CVtemp[i]=0.00;
			else
			{
				CVtemp[i] = SDtemp[i] / Meantemp[i] * 100;
			}
		}

	}
	for (int i = 0; i < 4; i++)
	{
		Mean[i].Format(L"%.2f",Meantemp[i]);
		SD[i].Format(L"%.2f", SDtemp[i]);
		CV[i].Format(L"%.2f", CVtemp[i]);
	}

	SetDlgItemText(IDC_MEAN1, Mean[0]);
	SetDlgItemText(IDC_MEAN2, Mean[1]);
	SetDlgItemText(IDC_MEAN3, Mean[2]);
	SetDlgItemText(IDC_MEAN4, Mean[3]);

	SetDlgItemText(IDC_SD1, SD[0]);
	SetDlgItemText(IDC_SD2, SD[1]);
	SetDlgItemText(IDC_SD3, SD[2]);
	SetDlgItemText(IDC_SD4, SD[3]);

	SetDlgItemText(IDC_CV1, CV[0]);
	SetDlgItemText(IDC_CV2, CV[1]);
	SetDlgItemText(IDC_CV3, CV[2]);
	SetDlgItemText(IDC_CV4, CV[3]);

}

int CQualityControlChartView::GetNumDea(int controltype, int controlfile)
{
	CString getNumdea;
	CString filename;
	int rownum=0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;

	getNumdea.Format(L"select * from qceditdata where qctype = %d and filenum = %d;",controltype,controlfile);
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, getNumdea);
	rownum = int(m_pRs->GetRecordCount());
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空\n");
			return -1;
		}
		while ((!m_pRs->adoEOF))
		{
			for (int i = 0; i < 26; i++)
			{
				var = m_pRs->GetFields()->GetItem(4+i)->Value;
				if (var.vt != VT_NULL){
					lowerlimit[i] = var;
				}
				var = m_pRs->GetFields()->GetItem(4+26+i)->Value;
				if (var.vt != VT_NULL){
					upperlimit[i] = var;
				}
			}
		}
	}
	catch (_com_error &e)
	{
		TRACE("GetNumDea函数程序异常\n");
	}
	CloseDataBase(m_pDB, m_pRs);
	return rownum;
}

int CQualityControlChartView::GetDetail(int controltype, int controlfile)
{
	CString select_detail;
	CString filename;
	int rownum = 0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;

	select_detail.Format(L"select * from qcresultdata where qctype = %d and filenum = %d;", controltype, controlfile);
	
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, select_detail);
	int k = 0;
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空\n");
			return -1;
		}
		while ((!m_pRs->adoEOF))
		{
			for (int i = 0; i < 26; i++)
			{
				var = m_pRs->GetFields()->GetItem(1 + i)->Value;
				if (var.vt != VT_NULL){
					data[i][k] = var;
				}
			}
			k++;
		}
	}
	catch (_com_error &e)
	{
		TRACE("GetNumDea函数程序异常\n");
	}
	rownum = int(m_pRs->GetRecordCount());
	CloseDataBase(m_pDB, m_pRs);
	return rownum;
}