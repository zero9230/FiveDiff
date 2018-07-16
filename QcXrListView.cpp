// QcXrListView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QcXrListView.h"
#include "afxdialogex.h"


// CQcXrListView 对话框

IMPLEMENT_DYNAMIC(CQcXrListView, CDialogEx)

CQcXrListView::CQcXrListView(CWnd* pParent /*=NULL*/)
: CDialogEx(CQcXrListView::IDD, pParent)
{
	for (int i = 0; i < 26; i++){
		for (int j = 0; j < 31 * 2; j++){
			data[i][j] = -5.0;
		}
	}
	curpage = 0;
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

CQcXrListView::~CQcXrListView()
{
}

void CQcXrListView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QC_XR_LIST_LIST, m_ListList);
	DDX_Text(pDX, IDC_QC_XR_LIST_PAGE_NUM, pageNum);
}


BEGIN_MESSAGE_MAP(CQcXrListView, CDialogEx)
	ON_MESSAGE(UM_REDRAW, OnRedraw)
	ON_BN_CLICKED(IDC_QC_XR_LIST_UP_BUTTON, &CQcXrListView::OnBnClickedQcXrListUpButton)
	ON_BN_CLICKED(IDC_QC_XR_LIST_DOWN_BUTTON, &CQcXrListView::OnBnClickedQcXrListDownButton)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PRINT_X_LIST, &CQcXrListView::OnBnClickedPrintXList)
END_MESSAGE_MAP()


// CQcXrListView 消息处理程序


void CQcXrListView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


