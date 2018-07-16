// QualityControlView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityControlView.h"
#include "ControlChooese.h"
#include <string>
#include <vector>
#include "Includes_app.h"
// CQualityControlView
//CQualityTestView	m_QualityTestPage;

IMPLEMENT_DYNCREATE(CQualityControlView, CBCGPChartExampleView)

CQualityControlChartView	m_QualityChartPage;
CQualityListView			m_QualityListPage;

CQcXChartView				m_QcXChartPage;
CQcXListView				m_QcXListPage;

CQcXrChartView			m_QcXrChartPage;
CQcXrListView				m_QcXrListPage;

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
	ON_BN_CLICKED(IDC_QUALITY_FILEINFO, &CQualityControlView::OnBnClickedQualityFileinfo)
	
	ON_BN_CLICKED(IDC_QUALITY_LOAD, &CQualityControlView::OnBnClickedQualityLoad)
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

	GetDlgItem(IDC_QUALITY_SAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_QUALITY_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_QUALITY_RECOVER)->EnableWindow(FALSE);


	CRect rectTab;
	GetDlgItem(IDC_QUALITYCONTROL_TAB)->GetWindowRect(&rectTab);
	ScreenToClient(&rectTab);

	m_QualityTab.Create(CBCGPTabWnd::STYLE_3D, rectTab, this, 1, CBCGPTabWnd::LOCATION_TOP);
	CRect rc;
	m_QualityTab.GetClientRect(rc);
	m_QualityTab.SetResizeMode(CBCGPTabWnd::RESIZE_VERT);
	rc.top += 27;
	rc.bottom -= 5;
	rc.left += 5;
	rc.right -= 10;

	if (0 == Controltype){			//LJ质控
		m_QualityTab.RemoveAllTabs();

		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QualityChartPage.Create(IDD_QUALITY_CONTROL_CHART, &m_QualityTab);
		m_QualityTargetPage.Create(IDD_QUALITY_TARGETVALUE, &m_QualityTab);
		m_QualityTestPage.Create(IDD_QUALITY_TESTVIEW, &m_QualityTab);
		m_QualityListPage.Create(IDD_QUALITY_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"雷达图", 0);
		m_QualityTab.AddTab(&m_QualityChartPage, L"质控图", 1);
		m_QualityTab.AddTab(&m_QualityTargetPage, L"靶值", 2);
		m_QualityTab.AddTab(&m_QualityTestPage, L"质控计数", 3);
		m_QualityTab.AddTab(&m_QualityListPage, L"质控列表", 4);

	}
	else if (1 == Controltype){		//X质控
		m_QualityTab.RemoveAllTabs();

		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QcXChartPage.Create(IDD_QC_X_CHART, &m_QualityTab);
		m_QcXTargetPage.Create(IDD_QC_X_TARGETVALUE, &m_QualityTab);
		m_QcXTestPage.Create(IDD_QC_X_TESTVIEW, &m_QualityTab);
		m_QcXListPage.Create(IDD_QC_X_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"雷达图", 0);
		m_QualityTab.AddTab(&m_QcXChartPage, L"X质控图", 1);
		m_QualityTab.AddTab(&m_QcXTargetPage, L"X质控编辑", 2);
		m_QualityTab.AddTab(&m_QcXTestPage, L"X质控计数", 3);
		m_QualityTab.AddTab(&m_QcXListPage, L"X质控列表", 4);
		
	}
	else if (2 == Controltype){	//XR质控页面的切换

		m_QualityTab.RemoveAllTabs();
		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QcXrEditPage.Create(IDD_QC_XR_EDIT, &m_QualityTab);
		m_QcXrTestPage.Create(IDD_QC_XR_TEST, &m_QualityTab);
		m_QcXrChartPage.Create(IDD_QC_XR_CHART, &m_QualityTab);
		m_QcXrListPage.Create(IDD_QC_XR_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"雷达图", 0);
		m_QualityTab.AddTab(&m_QcXrChartPage, L"Xr质控图", 1);
		m_QualityTab.AddTab(&m_QcXrEditPage, L"Xr质控编辑", 2);
		m_QualityTab.AddTab(&m_QcXrTestPage, L"Xr质控测试", 3);
		m_QualityTab.AddTab(&m_QcXrListPage, L"Xr质控列表", 4);
	}

	//OnPaint();
	PostMessage(WM_PAINT, 0, 0);


	//m_RadarPage.MoveWindow(&rc);
	//m_QualityChartPage.MoveWindow(&rc);
	//m_QualityTargetPage.MoveWindow(&rc);
	//m_QualityTestPage.MoveWindow(&rc);
	//m_QualityListPage.MoveWindow(&rc);
	//m_QcXTargetPage.MoveWindow(&rc);
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
	//MessageBox(L"open here!");
	m_ControlChoose.DoModal();

	return CBCGPChartExampleView::PreCreateWindow(cs);
}


