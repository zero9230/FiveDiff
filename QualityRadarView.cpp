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

	GetLatestResult(Controltype, Controlfile);
	GetQcEditInfo(Controltype, Controlfile);

	OnInitRadarChart1();
	OnInitRadarChart2();
	OnInitRadarChart3();
	OnInitRadarChart4();
	//OnInitRadarChart5();
	OnInitQualityMaterialList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CQualityRadarView::OnInitRadarChart1()
{
	CBCGPChartVisualObject* pChart = m_RadarChart1.GetChart();
	ASSERT_VALID(pChart);

	pChart->CleanUpChartData();

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));

	pSeries1->RemoveAllDataPoints();

	pSeries1->AddDataPoint("WBC", data[0]);
	pSeries1->AddDataPoint("LYM%", data[1]);
	pSeries1->AddDataPoint("NEU%", data[2]);
	pSeries1->AddDataPoint("MONO%", data[3]);
	pSeries1->AddDataPoint("EOS%", data[4]);
	pSeries1->AddDataPoint("BASO%", data[5]);
	pSeries1->AddDataPoint("ALY%%", data[6]);
	pSeries1->AddDataPoint("LIC%", data[7]);

	//pSeries1->AddDataPoint("WBC", 15.);
	//pSeries1->AddDataPoint("LYM%", 10.);
	//pSeries1->AddDataPoint("NEU%", 8.);
	//pSeries1->AddDataPoint("MONO%", 22.);
	//pSeries1->AddDataPoint("EOS%", 22.);
	//pSeries1->AddDataPoint("BASO%",18.);

	//pSeries2->AddDataPoint(9.);
	//pSeries2->AddDataPoint(15.);
	//pSeries2->AddDataPoint(19.);
	//pSeries2->AddDataPoint(21.);
	//pSeries2->AddDataPoint(23.);

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
	pChart->CleanUpChartData();

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));

	pSeries1->RemoveAllDataPoints();

	pSeries1->AddDataPoint("LYM", data[8]);
	pSeries1->AddDataPoint("NEU", data[9]);
	pSeries1->AddDataPoint("MONO", data[10]);
	pSeries1->AddDataPoint("EOS", data[11]);
	pSeries1->AddDataPoint("BASO", data[12]);	
	pSeries1->AddDataPoint("ALY", data[13]);
	pSeries1->AddDataPoint("LIC", data[14]);
	
	//pSeries1->AddDataPoint("PLT", 15.);
	//pSeries1->AddDataPoint("MPV", 10.);
	//pSeries1->AddDataPoint("PDW", 8.);
	//pSeries1->AddDataPoint("PCT", 22.);
	//pSeries1->AddDataPoint("P-LCR", 22.);

	//pSeries2->AddDataPoint(9.);
	//pSeries2->AddDataPoint(15.);
	//pSeries2->AddDataPoint(19.);
	//pSeries2->AddDataPoint(21.);
	//pSeries2->AddDataPoint(23.);


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
	pChart->CleanUpChartData();

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));

	pSeries1->RemoveAllDataPoints();

	pSeries1->AddDataPoint("RBC", data[15]);
	pSeries1->AddDataPoint("HGB", data[16]);
	pSeries1->AddDataPoint("HCT", data[17]);
	pSeries1->AddDataPoint("MCV", data[18]);
	pSeries1->AddDataPoint("MCH", data[19]);
	pSeries1->AddDataPoint("MCHC", data[20]);
	pSeries1->AddDataPoint("RDW", data[21]);

	//pSeries1->AddDataPoint("RBC", 15.);
	//pSeries1->AddDataPoint("HGB", 10.);
	//pSeries1->AddDataPoint("HCT", 8.);
	//pSeries1->AddDataPoint("MCV", 22.);
	//pSeries1->AddDataPoint("MCH", 22.);

	//pSeries2->AddDataPoint(9.);
	//pSeries2->AddDataPoint(15.);
	//pSeries2->AddDataPoint(19.);
	//pSeries2->AddDataPoint(21.);
	//pSeries2->AddDataPoint(23.);


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
	pChart->CleanUpChartData();

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));

	pSeries1->RemoveAllDataPoints();

	pSeries1->AddDataPoint("PLT", data[22]);
	pSeries1->AddDataPoint("MPV", data[23]);
	pSeries1->AddDataPoint("PDW", data[24]);
	pSeries1->AddDataPoint("PCT", data[25]);

	//pSeries1->AddDataPoint("MCHC", 15.);
	//pSeries1->AddDataPoint("RDW-CV", 10.);
	//pSeries1->AddDataPoint("RDW-SD", 8.);
	//pSeries1->AddDataPoint("ALY%", 22.);
	//pSeries1->AddDataPoint("LIC%", 22.);
	//pSeries1->AddDataPoint("LIC#", 22.);

	//pSeries2->AddDataPoint(9.);
	//pSeries2->AddDataPoint(15.);
	//pSeries2->AddDataPoint(19.);
	//pSeries2->AddDataPoint(21.);
	//pSeries2->AddDataPoint(23.);


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
	pChart->CleanUpChartData();

	pChart->SetChartType(BCGPChartPolar);

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	CBCGPChartSeries* pSeries2 = pChart->CreateSeries(_T("Series 2"));
	
	pSeries1->RemoveAllDataPoints();

	//pSeries1->AddDataPoint("LYM#", 15.);
	//pSeries1->AddDataPoint("NEU#", 10.);
	//pSeries1->AddDataPoint("MONO#", 8.);
	//pSeries1->AddDataPoint("EOS#", 22.);
	//pSeries1->AddDataPoint("BASO#", 22.);
	//pSeries1->AddDataPoint("ALY#", 22.);

	//pSeries2->AddDataPoint(9.);
	//pSeries2->AddDataPoint(15.);
	//pSeries2->AddDataPoint(19.);
	//pSeries2->AddDataPoint(21.);
	//pSeries2->AddDataPoint(23.);


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
	m_QualityMaterialList.SetItemText(0, 2, (number));
	m_QualityMaterialList.SetItemText(0, 3, (deadline));

	//AfxMessageBox(_T("1213"));
	return TRUE;
}