HBRUSH CQcXrListView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CQcXrListView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString item_temp, done_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_QC_XR_LIST_STATIC0, item_temp);
	GetDlgItem(IDC_QC_XR_LIST_STATIC0)->SetFont(&textfont);

	GetDlgItem(IDC_QC_XR_LIST_NUMBER)->EnableWindow(false);//此处锁定批号和有效期的输入框
	GetDlgItem(IDC_QC_XR_LIST_DEADLINE)->EnableWindow(false);
	curpage = 0;
	InitListList();
	GetQcXrEditData();
	itemCount = GetQcXrResultData(Controltype, Controlfile);
	setQcAveRan();
	UpdateListResultList();
	maxPage = itemCount % 6 == 0 ? itemCount / 6 - 1 : itemCount / 6;


	pageNum.Format(L"第 %d/%d 页", curpage + 1, maxPage + 1);
	UpdateData(false);
	/****/
	if (curpage == 0)
		GetDlgItem(IDC_QC_XR_LIST_UP_BUTTON)->EnableWindow(false);
	else
		GetDlgItem(IDC_QC_XR_LIST_UP_BUTTON)->EnableWindow(true);
	if (curpage == maxPage)
		GetDlgItem(IDC_QC_XR_LIST_DOWN_BUTTON)->EnableWindow(false);
	else
		GetDlgItem(IDC_QC_XR_LIST_DOWN_BUTTON)->EnableWindow(true);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CQcXrListView::InitListList()
{
	/***************初始化表格**************/
	CRect rect;
	CString table[28] = { "日期", "时间", "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO", "ALY%", "LIC%", "LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#",
		"LIC#", "RBC", "HGB", "HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	/*	CString unit[] = { _T("10^9/L"), _T("%"), _T("%"), _T("%"), _T("%"),
	_T("%"), _T("%"), _T("%"), _T("10^9/L"), _T("10^9/L"),
	_T("10^9/L"), _T("10^9/L"), _T("10^9/L"), _T("10^9/L"), _T("10^9/L"),_T("10^12/L"), _T("g/L"), _T("%"), _T("fL"),
	_T("pg"), _T("g/L"), _T("%"), _T("fL"), _T("10^9/L"), _T("fL"), _T("fL"), _T("%") };
	*/
	// 获取编程语言列表视图控件的位置和大小   
	m_ListList.GetClientRect(&rect);
	m_ListList.SetRowHeigt(20);
	// 为列表视图控件添加全行选中和栅格风格   
	m_ListList.SetExtendedStyle(m_ListList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	// 为列表视图控件添加四列;
	m_ListList.InsertColumn(0, _T(""), LVCFMT_CENTER, rect.Width() * 1 / 9, 0);
	m_ListList.InsertColumn(1, _T("总平均值"), LVCFMT_CENTER, rect.Width() * 1 / 9, 1);
	m_ListList.InsertColumn(2, _T("平均极差"), LVCFMT_CENTER, rect.Width() * 1 / 9, 2);
	m_ListList.InsertColumn(3, _T("1"), LVCFMT_CENTER, rect.Width() * 1 / 9, 3);
	m_ListList.InsertColumn(4, _T(""), LVCFMT_CENTER, rect.Width() * 1 / 9, 4);
	m_ListList.InsertColumn(5, _T("2"), LVCFMT_CENTER, rect.Width() * 1 / 9, 5);
	m_ListList.InsertColumn(6, _T(""), LVCFMT_CENTER, rect.Width() * 1 / 9, 6);
	m_ListList.InsertColumn(7, _T("3"), LVCFMT_CENTER, rect.Width() * 1 / 9, 7);
	m_ListList.InsertColumn(8, _T(""), LVCFMT_CENTER, rect.Width() * 1 / 9, 7);

	// 在列表视图控件中插入列表项，并设置列表子项文本
	//m_ListList.InsertItem(0, _T("WBC"));
	////m_CoefficientList.InsertItem(0, _T(""));
	//m_ListList.InsertItem(1, _T("平均值"));
	//m_ListList.InsertItem(2, _T("CV值"));
	//m_ListList.InsertItem(3, _T("当前系数"));
	//m_ListList.InsertItem(4, _T("新系数"));
	for (int i = 0; i < 28; i++)
	{
		m_ListList.InsertItem(i, table[i]);
	}
	/***************填充初始化数据**************/
	//m_ListList.SetItemText(0, 4, L"10^9/L");
	//m_ListList.SetItemText(1, 4, L"%");
	//m_ListList.SetItemText(2, 4, L"%");
	//m_ListList.SetItemText(3, 4, L"%");
	//m_ListList.SetItemText(4, 4, L"%");
	//m_ListList.SetItemText(5, 4, L"%");
	//m_ListList.SetItemText(6, 4, L"%");
	//m_ListList.SetItemText(7, 4, L"%");
	//m_ListList.SetItemText(8, 4, L"10^9/L");
	//m_ListList.SetItemText(9, 4, L"10^9/L");
	//m_ListList.SetItemText(10, 4, L"10^9/L");
	//m_ListList.SetItemText(11, 4, L"10^9/L");
	//m_ListList.SetItemText(12, 4, L"10^9/L");
	//m_ListList.SetItemText(13, 4, L"10^9/L");
	//m_ListList.SetItemText(14, 4, L"10^9/L");
	//m_ListList.SetItemText(15, 4, L"10^12/L");
	//m_ListList.SetItemText(16, 4, L"g/L");
	//m_ListList.SetItemText(17, 4, L"%");
	//m_ListList.SetItemText(18, 4, L"fL");
	//m_ListList.SetItemText(19, 4, L"pg");
	//m_ListList.SetItemText(20, 4, L"g/L");
	//m_ListList.SetItemText(21, 4, L"%");
	//m_ListList.SetItemText(22, 4, L"10^9/L");
	//m_ListList.SetItemText(23, 4, L"fL");
	//m_ListList.SetItemText(24, 4, L"fL");
	//m_ListList.SetItemText(25, 4, L"%");

}

//获取靶值和偏差限,并填入列表中
bool CQcXrListView::GetQcXrEditData(){
	CString filename;
	CString	qctypetemp;
	CString qcFileNumtemp;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;
	CString strTemp;
	int temprow;

	qctypetemp.Format(L"%d", Controltype);
	qcFileNumtemp.Format(L"%d", Controlfile);
	CString inital_target = _T("select * from qceditdata where qctype ='") + qctypetemp + "'and filenum ='" + qcFileNumtemp + "';";

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1){
		//MessageBox(L"Open Failure!");
		return false;
	}
	ExeSql(m_pDB, m_pRs, inital_target);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();

		}
		else
		{
			TRACE("\n表内数据为空!\n");
			//return FALSE;//由于此处需要将表格中的数据置为空，所以不可直接返回
		}
		temprow = int(m_pRs->GetRecordCount());

		//TRACE("\n###temprow=%d\n",temprow);
		//TRACE("\n###nRow=%d", nRow);
		//nRow = temprow;
		if (temprow == 0)//有效行数为0，则填入空值
		{
			QcXrFileExist = 0;
			number = "";
			deadline = "";
			GetDlgItem(IDC_QC_XR_LIST_NUMBER)->SetWindowText(number);
			GetDlgItem(IDC_QC_XR_LIST_DEADLINE)->SetWindowText(deadline);
			//for (int i = 0; i < 26; i++)
			//{
			//	totalAve[i] = "";
			//	totalRan[i] = "";				
			//	m_ListList.SetItemText(i, 1, totalAve[i]);
			//	m_ListList.SetItemText(i, 2, totalRan[i]);
			//	//m_ListList.SetItemText(i, 3, TargetLimit[i]);
			//}
		}
		else
		{
			QcXrFileExist = 1;

			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
			{
				strTemp = m_pRs->GetCollect("number");
				number = (LPCSTR)_bstr_t(var);
				GetDlgItem(IDC_QC_XR_LIST_NUMBER)->SetWindowText(number);
				//填入批号
			}
			var = m_pRs->GetCollect("deadline");
			if (var.vt != VT_NULL)
			{
				int qctype = m_pRs->GetCollect("deadline");
				deadline.Format(L"%d", qctype);
				GetDlgItem(IDC_QC_XR_LIST_DEADLINE)->SetWindowText(deadline);
				//填入截止日期
			}

			////填入总平均值
			//for (int j = 0; j < 26; j++)
			//{
			//	var = m_pRs->GetFields()->GetItem((long)j + 5)->Value;//读取当前记录质控26个项目的靶值
			//	totalAve[j] = var;
			//	m_ListList.SetItemText(j + 2, 1, totalAve[j]);
			//}
			////填入平均极差
			//for (int j = 0; j < 26; j++)
			//{
			//	var = m_pRs->GetFields()->GetItem((long)j + 26 + 5)->Value;//读取当前记录质控26个项目的偏差值
			//	totalRan[j] = var;
			//	m_ListList.SetItemText(j + 2, 2, totalRan[j]);
			//	//double lowLimit = _wtof(Qctarget[j]) - _wtof(TargetLimit[j]);
			//	//double highimit = _wtof(Qctarget[j]) + _wtof(TargetLimit[j]);
			//	//CString str;
			//	//str.Format(L"%.2lf", lowLimit);
			//	//m_ListList.SetItemText(j, 1, str);
			//	//str.Format(L"%.2lf", highimit);
			//	//m_ListList.SetItemText(j, 3, str);
			//}

		}
		CloseDataBase(m_pDB, m_pRs);
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE("GetQcFile异常");
	}
	return false;
}