void CQualityControlView::OnBnClickedQualityFileinfo()
{
	// TODO:  在此添加控件通知处理程序代码
	//在此处加入窗口更新的代码
	CControlChooese m_controlChoose;
	m_controlChoose.DoModal();
	//OnInitialUpdate();
	//RedrawWindow();
	//if (m_RadarPage)
	//	m_RadarPage.UpdateView();
	//m_QualityTargetPage.UpdateView();	
	//m_QualityChartPage.UpdateView();
	//m_QualityTestPage.UpdateView();	
	//UpdateData(false);
	///////////测试代码//////////
	CString str;
	str.Format(L"%d", Controltype);
	//MessageBox(str);
	if (0 == Controltype){			//LJ质控
		m_QualityTab.RemoveAllTabs();
		
		//MessageBox(L"22");
		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QualityChartPage.Create(IDD_QUALITY_CONTROL_CHART, &m_QualityTab);
		m_QualityTargetPage.Create(IDD_QUALITY_TARGETVALUE, &m_QualityTab);
		m_QualityTestPage.Create(IDD_QUALITY_TESTVIEW, &m_QualityTab);
		m_QualityListPage.Create(IDD_QUALITY_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"雷达图", 0);
		m_QualityTab.AddTab(&m_QualityChartPage, L"质控图", 1);
		m_QualityTab.AddTab(&m_QualityTargetPage, L"靶值", 2);
		m_QualityTab.AddTab(&m_QualityTestPage, L"质控计数", 3);
		m_QualityTab.AddTab(&m_QualityListPage, L"质控列表", 4);

		/**********************测试代码********************/
		//m_QualityListPage.CloseWindow();
		//m_QualityListPage.ShowWindow(SW_RESTORE);

		//m_QualityTab.InsertTab(&m_QualityTargetPage, L"LJ质控编辑", 2);
		//m_QualityTab.AddTab(&m_QcXTargetPage, L"X质控编辑", 0);
	}
	else if (1 == Controltype){		//X质控
		m_QualityTab.RemoveAllTabs();

		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QcXChartPage.Create(IDD_QC_X_CHART, &m_QualityTab);
		m_QcXTargetPage.Create(IDD_QC_X_TARGETVALUE, &m_QualityTab);
		m_QcXTestPage.Create(IDD_QC_X_TESTVIEW, &m_QualityTab);
		m_QcXListPage.Create(IDD_QC_X_LIST, &m_QualityTab);
		
		m_QualityTab.AddTab(&m_RadarPage, L"雷达图", 0);
		m_QualityTab.AddTab(&m_QcXChartPage, L"X质控图", 1);
		m_QualityTab.AddTab(&m_QcXTargetPage, L"X质控编辑", 2);
		m_QualityTab.AddTab(&m_QcXTestPage, L"X质控计数", 3);
		m_QualityTab.AddTab(&m_QcXListPage, L"X质控列表",4);
		//MessageBox(L"22");
		//m_QualityTargetPage.CloseWindow();
		//m_QualityTab.InsertTab(&m_QcXTargetPage, L"X质控编辑", 2);
		//m_QualityTab.AddTab(&m_QcXTargetPage, L"X质控编辑", 0);
	}
	else if (2 == Controltype){	//XR质控页面的切换
	
		m_QualityTab.RemoveAllTabs();
		m_RadarPage.Create(IDD_RADARCHART, &m_QualityTab);
		m_QcXrEditPage.Create(IDD_QC_XR_EDIT, &m_QualityTab);
		m_QcXrTestPage.Create(IDD_QC_XR_TEST, &m_QualityTab);
		m_QcXrChartPage.Create(IDD_QC_XR_CHART, &m_QualityTab);
		m_QcXrListPage.Create(IDD_QC_XR_LIST, &m_QualityTab);

		m_QualityTab.AddTab(&m_RadarPage, L"雷达图", 0);
		m_QualityTab.AddTab(&m_QcXrChartPage, L"Xr质控图",1);
		m_QualityTab.AddTab(&m_QcXrEditPage, L"Xr质控编辑", 2);
		m_QualityTab.AddTab(&m_QcXrTestPage, L"Xr质控测试", 3);
		m_QualityTab.AddTab(&m_QcXrListPage, L"Xr质控列表",4);
	}

	/////////////////////////////

	return;

}