BOOL  CQualityRadarView::OnUpdateQualityMaterialList(){
	m_QualityMaterialList.DeleteAllItems();

	m_QualityMaterialList.InsertItem(0, _T("LYM%"));
	m_QualityMaterialList.SetItemText(0, 0, _T("质控图"));
	m_QualityMaterialList.SetItemText(0, 1, _T("级别2（当前）"));
	m_QualityMaterialList.SetItemText(0, 2, (number));
	m_QualityMaterialList.SetItemText(0, 3, (deadline));

	return true;

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

void CQualityRadarView::UpdateView()
{
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

	GetLatestResult(Controltype, Controlfile);
	GetQcEditInfo(Controltype, Controlfile);

	OnInitRadarChart1();
	OnInitRadarChart2();
	OnInitRadarChart3();
	OnInitRadarChart4();
	//OnInitRadarChart5();
	OnUpdateQualityMaterialList();
}

//查询质控测试结果，获得最近一条质控测试结果，用于雷达图显示
int CQualityRadarView::GetLatestResult(int controltype, int controlfile)
{
	CString select_latest_result;
	CString filename;
	int rownum = 0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	CString strTemp;
	int k = 0;

	for (int i = 0; i < 26; i++){//将数据容器data初始清空
		data[i] = 0;
	}

	select_latest_result.Format(L"select * from qcresultdata where qctype = '%d' and filenum = '%d' order by [date] desc,[time] desc;", controltype, controlfile);

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, select_latest_result);
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
		while ((!m_pRs->adoEOF))//只查询最近一条
		{

			for (int i = 0; i < 26; i++)
			{
				var = m_pRs->GetFields()->GetItem((long)2 + i)->Value;
				if (var.vt != VT_NULL){
					strTemp = (LPCSTR)_bstr_t(var);
					data[i] = _wtof(strTemp);
				}
			}
			k++;
			m_pRs->MoveNext();
			break;
		}
	}
	catch (_com_error &e)
	{
		TRACE("GetLatestResult函数程序异常\n");
	}
	CloseDataBase(m_pDB, m_pRs);
	return rownum;
}

//查询质控编辑文件，获得质控批号和截止日期
int CQualityRadarView::GetQcEditInfo(int controltype, int controlfile){
	CString select_qc_edit_info;
	CString filename;
	int rownum = 0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	CString strTemp;

	select_qc_edit_info.Format(L"select * from qceditdata where qctype = '%d' and filenum = '%d';", controltype, controlfile);

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, select_qc_edit_info);
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
			if (var.vt != VT_NULL)
			{
				strTemp = m_pRs->GetCollect("number");
				_tcscpy(number.GetBuffer(strTemp.GetLength() + 1), strTemp);
				
				//填入批号
			}
			var = m_pRs->GetCollect("deadline");
			if (var.vt != VT_NULL)
			{
				strTemp = m_pRs->GetCollect("deadline");
				_tcscpy(deadline.GetBuffer(strTemp.GetLength() + 1), strTemp);
				//填入截止日期
			}
			m_pRs->MoveNext();
			break;
		}
	}
	catch (_com_error &e)
	{
		TRACE("GetQcEditInfo函数程序异常\n");
	}
	CloseDataBase(m_pDB, m_pRs);
	return 0;

}