//获取质控结果
int CQcXrListView::GetQcXrResultData(int controltype, int controlfile){

	CString select_detail;
	CString filename;
	int rownum = 0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	CString strTemp;
	CString hhTemp;
	CString mmTemp;
	CString ssTemp;
	int k = 0;
	for (int i = 0; i < 31; i++){//将数据容器data初始清空
		qcResDate[i] = "";
		qcResTime[i] = "";

	}
	//
	select_detail.Format(L"select * from qcresultdata where qctype = '%d' and filenum = '%d' order by date,time;", controltype, controlfile);

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return -1;
	ExeSql(m_pDB, m_pRs, select_detail);
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
			var = m_pRs->GetCollect("date");
			if (var.vt != VT_NULL)
			{
				qcResDate[k] = m_pRs->GetCollect("date");
			}

			var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
			{
				qcResTime[k] = m_pRs->GetCollect("time");
				hhTemp = qcResTime[k].Left(2);
				mmTemp = qcResTime[k].Mid(2, 2);
				ssTemp = qcResTime[k].Right(2);
				qcResTime[k].Format(L"%s:%s:%s", hhTemp, mmTemp, ssTemp);
			}

			for (int i = 0; i < 26; i++)
			{
				var = m_pRs->GetFields()->GetItem((long)2 + i)->Value;
				if (var.vt != VT_NULL){
					strTemp = (LPCSTR)_bstr_t(var);
					data[i][k] = _wtof(strTemp);
					//UpdateListResultList();
				}
			}
			k++;
			m_pRs->MoveNext();
		}
		if (k != 0){
			qcXrListDataNum = k / 2;
		}
		else{
			qcXrListDataNum = 0;
		}
	}
	catch (_com_error &e)
	{
		TRACE("GetDetail函数程序异常\n");
	}
	CloseDataBase(m_pDB, m_pRs);
	return rownum;
}

void CQcXrListView::setQcAveRan(){
	if (qcXrListDataNum == 0) return;
	double aveSum = 0, ranSum = 0;
	CString str;
	for (int i = 0; i < 26; i++){
		for (int j = 0; j < qcXrListDataNum * 2; j += 2){
			aveSum += data[i][j];
			ranSum += data[i][j + 1];
		}
		qcAve[i] = aveSum / qcXrListDataNum;
		qcRan[i] = ranSum / qcXrListDataNum;
		aveSum = 0;
		ranSum = 0;
	}
	for (int i = 0; i < 26; i++){
		str.Format(L"%.2lf", qcAve[i]);
		m_ListList.SetItemText(i + 2, 1, str);
		str.Format(L"%.2lf", qcRan[i]);
		m_ListList.SetItemText(i + 2, 2, str);
	}
}