void CQualityControlView::OnBnClickedQualityLoad()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strPath = "数据库(*.accdb)|*.accdb||";//过滤文件列表  
	CString path;
	CFileDialog file(true, NULL, NULL, OFN_HIDEREADONLY, strPath, NULL);//创建文件对象并打开  
	if (file.DoModal() == IDOK)//显示文件打开对话框  
	{
		// MessageBox(L"OK");
		path = file.GetPathName();//get database's name
		
		DatabaseLoad(path);
	}
}
void CQualityControlView::DatabaseLoad(CString filename)
{
	using namespace std;
	/*暂时存储两个表中的数据*/
	vector<qc_edit_data_info> qc_edit;
	vector<qcresult_info> qc_result;
	qc_result_data qc_result_cur;

	/*打开目标数据库，进行两个表格的数据备份*/
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	if (-1 == OpenDataBase(filename, m_pDB, m_pRs)){
		return;
	}

	CString select_qc_edit = "select * from qceditdata order by ID";
	CString select_qc_result="select * from qcresultdata order by ID";
	/*打开edit表格进行备份*/
	ExeSql(m_pDB, m_pRs, select_qc_edit);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();

		}
		else
		{
			TRACE("\n表内数据为空!\n");
			return ;
		}
		while ((!m_pRs->adoEOF))
		{
			qc_edit_data qc_edit_cur;
			var = m_pRs->GetCollect("qctype");
			if (var.vt != VT_NULL)
			{
				qc_edit_cur.qctype = m_pRs->GetCollect("qctype");
				qc_edit_cur.qctype +='0';
			}

			var = m_pRs->GetCollect("filenum");
			if (var.vt != VT_NULL)
			{
				qc_edit_cur.filenum = m_pRs->GetCollect("filenum");
				qc_edit_cur.filenum += '0';
			}

			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
			{
				CString cur_num = (LPCSTR)_bstr_t(var);
				int i;
				for ( i= 0; i < cur_num.GetLength(); i++)
					qc_edit_cur.Number[i] = cur_num[i];
				for (; i < 13; i++)
					qc_edit_cur.Number[i] = '\0';
			}
			
			var = m_pRs->GetCollect("deadline");
			if (var.vt != VT_NULL)
			{

				CString cur_dead = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < cur_dead.GetLength(); i++)
					qc_edit_cur.Deadline[i] = cur_dead[i];
				for (; i < 11; i++)
					qc_edit_cur.Deadline[i] = '\0';
			}

			var = m_pRs->GetCollect("WBC");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.wbc[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.wbc[i] = '\0';
			}

			var = m_pRs->GetCollect("LYMP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.lymp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.lymp[i] = '\0';
			}

			var = m_pRs->GetCollect("NEUP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.neup[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.neup[i] = '\0';
			}
			var = m_pRs->GetCollect("MONOP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.monop[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.monop[i] = '\0';
			}
			var = m_pRs->GetCollect("EOSP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.eosp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.eosp[i] = '\0';
			}
			var = m_pRs->GetCollect("BASOP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.basp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.basp[i] = '\0';
			}
			var = m_pRs->GetCollect("ALYP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.alyp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.alyp[i] = '\0';
			}
			var = m_pRs->GetCollect("LICP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.licp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.licp[i] = '\0';
			}
			var = m_pRs->GetCollect("LYM");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.lym[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.lym[i] = '\0';
			}
			var = m_pRs->GetCollect("NEU");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.neu[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.neu[i] = '\0';
			}
			var = m_pRs->GetCollect("MONO");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.mono[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.mono[i] = '\0';
			}
			var = m_pRs->GetCollect("EOS");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.eos[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.eos[i] = '\0';
			}
			var = m_pRs->GetCollect("BASO");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.bas[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.bas[i] = '\0';
			}
			var = m_pRs->GetCollect("ALY");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.aly[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.aly[i] = '\0';
			}
			var = m_pRs->GetCollect("LIC");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbctarget.lic[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbctarget.lic[i] = '\0';
			}
			var = m_pRs->GetCollect("RBC");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbctarget.rbc[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbctarget.rbc[i] = '\0';
			}
			var = m_pRs->GetCollect("HGB");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbctarget.hgb[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbctarget.hgb[i] = '\0';
			}
			var = m_pRs->GetCollect("HCT");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbctarget.hct[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbctarget.hct[i] = '\0';
			}
			var = m_pRs->GetCollect("MCV");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbctarget.mcv[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbctarget.mcv[i] = '\0';
			}
			var = m_pRs->GetCollect("MCH");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbctarget.mch[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbctarget.mch[i] = '\0';
			}
			var = m_pRs->GetCollect("MCHC");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbctarget.mchc[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbctarget.mchc[i] = '\0';
			}
			var = m_pRs->GetCollect("RDW");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbctarget.rdw[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbctarget.rdw[i] = '\0';
			}
			var = m_pRs->GetCollect("PLT");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.plttarget.plt[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.plttarget.plt[i] = '\0';
			}
			var = m_pRs->GetCollect("MPV");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.plttarget.mpv[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.plttarget.mpv[i] = '\0';
			}
			var = m_pRs->GetCollect("PDW");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.plttarget.pdw[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.plttarget.pdw[i] = '\0';
			}
			var = m_pRs->GetCollect("PCT");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.plttarget.pct[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.plttarget.pct[i] = '\0';
			}			
			
			var = m_pRs->GetCollect("WBC_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.wbc[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.wbc[i] = '\0';
			}

			var = m_pRs->GetCollect("LYMP_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.lymp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.lymp[i] = '\0';
			}

			var = m_pRs->GetCollect("NEUP_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.neup[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.neup[i] = '\0';
			}
			var = m_pRs->GetCollect("MONOP_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.monop[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.monop[i] = '\0';
			}
			var = m_pRs->GetCollect("EOSP_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.eosp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.eosp[i] = '\0';
			}
			var = m_pRs->GetCollect("BASOP_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.basp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.basp[i] = '\0';
			}
			var = m_pRs->GetCollect("ALYP_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.alyp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.alyp[i] = '\0';
			}
			var = m_pRs->GetCollect("LICP_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.licp[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.licp[i] = '\0';
			}
			var = m_pRs->GetCollect("LYM_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.lym[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.lym[i] = '\0';
			}
			var = m_pRs->GetCollect("NEU_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.neu[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.neu[i] = '\0';
			}
			var = m_pRs->GetCollect("MONO_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.mono[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.mono[i] = '\0';
			}
			var = m_pRs->GetCollect("EOS_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.eos[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.eos[i] = '\0';
			}
			var = m_pRs->GetCollect("BASO_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.bas[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.bas[i] = '\0';
			}
			var = m_pRs->GetCollect("ALY_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.aly[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.aly[i] = '\0';
			}
			var = m_pRs->GetCollect("LIC_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.wbcsd.lic[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.wbcsd.lic[i] = '\0';
			}
			var = m_pRs->GetCollect("RBC_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbcsd.rbc[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbcsd.rbc[i] = '\0';
			}
			var = m_pRs->GetCollect("HGB_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbcsd.hgb[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbcsd.hgb[i] = '\0';
			}
			var = m_pRs->GetCollect("HCT_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbcsd.hct[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbcsd.hct[i] = '\0';
			}
			var = m_pRs->GetCollect("MCV_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbcsd.mcv[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbcsd.mcv[i] = '\0';
			}
			var = m_pRs->GetCollect("MCH_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbcsd.mch[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbcsd.mch[i] = '\0';
			}
			var = m_pRs->GetCollect("MCHC_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbcsd.mchc[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbcsd.mchc[i] = '\0';
			}
			var = m_pRs->GetCollect("RDW_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.rbcsd.rdw[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.rbcsd.rdw[i] = '\0';
			}
			var = m_pRs->GetCollect("PLT_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.pltsd.plt[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.pltsd.plt[i] = '\0';
			}
			var = m_pRs->GetCollect("MPV_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.pltsd.mpv[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.pltsd.mpv[i] = '\0';
			}
			var = m_pRs->GetCollect("PDW_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.pltsd.pdw[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.pltsd.pdw[i] = '\0';
			}
			var = m_pRs->GetCollect("PCT_SD");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_edit_cur.pltsd.pct[i] = curr[i];
				for (; i < 6; i++)
					qc_edit_cur.pltsd.pct[i] = '\0';
			}
			qc_edit.push_back(qc_edit_cur);
			m_pRs->MoveNext();
		}
	}
	
	catch (_com_error &e)
	{
		TRACE("GetQCFile异常");
	}

	/*打开edit表格进行备份*/

	
	ExeSql(m_pDB, m_pRs, select_qc_result);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();

		}
		else
		{
			TRACE("\n表内数据为空!\n");
			return;
		}
		while ((!m_pRs->adoEOF))
		{
			qc_result_data qc_result_cur;
			

			var = m_pRs->GetCollect("WBC");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.wbc[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.wbc[i] = '\0';
			}

			var = m_pRs->GetCollect("LYMP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.lymp[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.lymp[i] = '\0';
			}

			var = m_pRs->GetCollect("NEUP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.neup[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.neup[i] = '\0';
			}
			var = m_pRs->GetCollect("MONOP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.monop[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.monop[i] = '\0';
			}
			var = m_pRs->GetCollect("EOSP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.eosp[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.eosp[i] = '\0';
			}
			var = m_pRs->GetCollect("BASOP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.basp[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.basp[i] = '\0';
			}
			var = m_pRs->GetCollect("ALYP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.alyp[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.alyp[i] = '\0';
			}
			var = m_pRs->GetCollect("LICP");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.licp[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.licp[i] = '\0';
			}
			var = m_pRs->GetCollect("LYM");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.lym[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.lym[i] = '\0';
			}
			var = m_pRs->GetCollect("NEU");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.neu[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.neu[i] = '\0';
			}
			var = m_pRs->GetCollect("MONO");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.mono[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.mono[i] = '\0';
			}
			var = m_pRs->GetCollect("EOS");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.eos[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.eos[i] = '\0';
			}
			var = m_pRs->GetCollect("BASO");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.bas[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.bas[i] = '\0';
			}
			var = m_pRs->GetCollect("ALY");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.aly[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.aly[i] = '\0';
			}
			var = m_pRs->GetCollect("LIC");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.wbcdata.lic[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.wbcdata.lic[i] = '\0';
			}
			var = m_pRs->GetCollect("RBC");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.rbcdata.rbc[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.rbcdata.rbc[i] = '\0';
			}
			var = m_pRs->GetCollect("HGB");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.rbcdata.hgb[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.rbcdata.hgb[i] = '\0';
			}
			var = m_pRs->GetCollect("HCT");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.rbcdata.hct[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.rbcdata.hct[i] = '\0';
			}
			var = m_pRs->GetCollect("MCV");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.rbcdata.mcv[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.rbcdata.mcv[i] = '\0';
			}
			var = m_pRs->GetCollect("MCH");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.rbcdata.mch[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.rbcdata.mch[i] = '\0';
			}
			var = m_pRs->GetCollect("MCHC");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.rbcdata.mchc[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.rbcdata.mchc[i] = '\0';
			}
			var = m_pRs->GetCollect("RDW");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.rbcdata.rdw[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.rbcdata.rdw[i] = '\0';
			}
			var = m_pRs->GetCollect("PLT");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.pltdata.plt[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.pltdata.plt[i] = '\0';
			}
			var = m_pRs->GetCollect("MPV");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.pltdata.mpv[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.pltdata.mpv[i] = '\0';
			}
			var = m_pRs->GetCollect("PDW");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.pltdata.pdw[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.pltdata.pdw[i] = '\0';
			}
			var = m_pRs->GetCollect("PCT");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.pltdata.pct[i] = curr[i];
				for (; i < 6; i++)
					qc_result_cur.pltdata.pct[i] = '\0';
			}			

			
			var = m_pRs->GetCollect("basograph");
			if (var.vt != VT_NULL)
			{
				CString basograph = m_pRs->GetCollect("basograph");
				INT_PTR iLen = (basograph.GetLength()) / 2;
				BYTE *pByte = new BYTE[iLen];
				int iPos = 0, iStart = 0;
				while (iPos<iLen)
				{
					CString strToken;
					strToken = basograph[iPos * 2];
					strToken += basograph[iPos * 2 + 1];
					if (strToken.IsEmpty())
						break;
					pByte[iPos] = (BYTE)_tcstol(strToken, NULL, 16);
					qc_result_cur.basograph[iPos] = pByte[iPos];
					iPos++;
				}
				delete[]pByte;
			}

			var = m_pRs->GetCollect("rbcgraph");
			if (var.vt != VT_NULL)
			{
				CString rbcgraph = m_pRs->GetCollect("rbcgraph");
				INT_PTR iLen = (rbcgraph.GetLength()) / 2;
				BYTE *pByte = new BYTE[iLen];
				int iPos = 0, iStart = 0;
				while (iPos<iLen)
				{
					CString strToken;
					strToken = rbcgraph[iPos * 2];
					strToken += rbcgraph[iPos * 2 + 1];
					if (strToken.IsEmpty())
						break;
					pByte[iPos] = (BYTE)_tcstol(strToken, NULL, 16);
					qc_result_cur.rbcgraph[iPos] = pByte[iPos];
					iPos++;
				}
				delete[]pByte;
			}

			var = m_pRs->GetCollect("pltgraph");
			if (var.vt != VT_NULL)
			{
				CString pltgraph = m_pRs->GetCollect("pltgraph");
				INT_PTR iLen = (pltgraph.GetLength()) / 2;
				BYTE *pByte = new BYTE[iLen];
				int iPos = 0, iStart = 0;
				while (iPos<iLen)
				{
					CString strToken;
					strToken = pltgraph[iPos * 2];
					strToken += pltgraph[iPos * 2 + 1];
					if (strToken.IsEmpty())
						break;
					pByte[iPos] = (BYTE)_tcstol(strToken, NULL, 16);
					qc_result_cur.pltgraph[iPos] = pByte[iPos];
					iPos++;
				}
				delete[]pByte;
			}
			
			var = m_pRs->GetCollect("lmneflg");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.lmneflg[i] = curr[i];
				for (; i < 9; i++)
					qc_result_cur.lmneflg[i] = '\0';
			}

			var = m_pRs->GetCollect("basoflg");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				qc_result_cur.basoflg[0] = curr[0];
			}

			var = m_pRs->GetCollect("rbcflg");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.rbcflg[i] = curr[i];
				for (; i < 2; i++)
					qc_result_cur.rbcflg[i] = '\0';
			}

			var = m_pRs->GetCollect("pltflg");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.pltflg[i] = curr[i];
				for (; i < 2; i++)
					qc_result_cur.pltflg[i] = '\0';
			}

			var = m_pRs->GetCollect("qctype");
			if (var.vt != VT_NULL)
			{
				qc_result_cur.qctype = m_pRs->GetCollect("qctype");
				qc_result_cur.qctype += '0';
			}
			var = m_pRs->GetCollect("filenum");
			if (var.vt != VT_NULL)
			{
				qc_result_cur.filenum = m_pRs->GetCollect("filenum");
				qc_result_cur.filenum += '0';
			}

			var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
			{
				qc_result_cur.time = m_pRs->GetCollect("time");
			}

			var = m_pRs->GetCollect("date");
			if (var.vt != VT_NULL)
			{
				CString curr = (LPCSTR)_bstr_t(var);
				int i;
				for (i = 0; i < curr.GetLength(); i++)
					qc_result_cur.date[i] = curr[i];
				for (; i < 11; i++)
					qc_result_cur.date[i] = '\0';
			}
			
			var = m_pRs->GetCollect("row");
			if (var.vt != VT_NULL)
			{
				qc_result_cur.row = m_pRs->GetCollect("row");
			}
			
			var = m_pRs->GetCollect("lmne");
			if (var.vt != VT_NULL)
			{
				char *temp;
				CString lmnegraph = m_pRs->GetCollect("lmne");
				INT_PTR iLen = (lmnegraph.GetLength()) / 2;
				BYTE *pByte = new BYTE[iLen];
				int iPos = 0, iStart = 0;
				while (iPos<iLen)
				{
					CString strToken;
					strToken = lmnegraph[iPos * 2];
					strToken += lmnegraph[iPos * 2 + 1];
					if (strToken.IsEmpty())
						break;
					pByte[iPos] = (BYTE)_tcstol(strToken, NULL, 16);
					qc_result_cur.lmnegraph[iPos] = pByte[iPos];
					iPos++;
				}
				while (iPos < 7500)
					qc_result_cur.lmnegraph[iPos++] = '\0';
				delete[]pByte;
				//				strncpy(param.lmnegraph, temp, sizeof(param.lmnegraph) / sizeof(char));
			}
			qc_result.push_back(qc_result_cur);
			m_pRs->MoveNext();
		}
	}
	catch (_com_error &e)
	{
		TRACE("异常");
	}
	
	CloseDataBase(m_pDB, m_pRs);
	DatabaseSave(qc_edit, qc_result);

}