//更新list控件中的数据，在初始化及翻页时调用
void CQcXrListView::UpdateListResultList(){
	startIndex = curpage * 6;
	endIndex = curpage * 6 + 5;
	CString strData;

	for (int i = startIndex; i <= endIndex; i++){	//外循环，遍历每一页中的记录，从0~5
		if (i > 30){								//总共显示31条数据，多出来的显示空白
			m_ListList.SetItemText(0, i + 3 - curpage * 6, L"");
			m_ListList.SetItemText(1, i + 3 - curpage * 6, L"");
			for (int j = 0; j < 26; j++){				//内循环，遍历每条记录的参数
				m_ListList.SetItemText(j + 2, i + 3 - curpage * 6, L"");
			}
		}
		else{
			m_ListList.SetItemText(0, i + 3 - curpage * 6, qcResDate[i]);
			m_ListList.SetItemText(1, i + 3 - curpage * 6, qcResTime[i]);
			for (int j = 0; j < 26; j++){				//内循环，遍历每条记录的参数
				strData.Format(L"%.2lf", data[j][i]);
				m_ListList.SetItemText(j + 2, i + 3 - curpage * 6, strData);
				if (data[j][i] == -5.0){
					m_ListList.SetItemText(j + 2, i + 3 - curpage * 6, L"");
				}
			}
		}
	}
	pageNum.Format(L"第 %d/%d 页", curpage + 1, maxPage + 1);
	UpdateData(false);
}


void CQcXrListView::OnBnClickedQcXrListUpButton()
{
	// TODO:  在此添加控件通知处理程序代码
	//获取页码，合理性判断，改变页码，更新resultList
	if (curpage > 0)
	{
		curpage--;
	}
	if (curpage == 0)
		GetDlgItem(IDC_QC_XR_LIST_UP_BUTTON)->EnableWindow(false);
	else
		GetDlgItem(IDC_QC_XR_LIST_UP_BUTTON)->EnableWindow(true);
	if (curpage == maxPage)
		GetDlgItem(IDC_QC_XR_LIST_DOWN_BUTTON)->EnableWindow(false);
	else
		GetDlgItem(IDC_QC_XR_LIST_DOWN_BUTTON)->EnableWindow(true);	//UpdateData();
	UpdateListResultList();

}


void CQcXrListView::OnBnClickedQcXrListDownButton()
{
	// TODO:  在此添加控件通知处理程序代码
	if (curpage <maxPage)
	{
		curpage++;
	}
	if (curpage == 0)
		GetDlgItem(IDC_QC_XR_LIST_UP_BUTTON)->EnableWindow(false);
	else
		GetDlgItem(IDC_QC_XR_LIST_UP_BUTTON)->EnableWindow(true);
	if (curpage == maxPage)
		GetDlgItem(IDC_QC_XR_LIST_DOWN_BUTTON)->EnableWindow(false);
	else
		GetDlgItem(IDC_QC_XR_LIST_DOWN_BUTTON)->EnableWindow(true);	//UpdateData();
	UpdateListResultList();
}

void CQcXrListView::UpdateView(){
	CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_QC_XR_LIST_STATIC0, item_temp);
	GetDlgItem(IDC_QC_XR_LIST_STATIC0)->SetFont(&textfont);

	GetDlgItem(IDC_QC_XR_LIST_NUMBER)->EnableWindow(false);//此处锁定批号和有效期的输入框
	GetDlgItem(IDC_QC_XR_LIST_DEADLINE)->EnableWindow(false);

	//InitListList();
	GetQcXrEditData();
	itemCount = GetQcXrResultData(Controltype, Controlfile);
	setQcAveRan();
	UpdateListResultList();
	maxPage = itemCount % 6 == 0 ? itemCount / 6 - 1 : itemCount / 6;

	pageNum.Format(L"第 %d/%d 页", curpage + 1, maxPage + 1);
	UpdateData(false);

}

afx_msg LRESULT CQcXrListView::OnRedraw(WPARAM, LPARAM){
	UpdateView();
	return 0;
}


void CQcXrListView::OnBnClickedPrintXList()
{
	CString table[28] = { "日期", "时间", "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO", "ALY%", "LIC%", "LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#",
		"LIC#", "RBC", "HGB", "HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	PRINTDLG pd;
	int num;
	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(PRINTDLG));
	pd.lStructSize = sizeof(PRINTDLG);
	pd.hwndOwner = NULL;
	pd.hDevMode = NULL;     // Don't forget to free or store hDevMode
	pd.hDevNames = NULL;     // Don't forget to free or store hDevNames
	pd.Flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC;
	pd.nCopies = 1;
	pd.nFromPage = 0xFFFF;
	pd.nToPage = 0xFFFF;
	pd.nMinPage = 1;
	pd.nMaxPage = 0xFFFF;
	//PrintDlg(&pd);
	if (PrintDlg(&pd) == TRUE)
	{
		// GDI calls to render output. 
		DOCINFO di;
		ZeroMemory(&di, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = _T("NewDoc");
		StartDoc(pd.hDC, &di);
		CDC pDC;
		CFont font;
		CPen penBlack;
		CString str;
		CFont *poldfont;
		int page_num;
		int finally_page_num;

		pDC.Attach(pd.hDC);
		font.CreateFont(80, 30, 0, 0, 400, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
		penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));


		finally_page_num = itemCount % 6;
		if (finally_page_num == 0)
			page_num = itemCount / 6;
		else
			page_num = itemCount / 6 + 1;

		for (int m_page = 0; m_page < page_num; m_page++)
		{
			StartPage(pd.hDC);
			pDC.TextOutW(2200, 300, L"	X-R靶值编辑(文件03)");
			if (m_page == 0)
				poldfont = pDC.SelectObject(&font);
			else
				pDC.SelectObject(&font);

			pDC.TextOutW(500, 350, L"批号:");
			pDC.TextOutW(500, 500, L"有效期:");
			pDC.TextOutW(800, 350, number);
			pDC.TextOutW(800, 500, deadline);
			pDC.SetViewportOrg(500, 700);
			pDC.Rectangle(0, 0, 4000, 5800);
			for (int j = 0; j < 28; j++)
			{
				pDC.TextOutW(20, (j + 1) * 200, table[j]);
			}
			pDC.TextOutW(400, 30, L"总平均值");
			pDC.TextOutW(800, 30, L"平均极差");
			pDC.TextOutW(1350, 30, L"1");
			pDC.TextOutW(2250, 30, L"2");
			pDC.TextOutW(3150, 30, L"3");
			if (m_page < page_num - 1)
			{
				//写时间和日期
				for (int i = 0; i < 6; i++)
				{
					pDC.TextOutW(1200 + i * 450, 200, qcResDate[i + m_page * 6]);
					pDC.TextOutW(1200 + i * 450, 400, qcResTime[i + m_page * 6]);
				}
				//写入质控数据
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 26; j++)
					{
						str.Format(L"%.2f", data[j][i + m_page * 6]);
						pDC.TextOutW(1200 + i * 450, 600 + j * 200, str);
					}
				}
			}
			else
			{
				if (finally_page_num != 0)
				{
					//写时间和日期
					for (int i = 0; i < finally_page_num; i++)
					{
						pDC.TextOutW(1200 + i * 450, 200, qcResDate[i + m_page * 6]);
						pDC.TextOutW(1200 + i * 450, 400, qcResTime[i + m_page * 6]);
					}
					//写入质控数据
					for (int i = 0; i < finally_page_num; i++)
					{
						for (int j = 0; j < 26; j++)
						{
							str.Format(L"%.2f", data[j][i + m_page * 6]);
							pDC.TextOutW(1200 + i * 450, 600 + j * 200, str);
						}
					}
				}
				else
				{
					for (int i = 0; i < 6; i++)
					{
						pDC.TextOutW(1200 + i * 450, 200, qcResDate[i + m_page * 6]);
						pDC.TextOutW(1200 + i * 450, 400, qcResTime[i + m_page * 6]);
					}
					//写入质控数据
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 26; j++)
						{
							str.Format(L"%.2f", data[j][i + m_page * 6]);
							pDC.TextOutW(1200 + i * 450, 600 + j * 200, str);
						}
					}
				}

			}
			//写总平均值和极差
			for (int i = 0; i < 26; i++)
			{
				str.Format(L"%.2f", qcAve[i]);
				pDC.TextOutW(400, 600 + i * 200, str);
				str.Format(L"%.2f", qcRan[i]);
				pDC.TextOutW(800, 600 + i * 200, str);
			}

			pDC.SelectObject(poldfont);
			EndPage(pd.hDC);
		}
		EndDoc(pd.hDC);

		// Delete DC when done.
		DeleteDC(pd.hDC);
	}
}