void CQualityControlView::DatabaseSave(vector<qc_edit_data_info> &qc_edit, vector<qcresult_info> &qc_result)
{
	/*打开目标数据库，进行两个表格的数据备份*/
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;

	if (-1 == OpenDataBase("appdata.accdb", m_pDB, m_pRs)){
		return;
	}

	CString select_qc_edit = "delete  from qceditdata";
	CString select_qc_result = "delete  from qcresultdata";
	/*打开表格进行删除*/
	ExeSql(m_pDB, m_pRs, select_qc_edit);
	ExeSql(m_pDB, m_pRs, select_qc_result);
	CloseDataBase(m_pDB, m_pRs);

	CString filename;
	filename.Format(_T("appdata.accdb"));
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;

	for (int i = 0; i < qc_edit.size(); i++)
	{
		qc_edit_data_info *pqcLjXXrEditData = &qc_edit[i];


		CString qctype;
		//qctype.Format((*pqcLjXXrEditData).qctype);
		qctype = (*pqcLjXXrEditData).qctype;
		//TRACE("***###\nqctype=%s\n",qctype);
		CString filenum;
		//filenum.Format((*pqcLjXXrEditData).filenum);
		filenum = (*pqcLjXXrEditData).filenum;
		CString Number;
		Number = ChartsToCString((*pqcLjXXrEditData).Number, sizeof((*pqcLjXXrEditData).Number) / sizeof(char));
		CString Deadline;
		Deadline = ChartsToCString((*pqcLjXXrEditData).Deadline, sizeof((*pqcLjXXrEditData).Deadline) / sizeof(char));
		CString wbctarget_wbc;
		wbctarget_wbc = ChartsToCString((*pqcLjXXrEditData).wbctarget.wbc, sizeof((*pqcLjXXrEditData).wbctarget.wbc) / sizeof(char));
		CString wbctarget_lymp;
		wbctarget_lymp = ChartsToCString((*pqcLjXXrEditData).wbctarget.lymp, sizeof((*pqcLjXXrEditData).wbctarget.lymp) / sizeof(char));
		CString wbctarget_neup;
		wbctarget_neup = ChartsToCString((*pqcLjXXrEditData).wbctarget.neup, sizeof((*pqcLjXXrEditData).wbctarget.neup) / sizeof(char));
		CString wbctarget_monop;
		wbctarget_monop = ChartsToCString((*pqcLjXXrEditData).wbctarget.monop, sizeof((*pqcLjXXrEditData).wbctarget.monop) / sizeof(char));
		CString wbctarget_eosp;
		wbctarget_eosp = ChartsToCString((*pqcLjXXrEditData).wbctarget.eosp, sizeof((*pqcLjXXrEditData).wbctarget.eosp) / sizeof(char));
		CString wbctarget_basp;
		wbctarget_basp = ChartsToCString((*pqcLjXXrEditData).wbctarget.basp, sizeof((*pqcLjXXrEditData).wbctarget.basp) / sizeof(char));
		CString wbctarget_alyp;
		wbctarget_alyp = ChartsToCString((*pqcLjXXrEditData).wbctarget.alyp, sizeof((*pqcLjXXrEditData).wbctarget.alyp) / sizeof(char));
		CString wbctarget_licp;
		wbctarget_licp = ChartsToCString((*pqcLjXXrEditData).wbctarget.licp, sizeof((*pqcLjXXrEditData).wbctarget.licp) / sizeof(char));
		CString wbctarget_lym;
		wbctarget_lym = ChartsToCString((*pqcLjXXrEditData).wbctarget.lym, sizeof((*pqcLjXXrEditData).wbctarget.lym) / sizeof(char));
		CString wbctarget_neu;
		wbctarget_neu = ChartsToCString((*pqcLjXXrEditData).wbctarget.neu, sizeof((*pqcLjXXrEditData).wbctarget.neu) / sizeof(char));
		CString wbctarget_mono;
		wbctarget_mono = ChartsToCString((*pqcLjXXrEditData).wbctarget.mono, sizeof((*pqcLjXXrEditData).wbctarget.mono) / sizeof(char));
		CString wbctarget_eos;
		wbctarget_eos = ChartsToCString((*pqcLjXXrEditData).wbctarget.eos, sizeof((*pqcLjXXrEditData).wbctarget.eos) / sizeof(char));
		CString wbctarget_bas;
		wbctarget_bas = ChartsToCString((*pqcLjXXrEditData).wbctarget.bas, sizeof((*pqcLjXXrEditData).wbctarget.bas) / sizeof(char));
		CString wbctarget_aly;
		wbctarget_aly = ChartsToCString((*pqcLjXXrEditData).wbctarget.aly, sizeof((*pqcLjXXrEditData).wbctarget.aly) / sizeof(char));
		CString wbctarget_lic;
		wbctarget_lic = ChartsToCString((*pqcLjXXrEditData).wbctarget.lic, sizeof((*pqcLjXXrEditData).wbctarget.lic) / sizeof(char));
		CString rbctarget_rbc;
		rbctarget_rbc = ChartsToCString((*pqcLjXXrEditData).rbctarget.rbc, sizeof((*pqcLjXXrEditData).rbctarget.rbc) / sizeof(char));
		CString rbctarget_hgb;
		rbctarget_hgb = ChartsToCString((*pqcLjXXrEditData).rbctarget.hgb, sizeof((*pqcLjXXrEditData).rbctarget.hgb) / sizeof(char));
		CString rbctarget_hct;
		rbctarget_hct = ChartsToCString((*pqcLjXXrEditData).rbctarget.hct, sizeof((*pqcLjXXrEditData).rbctarget.hct) / sizeof(char));
		CString rbctarget_mcv;
		rbctarget_mcv = ChartsToCString((*pqcLjXXrEditData).rbctarget.mcv, sizeof((*pqcLjXXrEditData).rbctarget.mcv) / sizeof(char));
		CString rbctarget_mch;
		rbctarget_mch = ChartsToCString((*pqcLjXXrEditData).rbctarget.mch, sizeof((*pqcLjXXrEditData).rbctarget.mch) / sizeof(char));
		CString rbctarget_mchc;
		rbctarget_mchc = ChartsToCString((*pqcLjXXrEditData).rbctarget.mchc, sizeof((*pqcLjXXrEditData).rbctarget.mchc) / sizeof(char));
		CString rbctarget_rdw;
		rbctarget_rdw = ChartsToCString((*pqcLjXXrEditData).rbctarget.rdw, sizeof((*pqcLjXXrEditData).rbctarget.rdw) / sizeof(char));
		CString plttarget_plt;
		plttarget_plt = ChartsToCString((*pqcLjXXrEditData).plttarget.plt, sizeof((*pqcLjXXrEditData).plttarget.plt) / sizeof(char));
		CString plttarget_mpv;
		plttarget_mpv = ChartsToCString((*pqcLjXXrEditData).plttarget.mpv, sizeof((*pqcLjXXrEditData).plttarget.mpv) / sizeof(char));
		CString plttarget_pdw;
		plttarget_pdw = ChartsToCString((*pqcLjXXrEditData).plttarget.pdw, sizeof((*pqcLjXXrEditData).plttarget.pdw) / sizeof(char));
		CString plttarget_pct;
		plttarget_pct = ChartsToCString((*pqcLjXXrEditData).plttarget.pct, sizeof((*pqcLjXXrEditData).plttarget.pct) / sizeof(char));
		CString wbcsd_wbc;
		wbcsd_wbc = ChartsToCString((*pqcLjXXrEditData).wbcsd.wbc, sizeof((*pqcLjXXrEditData).wbcsd.wbc) / sizeof(char));
		CString wbcsd_lymp;
		wbcsd_lymp = ChartsToCString((*pqcLjXXrEditData).wbcsd.lymp, sizeof((*pqcLjXXrEditData).wbcsd.lymp) / sizeof(char));
		CString wbcsd_neup;
		wbcsd_neup = ChartsToCString((*pqcLjXXrEditData).wbcsd.neup, sizeof((*pqcLjXXrEditData).wbcsd.neup) / sizeof(char));
		CString wbcsd_monop;
		wbcsd_monop = ChartsToCString((*pqcLjXXrEditData).wbcsd.monop, sizeof((*pqcLjXXrEditData).wbcsd.monop) / sizeof(char));
		CString wbcsd_eosp;
		wbcsd_eosp = ChartsToCString((*pqcLjXXrEditData).wbcsd.eosp, sizeof((*pqcLjXXrEditData).wbcsd.eosp) / sizeof(char));
		CString wbcsd_basp;
		wbcsd_basp = ChartsToCString((*pqcLjXXrEditData).wbcsd.basp, sizeof((*pqcLjXXrEditData).wbcsd.basp) / sizeof(char));
		CString wbcsd_alyp;
		wbcsd_alyp = ChartsToCString((*pqcLjXXrEditData).wbcsd.alyp, sizeof((*pqcLjXXrEditData).wbcsd.alyp) / sizeof(char));
		CString wbcsd_licp;
		wbcsd_licp = ChartsToCString((*pqcLjXXrEditData).wbcsd.licp, sizeof((*pqcLjXXrEditData).wbcsd.licp) / sizeof(char));
		CString wbcsd_lym;
		wbcsd_lym = ChartsToCString((*pqcLjXXrEditData).wbcsd.lym, sizeof((*pqcLjXXrEditData).wbcsd.lym) / sizeof(char));
		CString wbcsd_neu;
		wbcsd_neu = ChartsToCString((*pqcLjXXrEditData).wbcsd.neu, sizeof((*pqcLjXXrEditData).wbcsd.neu) / sizeof(char));
		CString wbcsd_mono;
		wbcsd_mono = ChartsToCString((*pqcLjXXrEditData).wbcsd.mono, sizeof((*pqcLjXXrEditData).wbcsd.mono) / sizeof(char));
		CString wbcsd_eos;
		wbcsd_eos = ChartsToCString((*pqcLjXXrEditData).wbcsd.eos, sizeof((*pqcLjXXrEditData).wbcsd.eos) / sizeof(char));
		CString wbcsd_bas;
		wbcsd_bas = ChartsToCString((*pqcLjXXrEditData).wbcsd.bas, sizeof((*pqcLjXXrEditData).wbcsd.bas) / sizeof(char));
		CString wbcsd_aly;
		wbcsd_aly = ChartsToCString((*pqcLjXXrEditData).wbcsd.aly, sizeof((*pqcLjXXrEditData).wbcsd.aly) / sizeof(char));
		CString wbcsd_lic;
		wbcsd_lic = ChartsToCString((*pqcLjXXrEditData).wbcsd.lic, sizeof((*pqcLjXXrEditData).wbcsd.lic) / sizeof(char));
		CString rbcsd_rbc;
		rbcsd_rbc = ChartsToCString((*pqcLjXXrEditData).rbcsd.rbc, sizeof((*pqcLjXXrEditData).rbcsd.rbc) / sizeof(char));
		CString rbcsd_hgb;
		rbcsd_hgb = ChartsToCString((*pqcLjXXrEditData).rbcsd.hgb, sizeof((*pqcLjXXrEditData).rbcsd.hgb) / sizeof(char));
		CString rbcsd_hct;
		rbcsd_hct = ChartsToCString((*pqcLjXXrEditData).rbcsd.hct, sizeof((*pqcLjXXrEditData).rbcsd.hct) / sizeof(char));
		CString rbcsd_mcv;
		rbcsd_mcv = ChartsToCString((*pqcLjXXrEditData).rbcsd.mcv, sizeof((*pqcLjXXrEditData).rbcsd.mcv) / sizeof(char));
		CString rbcsd_mch;
		rbcsd_mch = ChartsToCString((*pqcLjXXrEditData).rbcsd.mch, sizeof((*pqcLjXXrEditData).rbcsd.mch) / sizeof(char));
		CString rbcsd_mchc;
		rbcsd_mchc = ChartsToCString((*pqcLjXXrEditData).rbcsd.mchc, sizeof((*pqcLjXXrEditData).rbcsd.mchc) / sizeof(char));
		CString rbcsd_rdw;
		rbcsd_rdw = ChartsToCString((*pqcLjXXrEditData).rbcsd.rdw, sizeof((*pqcLjXXrEditData).rbcsd.rdw) / sizeof(char));
		CString pltsd_plt;
		pltsd_plt = ChartsToCString((*pqcLjXXrEditData).pltsd.plt, sizeof((*pqcLjXXrEditData).pltsd.plt) / sizeof(char));
		CString pltsd_mpv;
		pltsd_mpv = ChartsToCString((*pqcLjXXrEditData).pltsd.mpv, sizeof((*pqcLjXXrEditData).pltsd.mpv) / sizeof(char));
		CString pltsd_pdw;
		pltsd_pdw = ChartsToCString((*pqcLjXXrEditData).pltsd.pdw, sizeof((*pqcLjXXrEditData).pltsd.pdw) / sizeof(char));
		CString pltsd_pct;
		pltsd_pct = ChartsToCString((*pqcLjXXrEditData).pltsd.pct, sizeof((*pqcLjXXrEditData).pltsd.pct) / sizeof(char));
		CString insertqceditdata = _T("insert into [qceditdata]([qctype],[filenum],[number],[deadline],[WBC],[LYMP],[NEUP],[MONOP],[EOSP],[BASOP],[ALYP],[LICP],[LYM],[NEU],[MONO],[EOS],[BASO],[ALY],[LIC],[RBC],[HGB],[HCT],[MCV],[MCH],[MCHC],[RDW],[PLT],[MPV],[PDW],[PCT],[WBC_SD],[LYMP_SD],[NEUP_SD],[MONOP_SD],[EOSP_SD],[BASOP_SD],[ALYP_SD],[LICP_SD],[LYM_SD],[NEU_SD],[MONO_SD],[EOS_SD],[BASO_SD],[ALY_SD],[LIC_SD],[RBC_SD],[HGB_SD],[HCT_SD],[MCV_SD],[MCH_SD],[MCHC_SD],[RDW_SD],[PLT_SD],[MPV_SD],[PDW_SD],[PCT_SD]) values('") +
			qctype.Trim() + "' ,'" + filenum.Trim() + "' ,'" + Number.Trim() + "' ,'" + Deadline.Trim() + "' ,'" +
			wbctarget_wbc.Trim() + "' ,'" + wbctarget_lymp.Trim() + "' ,'" + wbctarget_neup.Trim() + "' ,'" + wbctarget_monop.Trim() + "' ,'" + wbctarget_eosp.Trim() + "' ,'" +
			wbctarget_basp.Trim() + "' ,'" + wbctarget_alyp.Trim() + "' ,'" + wbctarget_licp.Trim() + "' ,'" + wbctarget_lym.Trim() + "' ,'" + wbctarget_neu.Trim() + "' ,'" +
			wbctarget_mono.Trim() + "' ,'" + wbctarget_eos.Trim() + "' ,'" + wbctarget_bas.Trim() + "' ,'" + wbctarget_aly.Trim() + "' ,'" + wbctarget_lic.Trim() + "' ,'" +
			rbctarget_rbc.Trim() + "' ,'" + rbctarget_hgb.Trim() + "' ,'" + rbctarget_hct.Trim() + "' ,'" + rbctarget_mcv.Trim() + "' ,'" + rbctarget_mch.Trim() + "' ,'" +
			rbctarget_mchc.Trim() + "' ,'" + rbctarget_rdw.Trim() + "' ,'" + plttarget_plt.Trim() + "' ,'" + plttarget_mpv.Trim() + "' ,'" + plttarget_pdw.Trim() + "' ,'" +
			plttarget_pct.Trim() + "' ,'" + wbcsd_wbc.Trim() + "' ,'" + wbcsd_lymp.Trim() + "' ,'" + wbcsd_neup.Trim() + "' ,'" + wbcsd_monop.Trim() + "' ,'" + wbcsd_eosp.Trim() + "' ,'" +
			wbcsd_basp.Trim() + "' ,'" + wbcsd_alyp.Trim() + "' ,'" + wbcsd_licp.Trim() + "' ,'" + wbcsd_lym.Trim() + "' ,'" + wbcsd_neu.Trim() + "' ,'" + wbcsd_mono.Trim() + "' ,'" + wbcsd_eos.Trim() + "' ,'" +
			wbcsd_bas.Trim() + "' ,'" + wbcsd_aly.Trim() + "' ,'" + wbcsd_lic.Trim() + "' ,'" + rbcsd_rbc.Trim() + "' ,'" + rbcsd_hgb.Trim() + "' ,'" + rbcsd_hct.Trim() + "' ,'" + rbcsd_mcv.Trim() + "' ,'" +
			rbcsd_mch.Trim() + "' ,'" + rbcsd_mchc.Trim() + "' ,'" + rbcsd_rdw.Trim() + "' ,'" + pltsd_plt.Trim() + "' ,'" + pltsd_mpv.Trim() + "' ,'" + pltsd_pdw.Trim() + "' ,'" + pltsd_pct.Trim() + "');";

		ExeSql(m_pDB, m_pRs, insertqceditdata);
	}
	for (int i = 0; i < qc_result.size(); i++)
	{
		qcresult_info *qcresultdata = &qc_result[i];

		CString row;
		row.Format(_T("%d"), qcresultdata->row);
		CString wbcdata_wbc;
		wbcdata_wbc = ChartsToCString(qcresultdata->wbcdata.wbc, sizeof(qcresultdata->wbcdata.wbc) / sizeof(char));
		CString wbcdata_lymp;
		wbcdata_lymp = ChartsToCString(qcresultdata->wbcdata.lymp, sizeof(qcresultdata->wbcdata.lymp) / sizeof(char));
		CString wbcdata_neup;
		wbcdata_neup = ChartsToCString(qcresultdata->wbcdata.neup, sizeof(qcresultdata->wbcdata.neup) / sizeof(char));
		CString wbcdata_monop;
		wbcdata_monop = ChartsToCString(qcresultdata->wbcdata.monop, sizeof(qcresultdata->wbcdata.monop) / sizeof(char));
		CString wbcdata_eosp;
		wbcdata_eosp = ChartsToCString(qcresultdata->wbcdata.eosp, sizeof(qcresultdata->wbcdata.eosp) / sizeof(char));
		CString wbcdata_basp;
		wbcdata_basp = ChartsToCString(qcresultdata->wbcdata.basp, sizeof(qcresultdata->wbcdata.basp) / sizeof(char));
		CString wbcdata_alyp;
		wbcdata_alyp = ChartsToCString(qcresultdata->wbcdata.alyp, sizeof(qcresultdata->wbcdata.alyp) / sizeof(char));
		CString wbcdata_licp;
		wbcdata_licp = ChartsToCString(qcresultdata->wbcdata.licp, sizeof(qcresultdata->wbcdata.licp) / sizeof(char));
		CString wbcdata_lym;
		wbcdata_lym = ChartsToCString(qcresultdata->wbcdata.lym, sizeof(qcresultdata->wbcdata.lym) / sizeof(char));
		CString wbcdata_neu;
		wbcdata_neu = ChartsToCString(qcresultdata->wbcdata.neu, sizeof(qcresultdata->wbcdata.neu) / sizeof(char));
		CString wbcdata_mono;
		wbcdata_mono = ChartsToCString(qcresultdata->wbcdata.mono, sizeof(qcresultdata->wbcdata.mono) / sizeof(char));
		CString wbcdata_eos;
		wbcdata_eos = ChartsToCString(qcresultdata->wbcdata.eos, sizeof(qcresultdata->wbcdata.eos) / sizeof(char));
		CString wbcdata_bas;
		wbcdata_bas = ChartsToCString(qcresultdata->wbcdata.bas, sizeof(qcresultdata->wbcdata.bas) / sizeof(char));
		CString wbcdata_aly;
		wbcdata_aly = ChartsToCString(qcresultdata->wbcdata.aly, sizeof(qcresultdata->wbcdata.aly) / sizeof(char));
		CString wbcdata_lic;
		wbcdata_lic = ChartsToCString(qcresultdata->wbcdata.lic, sizeof(qcresultdata->wbcdata.lic) / sizeof(char));
		CString rbcdata_rbc;
		rbcdata_rbc = ChartsToCString(qcresultdata->rbcdata.rbc, sizeof(qcresultdata->rbcdata.rbc) / sizeof(char));
		CString rbcdata_hgb;
		rbcdata_hgb = ChartsToCString(qcresultdata->rbcdata.hgb, sizeof(qcresultdata->rbcdata.hgb) / sizeof(char));
		CString rbcdata_hct;
		rbcdata_hct = ChartsToCString(qcresultdata->rbcdata.hct, sizeof(qcresultdata->rbcdata.hct) / sizeof(char));
		CString rbcdata_mcv;
		rbcdata_mcv = ChartsToCString(qcresultdata->rbcdata.mcv, sizeof(qcresultdata->rbcdata.mcv) / sizeof(char));
		CString rbcdata_mch;
		rbcdata_mch = ChartsToCString(qcresultdata->rbcdata.mch, sizeof(qcresultdata->rbcdata.mch) / sizeof(char));
		CString rbcdata_mchc;
		rbcdata_mchc = ChartsToCString(qcresultdata->rbcdata.mchc, sizeof(qcresultdata->rbcdata.mchc) / sizeof(char));
		CString rbcdata_rdw;
		rbcdata_rdw = ChartsToCString(qcresultdata->rbcdata.rdw, sizeof(qcresultdata->rbcdata.rdw) / sizeof(char));
		CString pltdata_plt;
		pltdata_plt = ChartsToCString(qcresultdata->pltdata.plt, sizeof(qcresultdata->pltdata.plt) / sizeof(char));
		CString pltdata_mpv;
		pltdata_mpv = ChartsToCString(qcresultdata->pltdata.mpv, sizeof(qcresultdata->pltdata.mpv) / sizeof(char));
		CString pltdata_pdw;
		pltdata_pdw = ChartsToCString(qcresultdata->pltdata.pdw, sizeof(qcresultdata->pltdata.pdw) / sizeof(char));
		CString pltdata_pct;
		pltdata_pct = ChartsToCString(qcresultdata->pltdata.pct, sizeof(qcresultdata->pltdata.pct) / sizeof(char));
		CString lmnegraph;
		lmnegraph = ChartsToCStringdata2(qcresultdata->lmnegraph, sizeof(qcresultdata->lmnegraph) / sizeof(char));
		CString basograph;
		basograph = ChartsToCStringdata2(qcresultdata->basograph, sizeof(qcresultdata->basograph) / sizeof(char));
		CString rbcgraph;
		rbcgraph = ChartsToCStringdata2(qcresultdata->rbcgraph, sizeof(qcresultdata->rbcgraph) / sizeof(char));
		CString pltgraph;
		pltgraph = ChartsToCStringdata2(qcresultdata->pltgraph, sizeof(qcresultdata->pltgraph) / sizeof(char));
		CString lmneflg;
		lmneflg = ChartsToCString(qcresultdata->lmneflg, sizeof(qcresultdata->lmneflg) / sizeof(char));
		CString basoflg;
		basoflg = ChartsToCString(qcresultdata->basoflg, sizeof(qcresultdata->basoflg) / sizeof(char));
		CString rbcflg;
		rbcflg = ChartsToCString(qcresultdata->rbcflg, sizeof(qcresultdata->rbcflg) / sizeof(char));
		CString pltflg;
		pltflg = ChartsToCString(qcresultdata->pltflg, sizeof(qcresultdata->pltflg) / sizeof(char));
		CString qctype;
		qctype = (qcresultdata->qctype);
		CString filenum;
		filenum = qcresultdata->filenum;
		CString time1;

		//date = ChartsToCString(qcresultdata->date, sizeof(qcresultdata->date) / sizeof(char));
		time(&systime);
		caltime = localtime(&systime);
		qcresultdata->time = (caltime->tm_hour) * 10000 + (caltime->tm_min) * 100 + caltime->tm_sec;

		sprintf(qcresultdata->date, "%04d-%02d-%02d", caltime->tm_year + 1900, caltime->tm_mon + 1, caltime->tm_mday);//mny,20171219

		time1.Format(_T("%d"), qcresultdata->time);

		CString insertqcresult = _T("insert into [qcresultdata]([row],[WBC],[LYMP],[NEUP],[MONOP],[EOSP],[BASOP],[ALYP],[LICP],[LYM],[NEU],[MONO],[EOS],[BASO],[ALY],[LIC],[RBC],[HGB],[HCT],[MCV],[MCH],[MCHC],[RDW],[PLT],[MPV],[PDW],[PCT],[lmne],[basograph],[rbcgraph],[pltgraph],[lmneflg],[basoflg],[rbcflg],[pltflg],[qctype],[filenum],[time],[date]) values(") + row + " ,'" + wbcdata_wbc + "' ,'" + wbcdata_lymp + "' ,'" + wbcdata_neup + "' ,'" +
			wbcdata_monop + "' ,'" + wbcdata_eosp + "' ,'" + wbcdata_basp + "' ,'" + wbcdata_alyp + "' ,'" + wbcdata_licp + "' ,'" + wbcdata_lym + "' ,'" +
			wbcdata_neu + "' ,'" + wbcdata_mono + "' ,'" + wbcdata_eos + "' ,'" + wbcdata_bas + "' ,'" + wbcdata_aly + "' ,'" + wbcdata_lic + "' ,'" +
			rbcdata_rbc + "' ,'" + rbcdata_hgb + "' ,'" + rbcdata_hct + "' ,'" + rbcdata_mcv + "' ,'" + rbcdata_mch + "' ,'" + rbcdata_mchc + "' ,'" +
			rbcdata_rdw + "' ,'" + pltdata_plt + "' ,'" + pltdata_mpv + "' ,'" + pltdata_pdw + "' ,'" + pltdata_pct + "' ,'" + lmnegraph + "' ,'" +
			basograph + "' ,'" + rbcgraph + "' ,'" + pltgraph + "' ,'" + lmneflg + "' ,'" + basoflg + "' ,'" + rbcflg + "' ,'" + pltflg + "' ,'"
			+ qctype + "' ,'" + filenum + "' ,'" + time1 + "' ,'" + qcresultdata->date + "');";

		//[lmne],[basograph],,[pltgraph]
		//+ lmnegraph + "' ,'" + basograph + "' ,'" +  + "' ,'"+pltgraph
		CString testtesttest = _T("insert into [qcresultdata]([rbcgraph]) values('") + rbcgraph + "');";
		//ExeSql(m_pDB, m_pRs, insertqcresult);
		ExeSql(m_pDB, m_pRs, insertqcresult);
	}
	CloseDataBase(m_pDB, m_pRs);
	MessageBox(L"成功导入数据库!", L"提示", MB_OK | MB_ICONINFORMATION);
}
CString CQualityControlView::ChartsToCString(char * chart, int len)
{
	CString string;
	int i = 0;

	//while (i<len){
	while ((i < len) && (chart[i] != 0)){
		if ((chart[i] >= 0) && (chart[i] <= 9))
			chart[i] += 48;
		/*if (chart[i] == '\x1')
		{
		char temp = 0;
		string += temp;
		break;
		}
		else*/
		{
			string += chart[i];
			i++;
		}
	}
	char a = 0;
	string += a;
	string.Replace('\0', ' ');
	return string;
}
CString CQualityControlView::ChartsToCStringdata2(unsigned char * chart, int len)
{
	CString string;
	int i = 0;

	//while (i<len){
	while ((i < len) && (chart[i] != 0))
	{
		CString final_test1;
		if (chart[i] < 16)
		{
			int a = 0;
			CString temp;
			temp.Format(_T("%d"), a);
			string += temp;
		}
		final_test1.Format(_T("%x"), chart[i]);
		string += final_test1;
		i++;
	}
	char a = 0;
	string += a;
	string.Replace('\0', ' ');
	return string;

}