// QcXrTestView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QcXrTestView.h"
#include "afxdialogex.h"
#include "QcXrListView.h"
#include "QcXrChartView.h"


// CQcXrTestView 对话框

IMPLEMENT_DYNAMIC(CQcXrTestView, CDialogEx)

extern CQcXrListView m_QcXrListPage;
extern CQcXrChartView m_QcXrChartPage;

CQcXrTestView::CQcXrTestView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQcXrTestView::IDD, pParent)
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

CQcXrTestView::~CQcXrTestView()
{
}

void CQcXrTestView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QC_XR_TEST_LIST, m_QcXrTestList);
}


BEGIN_MESSAGE_MAP(CQcXrTestView, CDialogEx)
	ON_WM_PAINT()
	ON_MESSAGE(WM_QUALITYTEST, &CQcXrTestView::OnQualitytest)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CQcXrTestView::OnAckspi)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CQcXrTestView 消息处理程序


void CQcXrTestView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


HBRUSH CQcXrTestView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CQcXrTestView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J 质控测试（文件 %02u）", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X 质控测试（文件 %02u）", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R 质控测试（文件 %02u）", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_QC_XR_TEST_STATIC0, item_temp);
	GetDlgItem(IDC_QC_XR_TEST_STATIC0)->SetFont(&textfont);
	getQcXrEditFile();
	InitQcXrTestList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CQcXrTestView::InitQcXrTestList()
{
	CRect rect;
	CString table[26] = { "WBC", "LYM%", "NEU%", "MONO%", "EOS%", "BASO", "ALY%", "LIC%", "LYM#", "NEU#", "MONO#", "EOS#", "BASO#", "ALY#",
		"LIC#", "RBC", "HGB", "HCT", "MCV", "MCH", "MCHC", "RDW", "PLT", "MPV", "PDW", "PCT" };
	// 获取编程语言列表视图控件的位置和大小   
	m_QcXrTestList.GetClientRect(&rect);
	m_QcXrTestList.SetRowHeigt(20);
	// 为列表视图控件添加全行选中和栅格风格   
	m_QcXrTestList.SetExtendedStyle(m_QcXrTestList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	// 为列表视图控件添加四列
	m_QcXrTestList.InsertColumn(0, _T("项目"), LVCFMT_CENTER, rect.Width() * 1 / 6, 0);
	m_QcXrTestList.InsertColumn(1, _T("第一次"), LVCFMT_CENTER, rect.Width() * 1 / 6, 1);
	m_QcXrTestList.InsertColumn(2, _T("第二次"), LVCFMT_CENTER, rect.Width() * 1 / 6, 2);
	m_QcXrTestList.InsertColumn(3, _T("平均值"), LVCFMT_CENTER, rect.Width() * 1 / 6, 3);
	m_QcXrTestList.InsertColumn(4, _T("极差"), LVCFMT_CENTER, rect.Width() * 1 / 6, 4);
	m_QcXrTestList.InsertColumn(5, _T("单位"), LVCFMT_CENTER, rect.Width() * 1 / 7, 5);


	// 在列表视图控件中插入列表项，并设置列表子项文本
	//m_QcXrTestList.InsertItem(0, _T("WBC"));
	////m_CoefficientList.InsertItem(0, _T(""));
	//m_QcXrTestList.InsertItem(1, _T("平均值"));
	//m_QcXrTestList.InsertItem(2, _T("CV值"));
	//m_QcXrTestList.InsertItem(3, _T("当前系数"));
	//m_QcXrTestList.InsertItem(4, _T("新系数"));
	for (int i = 0; i < 26; i++)
	{
		m_QcXrTestList.InsertItem(i, table[i]);
	}

	m_QcXrTestList.SetItemText(0, 5, L"10^9/L");
	m_QcXrTestList.SetItemText(1, 5, L"%");
	m_QcXrTestList.SetItemText(2, 5, L"%");
	m_QcXrTestList.SetItemText(3, 5, L"%");
	m_QcXrTestList.SetItemText(4, 5, L"%");
	m_QcXrTestList.SetItemText(5, 5, L"%");
	m_QcXrTestList.SetItemText(6, 5, L"%");
	m_QcXrTestList.SetItemText(7, 5, L"%");
	m_QcXrTestList.SetItemText(8, 5, L"10^9/L");
	m_QcXrTestList.SetItemText(9, 5, L"10^9/L");
	m_QcXrTestList.SetItemText(10, 5, L"10^9/L");
	m_QcXrTestList.SetItemText(11, 5, L"10^9/L");
	m_QcXrTestList.SetItemText(12, 5, L"10^9/L");
	m_QcXrTestList.SetItemText(13, 5, L"10^9/L");
	m_QcXrTestList.SetItemText(14, 5, L"10^9/L");
	m_QcXrTestList.SetItemText(15, 5, L"10^12/L");
	m_QcXrTestList.SetItemText(16, 5, L"g/L");
	m_QcXrTestList.SetItemText(17, 5, L"%");
	m_QcXrTestList.SetItemText(18, 5, L"fL");
	m_QcXrTestList.SetItemText(19, 5, L"pg");
	m_QcXrTestList.SetItemText(20, 5, L"g/L");
	m_QcXrTestList.SetItemText(21, 5, L"%");
	m_QcXrTestList.SetItemText(22, 5, L"10^9/L");
	m_QcXrTestList.SetItemText(23, 5, L"fL");
	m_QcXrTestList.SetItemText(24, 5, L"fL");
	m_QcXrTestList.SetItemText(25, 5, L"%");
}

afx_msg LRESULT CQcXrTestView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	int rowCount = 0;
	switch (wParam)
	{
	case SPI_STATE_DATAISOK:
		if (PC_status != WAITING_DATA)
			break;
		KillTimer(POLLTIME);
		//接收BASO  数据
		sdata_cmd[0] = SPI_CMD_REQBASO;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(qcresultdata.basograph, SPI_TYPE_BASORES);
		//接收LMNE  数据
		sdata_cmd[0] = SPI_CMD_REQLMNE;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(qcresultdata.lmnegraph, SPI_TYPE_LMNERES);
		//接收HGB  数据
		sdata_cmd[0] = SPI_CMD_REQHGB;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(hgbgraph, SPI_TYPE_HGBRES);
		//接收RBC 数据
		sdata_cmd[0] = SPI_CMD_REQRBC;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(qcresultdata.rbcgraph, SPI_TYPE_RBCRES);
		//接收PLT   数据
		sdata_cmd[0] = SPI_CMD_REQPLT;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(qcresultdata.pltgraph, SPI_TYPE_PLTRES);

		m_qcDataProcess.QcWbcBasoAnalysis(&qcresultdata);	//和主测试过程独立开
		m_qcDataProcess.QcLmneAnalysis(&qcresultdata);		//必须放在BASO分析后面						
		m_qcDataProcess.QcHgbAnalysis(&qcresultdata);		//必须放在BASO分析前面
		m_qcDataProcess.QcRbcAnalysis(&qcresultdata);
		m_qcDataProcess.QcPltAnalysis(&qcresultdata);

		//数据库保存	
		testNum++;
		if (1 == testNum)
		{
			copyqcresultToResult1();		//第一次测试结果
			UpdateQcXrTestList1();			//填入第一次测试结果
			//GetDlgItem(IDC_QC_X_STATIC1)->SetDlgItemText(" ");
			
		}
		else if (2 == testNum)
		{
			getAveRan();	//将第二次测试结果放到平均测试结果中，并取平均值，并取极值
			//数据库保存	
			rowCount = getqcresultRow();
			qcresultdataRan.row = qcresultdataAve.row + 1;
			if (qcresultdataAve.row > 31 * 2)//将最前面的一个平均记录，一个极差记录删除
			{
				DelQcLjXXrResult(3, Controlfile, qcresultdataAve.row - 31 * 2);
				DelQcLjXXrResult(3, Controlfile, qcresultdataRan.row - 31 * 2);
			}
			//存入数据库的是平均值和极差
			AddQcLjXXrResult(&qcresultdataAve);
			AddQcLjXXrResult(&qcresultdataRan);

			UpdateQcXrTestList2();			//填入第二次测试结果
			UpdateQcXrTestHeadInfo();		//填入测试的头部信息，如日期，时间，编号

			//刷新质控的其他页面——质控图、质控列表		
			::PostMessage(m_QcXrChartPage, UM_REDRAW, 0, 0);
			::PostMessage(m_QcXrListPage, UM_REDRAW, 0, 0);
		}

		//刷新本界面
		UpdateData(false);
		//UpdateForm(&qcresultdata);
		//UpdatePrintChart(&qcresultdata);

		//等待流程结束
		PC_status = WAITING_TEST_OVER;
		SetTimer(POLLTIME, SPI_POLL_TIME3000, 0);
		break;
		//测试过程结束
	case SPI_STATE_TESTISOVER:
		PC_status = TEST_OVER;
		KillTimer(POLLTIME);
		DSP_status = Free;
		//ARM_GPIOCMD(EN_GREEN);
		key_status = true;
		TRACE("\nMSG_ACKSPI: Test Proc is over -------------#\n");
		break;
	default:
		break;
	}

	return 0;
}
void CQcXrTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent){
	case SLEEP_TIMER1:
	{
		KillTimer(SLEEP_TIMER1);
		TRACE("MSG_TIMER:SLEEP_TIMER1 is due -------------#\n");
		PC_status = WAITING_DATA;
		SetTimer(POLLTIME, SPI_POLL_TIME1000, 0);
		break;
	}
	case POLLTIME:
	{
		TRACE("MSG_TIMER:POLLTIME is due -------------#\n");

		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(WM_ACKSPI, rdata_state[0], 0);
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
afx_msg LRESULT CQcXrTestView::OnQualitytest(WPARAM wParam, LPARAM lParam)
{
	MessageBox(L"QC test in QualityTestView");
	{
		if (0 == QcXrFileExistEdit)
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"对应质控文件未编辑!", L"警告!");
			//else if (systemcfg.language == ENGLISH)
			//	CreateWarningBoxNonCHDlg(hDlg, "Refered QC File has not been edited", "Warning!");
			return 0;
		}
		key_status = FALSE;
		initQcXrData();	//数据初始化
		if (2 == testNum)
			testNum = 0;
		if (0 == testNum)
		{
			initQcXrAveData();
			initQcXrData();
		}
		DSP_status = Busy;
		sdata_cmd[0] = SPI_CMD_CBC5DIFF_MODE;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		//statusShowMess = 1;
		//显示运行
		SetTimer(SLEEP_TIMER1, 30000, 0);
	}
	return 0;
}

bool CQcXrTestView::getQcXrEditFile()//读取数据库中质控编辑数据，装入批号和截止日期中
{
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

	if (-1 == OpenDataBase(filename, m_pDB, m_pRs)){
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
			QcXrFileExistEdit = 0;
			tempXrNumber = "";
			tempXrDeadline = "";
			GetDlgItem(IDC_QC_XR_TEST_NUMBER)->SetWindowText(tempXrNumber);
			GetDlgItem(IDC_QC_XR_TEST_DEADLINE)->SetWindowText(tempXrDeadline);
		}
		else
		{
			QcXrFileExistEdit = 1;

			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
			{
				strTemp = m_pRs->GetCollect("number");
				tempXrNumber = (LPCSTR)_bstr_t(var);
				GetDlgItem(IDC_QC_XR_TEST_NUMBER)->SetWindowText(tempXrNumber);
				//填入批号
			}
			var = m_pRs->GetCollect("deadline");
			if (var.vt != VT_NULL)
			{
				int qctype = m_pRs->GetCollect("deadline");
				tempXrDeadline.Format(L"%d", qctype);
				GetDlgItem(IDC_QC_XR_TEST_DEADLINE)->SetWindowText(tempXrDeadline);
				//填入截止日期
			}

		}
		CloseDataBase(m_pDB, m_pRs);
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE("GetQcXrFile异常");
	}
	return false;


}
//获得最后记录数
int CQcXrTestView::getqcresultRow()
{
	CString filename;
	CString	qctypetemp;
	CString qcFileNumtemp;
	int 			rc = 0;
	int minRow, maxRow, rowCount;
	int i = 0;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;

	qctypetemp.Format(L"%d", Controltype);
	qcFileNumtemp.Format(L"%d", Controlfile);
	CString getQcRes = _T("select min(row),max(row) from qcresultdata where qctype ='") + qctypetemp + "'and filenum ='" + qcFileNumtemp + "';";
	if (-1 == OpenDataBase(filename, m_pDB, m_pRs)){
		MessageBox(L"Open Failure!");
		return 0;
	}
	rc = ExeSql(m_pDB, m_pRs, getQcRes);

	try{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空");
			return FALSE;
		}
		minRow = int(m_pRs->GetFields()->GetItem((long)0)->Value);
		maxRow = int(m_pRs->GetFields()->GetItem((long)1)->Value);
		rowCount = maxRow - minRow + 1;
		if (0 == (maxRow - minRow)){
			qcresultdataAve.row = 1;
		}
		else{
			qcresultdataAve.row = maxRow + 1;
		}
		TRACE("\n######maxRow=%d\n", maxRow);
	}
	catch (_com_error &e)
	{
		TRACE("getQcResultRow异常");
	}
	CloseDataBase(m_pDB, m_pRs);
	return rowCount;

}
void CQcXrTestView::initQcXrData()//质控测试参数就是26个，没有必要28个，和主测试流程不一样
{
	unsigned int i = 0;

	//默认字符为""
	qcresultdata.row = 0;

	qcresultdata.qctype = Controltype + 48;
	qcresultdata.filenum = Controlfile + 48;
	qcresultdata.time = 0;
	strcpy(qcresultdata.date, "");

	strcpy(qcresultdata.wbcdata.wbc, "**.**");

	strcpy(qcresultdata.wbcdata.lymp, "**.*");
	strcpy(qcresultdata.wbcdata.neup, "**.*");
	strcpy(qcresultdata.wbcdata.monop, "*.*");
	strcpy(qcresultdata.wbcdata.eosp, "*.*");
	strcpy(qcresultdata.wbcdata.basp, "*.*");
	strcpy(qcresultdata.wbcdata.alyp, "*.*");
	strcpy(qcresultdata.wbcdata.licp, "*.*");

	strcpy(qcresultdata.wbcdata.lym, "*.**");
	strcpy(qcresultdata.wbcdata.neu, "*.**");
	strcpy(qcresultdata.wbcdata.mono, "*.**");
	strcpy(qcresultdata.wbcdata.eos, "*.**");
	strcpy(qcresultdata.wbcdata.bas, "*.**");
	strcpy(qcresultdata.wbcdata.aly, "*.**");
	strcpy(qcresultdata.wbcdata.lic, "*.**");
	//RBC
	strcpy(qcresultdata.rbcdata.rbc, "*.**");
	strcpy(qcresultdata.rbcdata.hgb, "***.*");
	strcpy(qcresultdata.rbcdata.hct, "**.*");
	strcpy(qcresultdata.rbcdata.mcv, "***.*");
	strcpy(qcresultdata.rbcdata.mch, "**.*");
	strcpy(qcresultdata.rbcdata.mchc, "***.*");
	strcpy(qcresultdata.rbcdata.rdw, "**.*");
	//PLT
	strcpy(qcresultdata.pltdata.plt, "***");
	strcpy(qcresultdata.pltdata.mpv, "**.**");
	strcpy(qcresultdata.pltdata.pdw, "**.*");
	strcpy(qcresultdata.pltdata.pct, "**.**");
	//散点图
	for (i = 0; i < MATRIX_DATA_MAX; i++)
		qcresultdata.lmnegraph[i] = 1;
	//BASO直方图
	for (i = 0; i < 256; i++)
		qcresultdata.basograph[i] = 1;
	//RBC直方图
	for (i = 0; i < 512; i++)
		qcresultdata.rbcgraph[i] = 1;
	//PLT直方图
	for (i = 0; i < 256; i++)
		qcresultdata.pltgraph[i] = 1;
	//界标
	for (i = 0; i < 9; i++)
		qcresultdata.lmneflg[i] = 1;
	qcresultdata.basoflg[0] = 1;
	for (i = 0; i < 2; i++)
		qcresultdata.rbcflg[i] = 1;
	for (i = 0; i < 2; i++)
		qcresultdata.pltflg[i] = 1;
}

void CQcXrTestView::initQcXrAveData()//质控测试参数就是26个，没有必要28个，和主测试流程不一样
{
	int 		i = 0;

	//默认字符为""
	qcresultdataAve.row = 0;

	qcresultdataAve.qctype = Controltype + 48;
	qcresultdataAve.filenum = Controlfile + 48;
	qcresultdataAve.time = 0;
	strcpy(qcresultdataAve.date, "");

	strcpy(qcresultdataAve.wbcdata.wbc, "**.**");

	strcpy(qcresultdataAve.wbcdata.lymp, "**.*");
	strcpy(qcresultdataAve.wbcdata.neup, "**.*");
	strcpy(qcresultdataAve.wbcdata.monop, "*.*");
	strcpy(qcresultdataAve.wbcdata.eosp, "*.*");
	strcpy(qcresultdataAve.wbcdata.basp, "*.*");
	strcpy(qcresultdataAve.wbcdata.alyp, "*.*");
	strcpy(qcresultdataAve.wbcdata.licp, "*.*");

	strcpy(qcresultdataAve.wbcdata.lym, "*.**");
	strcpy(qcresultdataAve.wbcdata.neu, "*.**");
	strcpy(qcresultdataAve.wbcdata.mono, "*.**");
	strcpy(qcresultdataAve.wbcdata.eos, "*.**");
	strcpy(qcresultdataAve.wbcdata.bas, "*.**");
	strcpy(qcresultdataAve.wbcdata.aly, "*.**");
	strcpy(qcresultdataAve.wbcdata.lic, "*.**");
	//RBC
	strcpy(qcresultdataAve.rbcdata.rbc, "*.**");
	strcpy(qcresultdataAve.rbcdata.hgb, "***.*");
	strcpy(qcresultdataAve.rbcdata.hct, "**.*");
	strcpy(qcresultdataAve.rbcdata.mcv, "***.*");
	strcpy(qcresultdataAve.rbcdata.mch, "**.*");
	strcpy(qcresultdataAve.rbcdata.mchc, "***.*");
	strcpy(qcresultdataAve.rbcdata.rdw, "**.*");
	//PLT
	strcpy(qcresultdataAve.pltdata.plt, "***");
	strcpy(qcresultdataAve.pltdata.mpv, "**.**");
	strcpy(qcresultdataAve.pltdata.pdw, "**.*");
	strcpy(qcresultdataAve.pltdata.pct, "**.**");
	//散点图
	for (i = 0; i < MATRIX_DATA_MAX; i++)
		qcresultdataAve.lmnegraph[i] = 1;
	//BASO直方图
	for (i = 0; i < 256; i++)
		qcresultdataAve.basograph[i] = 1;
	//RBC直方图
	for (i = 0; i < 512; i++)
		qcresultdataAve.rbcgraph[i] = 1;
	//PLT直方图
	for (i = 0; i < 256; i++)
		qcresultdataAve.pltgraph[i] = 1;
	//界标
	for (i = 0; i < 9; i++)
		qcresultdataAve.lmneflg[i] = 1;
	qcresultdataAve.basoflg[0] = 1;
	for (i = 0; i < 2; i++)
		qcresultdataAve.rbcflg[i] = 1;
	for (i = 0; i < 2; i++)
		qcresultdataAve.pltflg[i] = 1;
}

void CQcXrTestView::initQcXrData1()//质控测试参数就是26个，没有必要28个，和主测试流程不一样
{
	unsigned int i = 0;

	//默认字符为""
	qcresultdata1.row = 0;

	qcresultdata1.qctype = Controltype + 48;
	qcresultdata1.filenum = Controlfile + 48;
	qcresultdata1.time = 0;
	strcpy(qcresultdata1.date, "");

	strcpy(qcresultdata1.wbcdata.wbc, "**.**");

	strcpy(qcresultdata1.wbcdata.lymp, "**.*");
	strcpy(qcresultdata1.wbcdata.neup, "**.*");
	strcpy(qcresultdata1.wbcdata.monop, "*.*");
	strcpy(qcresultdata1.wbcdata.eosp, "*.*");
	strcpy(qcresultdata1.wbcdata.basp, "*.*");
	strcpy(qcresultdata1.wbcdata.alyp, "*.*");
	strcpy(qcresultdata1.wbcdata.licp, "*.*");

	strcpy(qcresultdata1.wbcdata.lym, "*.**");
	strcpy(qcresultdata1.wbcdata.neu, "*.**");
	strcpy(qcresultdata1.wbcdata.mono, "*.**");
	strcpy(qcresultdata1.wbcdata.eos, "*.**");
	strcpy(qcresultdata1.wbcdata.bas, "*.**");
	strcpy(qcresultdata1.wbcdata.aly, "*.**");
	strcpy(qcresultdata1.wbcdata.lic, "*.**");
	//RBC
	strcpy(qcresultdata1.rbcdata.rbc, "*.**");
	strcpy(qcresultdata1.rbcdata.hgb, "***.*");
	strcpy(qcresultdata1.rbcdata.hct, "**.*");
	strcpy(qcresultdata1.rbcdata.mcv, "***.*");
	strcpy(qcresultdata1.rbcdata.mch, "**.*");
	strcpy(qcresultdata1.rbcdata.mchc, "***.*");
	strcpy(qcresultdata1.rbcdata.rdw, "**.*");
	//PLT
	strcpy(qcresultdata1.pltdata.plt, "***");
	strcpy(qcresultdata1.pltdata.mpv, "**.**");
	strcpy(qcresultdata1.pltdata.pdw, "**.*");
	strcpy(qcresultdata1.pltdata.pct, "**.**");
	//散点图
	for (i = 0; i < MATRIX_DATA_MAX; i++)
		qcresultdata1.lmnegraph[i] = 1;
	//BASO直方图
	for (i = 0; i < 256; i++)
		qcresultdata1.basograph[i] = 1;
	//RBC直方图
	for (i = 0; i < 512; i++)
		qcresultdata1.rbcgraph[i] = 1;
	//PLT直方图
	for (i = 0; i < 256; i++)
		qcresultdata1.pltgraph[i] = 1;
	//界标
	for (i = 0; i < 9; i++)
		qcresultdata1.lmneflg[i] = 1;
	qcresultdata1.basoflg[0] = 1;
	for (i = 0; i < 2; i++)
		qcresultdata1.rbcflg[i] = 1;
	for (i = 0; i < 2; i++)
		qcresultdata1.pltflg[i] = 1;
}


//将第一次测试结果放到平均测试结果中
void CQcXrTestView::copyqcresultToResult1()
{
	strcpy(qcresultdata1.wbcdata.wbc, qcresultdata.wbcdata.wbc);

	strcpy(qcresultdata1.wbcdata.lymp, qcresultdata.wbcdata.lymp);
	strcpy(qcresultdata1.wbcdata.neup, qcresultdata.wbcdata.neup);
	strcpy(qcresultdata1.wbcdata.monop, qcresultdata.wbcdata.monop);
	strcpy(qcresultdata1.wbcdata.eosp, qcresultdata.wbcdata.eosp);
	strcpy(qcresultdata1.wbcdata.basp, qcresultdata.wbcdata.basp);
	strcpy(qcresultdata1.wbcdata.alyp, qcresultdata.wbcdata.alyp);
	strcpy(qcresultdata1.wbcdata.licp, qcresultdata.wbcdata.licp);

	strcpy(qcresultdata1.wbcdata.lym, qcresultdata.wbcdata.lym);
	strcpy(qcresultdata1.wbcdata.neu, qcresultdata.wbcdata.neu);
	strcpy(qcresultdata1.wbcdata.mono, qcresultdata.wbcdata.mono);
	strcpy(qcresultdata1.wbcdata.eos, qcresultdata.wbcdata.eos);
	strcpy(qcresultdata1.wbcdata.bas, qcresultdata.wbcdata.bas);
	strcpy(qcresultdata1.wbcdata.aly, qcresultdata.wbcdata.aly);
	strcpy(qcresultdata1.wbcdata.lic, qcresultdata.wbcdata.lic);
	//RBC
	strcpy(qcresultdata1.rbcdata.rbc, qcresultdata.rbcdata.rbc);
	strcpy(qcresultdata1.rbcdata.hgb, qcresultdata.rbcdata.hgb);
	strcpy(qcresultdata1.rbcdata.hct, qcresultdata.rbcdata.hct);
	strcpy(qcresultdata1.rbcdata.mcv, qcresultdata.rbcdata.mcv);
	strcpy(qcresultdata1.rbcdata.mch, qcresultdata.rbcdata.mch);
	strcpy(qcresultdata1.rbcdata.mchc, qcresultdata.rbcdata.mchc);
	strcpy(qcresultdata1.rbcdata.rdw, qcresultdata.rbcdata.rdw);
	//PLT
	strcpy(qcresultdata1.pltdata.plt, qcresultdata.pltdata.plt);
	strcpy(qcresultdata1.pltdata.mpv, qcresultdata.pltdata.mpv);
	strcpy(qcresultdata1.pltdata.pdw, qcresultdata.pltdata.pdw);
	strcpy(qcresultdata1.pltdata.pct, qcresultdata.pltdata.pct);
}

//将第二次测试结果放到平均测试结果中，并取平均值，并取极值
void CQcXrTestView::getAveRan()
{
	float tempValue;
	float tempValue2;

	qcresultdataAve.qctype = Controltype + 48;
	qcresultdataRan.qctype = Controltype + 48;
	qcresultdataAve.filenum = Controlfile + 48;
	qcresultdataRan.filenum = Controlfile + 48;
	qcresultdataAve.time = 0;
	qcresultdataRan.time = 0;
	strcpy(qcresultdataAve.date, "");
	strcpy(qcresultdataRan.date, "");

	tempValue = atof(qcresultdata1.wbcdata.wbc) + atof(qcresultdata.wbcdata.wbc);   
	tempValue2 = atof(qcresultdata1.wbcdata.wbc) - atof(qcresultdata.wbcdata.wbc);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.wbc, "%.2f", tempValue);
	sprintf(qcresultdataRan.wbcdata.wbc, "%.2f", fabs(tempValue2));

	tempValue = atof(qcresultdata1.wbcdata.lymp) + atof(qcresultdata.wbcdata.lymp);
	tempValue2 = atof(qcresultdata1.wbcdata.lymp) - atof(qcresultdata.wbcdata.lymp);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.lymp, "%.1f", tempValue);
	sprintf(qcresultdataRan.wbcdata.lymp, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.neup) + atof(qcresultdata.wbcdata.neup);
	tempValue2 = atof(qcresultdata1.wbcdata.neup) - atof(qcresultdata.wbcdata.neup);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.neup, "%.1f", tempValue);
	sprintf(qcresultdataRan.wbcdata.neup, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.monop) + atof(qcresultdata.wbcdata.monop);
	tempValue2 = atof(qcresultdata1.wbcdata.monop) - atof(qcresultdata.wbcdata.monop);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.monop, "%.1f", tempValue);
	sprintf(qcresultdataRan.wbcdata.monop, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.eosp) + atof(qcresultdata.wbcdata.eosp);
	tempValue2 = atof(qcresultdata1.wbcdata.eosp) - atof(qcresultdata.wbcdata.eosp);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.eosp, "%.1f", tempValue);
	sprintf(qcresultdataRan.wbcdata.eosp, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.basp) + atof(qcresultdata.wbcdata.basp);
	tempValue2 = atof(qcresultdata1.wbcdata.basp) - atof(qcresultdata.wbcdata.basp);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.basp, "%.1f", tempValue);
	sprintf(qcresultdataRan.wbcdata.basp, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.alyp) + atof(qcresultdata.wbcdata.alyp);
	tempValue2 = atof(qcresultdata1.wbcdata.alyp) - atof(qcresultdata.wbcdata.alyp);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.alyp, "%.1f", tempValue);
	sprintf(qcresultdataRan.wbcdata.alyp, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.licp) + atof(qcresultdata.wbcdata.licp);
	tempValue2 = atof(qcresultdata1.wbcdata.licp) - atof(qcresultdata.wbcdata.licp);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.licp, "%.1f", tempValue);
	sprintf(qcresultdataRan.wbcdata.licp, "%.1f", fabs(tempValue2));

	tempValue = atof(qcresultdata1.wbcdata.lym) + atof(qcresultdata.wbcdata.lym);
	tempValue2 = atof(qcresultdata1.wbcdata.lym) - atof(qcresultdata.wbcdata.lym);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.lym, "%.2f", tempValue);
	sprintf(qcresultdataRan.wbcdata.lym, "%.2f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.neu) + atof(qcresultdata.wbcdata.neu);
	tempValue2 = atof(qcresultdata1.wbcdata.neu) - atof(qcresultdata.wbcdata.neu);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.neu, "%.2f", tempValue);
	sprintf(qcresultdataRan.wbcdata.neu, "%.2f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.mono) + atof(qcresultdata.wbcdata.mono);
	tempValue2 = atof(qcresultdata1.wbcdata.mono) - atof(qcresultdata.wbcdata.mono);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.mono, "%.2f", tempValue);
	sprintf(qcresultdataRan.wbcdata.mono, "%.2f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.eos) + atof(qcresultdata.wbcdata.eos);
	tempValue2 = atof(qcresultdata1.wbcdata.eos) - atof(qcresultdata.wbcdata.eos);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.eos, "%.2f", tempValue);
	sprintf(qcresultdataRan.wbcdata.eos, "%.2f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.bas) + atof(qcresultdata.wbcdata.bas);
	tempValue2 = atof(qcresultdata1.wbcdata.bas) - atof(qcresultdata.wbcdata.bas);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.bas, "%.2f", tempValue);
	sprintf(qcresultdataRan.wbcdata.bas, "%.2f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.aly) + atof(qcresultdata.wbcdata.aly);
	tempValue2 = atof(qcresultdata1.wbcdata.aly) - atof(qcresultdata.wbcdata.aly);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.aly, "%.2f", tempValue);
	sprintf(qcresultdataRan.wbcdata.aly, "%.2f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.wbcdata.lic) + atof(qcresultdata.wbcdata.lic);
	tempValue2 = atof(qcresultdata1.wbcdata.lic) - atof(qcresultdata.wbcdata.lic);
	tempValue /= 2;
	sprintf(qcresultdataAve.wbcdata.lic, "%.2f", tempValue);
	sprintf(qcresultdataRan.wbcdata.lic, "%.2f", fabs(tempValue2));

	tempValue = atof(qcresultdata1.rbcdata.rbc) + atof(qcresultdata.rbcdata.rbc);
	tempValue2 = atof(qcresultdata1.rbcdata.rbc) - atof(qcresultdata.rbcdata.rbc);
	tempValue /= 2;
	sprintf(qcresultdataAve.rbcdata.rbc, "%.2f", tempValue);
	sprintf(qcresultdataRan.rbcdata.rbc, "%.2f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.rbcdata.hgb) + atof(qcresultdata.rbcdata.hgb);
	tempValue2 = atof(qcresultdata1.rbcdata.hgb) - atof(qcresultdata.rbcdata.hgb);
	tempValue /= 2;
	sprintf(qcresultdataAve.rbcdata.hgb, "%.1f", tempValue);
	sprintf(qcresultdataRan.rbcdata.hgb, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.rbcdata.hct) + atof(qcresultdata.rbcdata.hct);
	tempValue2 = atof(qcresultdata1.rbcdata.hct) - atof(qcresultdata.rbcdata.hct);
	tempValue /= 2;
	sprintf(qcresultdataAve.rbcdata.hct, "%.1f", tempValue);
	sprintf(qcresultdataRan.rbcdata.hct, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.rbcdata.mcv) + atof(qcresultdata.rbcdata.mcv);
	tempValue2 = atof(qcresultdata1.rbcdata.mcv) - atof(qcresultdata.rbcdata.mcv);
	tempValue /= 2;
	sprintf(qcresultdataAve.rbcdata.mcv, "%.1f", tempValue);
	sprintf(qcresultdataRan.rbcdata.mcv, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.rbcdata.mch) + atof(qcresultdata.rbcdata.mch);
	tempValue2 = atof(qcresultdata1.rbcdata.mch) - atof(qcresultdata.rbcdata.mch);
	tempValue /= 2;
	sprintf(qcresultdataAve.rbcdata.mch, "%.1f", tempValue);
	sprintf(qcresultdataRan.rbcdata.mch, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.rbcdata.mchc) + atof(qcresultdata.rbcdata.mchc);
	tempValue2 = atof(qcresultdata1.rbcdata.mchc) - atof(qcresultdata.rbcdata.mchc);
	tempValue /= 2;
	sprintf(qcresultdataAve.rbcdata.mchc, "%.1f", tempValue);
	sprintf(qcresultdataRan.rbcdata.mchc, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.rbcdata.rdw) + atof(qcresultdata.rbcdata.rdw);
	tempValue2 = atof(qcresultdata1.rbcdata.rdw) - atof(qcresultdata.rbcdata.rdw);
	tempValue /= 2;
	sprintf(qcresultdataAve.rbcdata.rdw, "%.1f", tempValue);
	sprintf(qcresultdataRan.rbcdata.rdw, "%.1f", fabs(tempValue2));

	tempValue = atof(qcresultdata1.pltdata.plt) + atof(qcresultdata.pltdata.plt);
	tempValue2 = atof(qcresultdata1.pltdata.plt) - atof(qcresultdata.pltdata.plt);
	tempValue /= 2;
	sprintf(qcresultdataAve.pltdata.plt, "%.0f", tempValue);
	sprintf(qcresultdataRan.pltdata.plt, "%.0f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.pltdata.mpv) + atof(qcresultdata.pltdata.mpv);
	tempValue2 = atof(qcresultdata1.pltdata.mpv) - atof(qcresultdata.pltdata.mpv);
	tempValue /= 2;
	sprintf(qcresultdataAve.pltdata.mpv, "%.2f", tempValue);
	sprintf(qcresultdataRan.pltdata.mpv, "%.2f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.pltdata.pdw) + atof(qcresultdata.pltdata.pdw);
	tempValue2 = atof(qcresultdata1.pltdata.pdw) - atof(qcresultdata.pltdata.pdw);
	tempValue /= 2;
	sprintf(qcresultdataAve.pltdata.pdw, "%.1f", tempValue);
	sprintf(qcresultdataRan.pltdata.pdw, "%.1f", fabs(tempValue2));
	tempValue = atof(qcresultdata1.pltdata.pct) + atof(qcresultdata.pltdata.pct);
	tempValue2 = atof(qcresultdata1.pltdata.pct) - atof(qcresultdata.pltdata.pct);
	tempValue /= 2;
	sprintf(qcresultdataAve.pltdata.pct, "%.2f", tempValue);
	sprintf(qcresultdataRan.pltdata.pct, "%.2f", fabs(tempValue2));
}



void CQcXrTestView::initQcXrRanData()		//质控测试参数就是26个，没有必要28个，和主测试流程不一样
{
	int 			i = 0;

	//默认字符为""
	qcresultdataRan.row = 0;

	qcresultdataRan.qctype = Controlfile + 48;
	qcresultdataRan.filenum = Controlfile + 48;
	qcresultdataRan.time = 0;
	strcpy(qcresultdataRan.date, "");

	strcpy(qcresultdataRan.wbcdata.wbc, "**.**");

	strcpy(qcresultdataRan.wbcdata.lymp, "**.*");
	strcpy(qcresultdataRan.wbcdata.neup, "**.*");
	strcpy(qcresultdataRan.wbcdata.monop, "*.*");
	strcpy(qcresultdataRan.wbcdata.eosp, "*.*");
	strcpy(qcresultdataRan.wbcdata.basp, "*.*");
	strcpy(qcresultdataRan.wbcdata.alyp, "*.*");
	strcpy(qcresultdataRan.wbcdata.licp, "*.*");

	strcpy(qcresultdataRan.wbcdata.lym, "*.**");
	strcpy(qcresultdataRan.wbcdata.neu, "*.**");
	strcpy(qcresultdataRan.wbcdata.mono, "*.**");
	strcpy(qcresultdataRan.wbcdata.eos, "*.**");
	strcpy(qcresultdataRan.wbcdata.bas, "*.**");
	strcpy(qcresultdataRan.wbcdata.aly, "*.**");
	strcpy(qcresultdataRan.wbcdata.lic, "*.**");
	//RBC
	strcpy(qcresultdataRan.rbcdata.rbc, "*.**");
	strcpy(qcresultdataRan.rbcdata.hgb, "***.*");
	strcpy(qcresultdataRan.rbcdata.hct, "**.*");
	strcpy(qcresultdataRan.rbcdata.mcv, "***.*");
	strcpy(qcresultdataRan.rbcdata.mch, "**.*");
	strcpy(qcresultdataRan.rbcdata.mchc, "***.*");
	strcpy(qcresultdataRan.rbcdata.rdw, "**.*");
	//PLT
	strcpy(qcresultdataRan.pltdata.plt, "***");
	strcpy(qcresultdataRan.pltdata.mpv, "**.**");
	strcpy(qcresultdataRan.pltdata.pdw, "**.*");
	strcpy(qcresultdataRan.pltdata.pct, "**.**");
	//散点图
	for (i = 0; i < MATRIX_DATA_MAX; i++)
		qcresultdataRan.lmnegraph[i] = 1;
	//BASO直方图
	for (i = 0; i < 256; i++)
		qcresultdataRan.basograph[i] = 1;
	//RBC直方图
	for (i = 0; i < 512; i++)
		qcresultdataRan.rbcgraph[i] = 1;
	//PLT直方图
	for (i = 0; i < 256; i++)
		qcresultdataRan.pltgraph[i] = 1;
	//界标
	for (i = 0; i < 9; i++)
		qcresultdataRan.lmneflg[i] = 1;
	qcresultdataRan.basoflg[0] = 1;
	for (i = 0; i < 2; i++)
		qcresultdataRan.rbcflg[i] = 1;
	for (i = 0; i < 2; i++)
		qcresultdataRan.pltflg[i] = 1;
}

void CQcXrTestView::UpdateQcXrTestList1()
{
	USES_CONVERSION;
	//str.Format(_T("%s"), qcresultdata.wbcdata.wbc);
	m_QcXrTestList.SetItemText(0, 1, (CString)qcresultdata.wbcdata.wbc);
	m_QcXrTestList.SetItemText(1, 1, (CString)qcresultdata.wbcdata.lymp);
	m_QcXrTestList.SetItemText(2, 1, (CString)qcresultdata.wbcdata.neup);
	m_QcXrTestList.SetItemText(3, 1, (CString)qcresultdata.wbcdata.monop);
	m_QcXrTestList.SetItemText(4, 1, (CString)qcresultdata.wbcdata.eosp);
	m_QcXrTestList.SetItemText(5, 1, (CString)qcresultdata.wbcdata.basp);
	m_QcXrTestList.SetItemText(6, 1, (CString)qcresultdata.wbcdata.alyp);
	m_QcXrTestList.SetItemText(7, 1, (CString)qcresultdata.wbcdata.licp);
	m_QcXrTestList.SetItemText(8, 1, (CString)qcresultdata.wbcdata.lym);
	m_QcXrTestList.SetItemText(9, 1, (CString)qcresultdata.wbcdata.neu);
	m_QcXrTestList.SetItemText(10, 1, (CString)qcresultdata.wbcdata.mono);
	m_QcXrTestList.SetItemText(11, 1, (CString)qcresultdata.wbcdata.eos);
	m_QcXrTestList.SetItemText(12, 1, (CString)qcresultdata.wbcdata.bas);
	m_QcXrTestList.SetItemText(13, 1, (CString)qcresultdata.wbcdata.aly);
	m_QcXrTestList.SetItemText(14, 1, (CString)qcresultdata.wbcdata.lic);

	m_QcXrTestList.SetItemText(15, 1, (CString)qcresultdata.rbcdata.rbc);
	m_QcXrTestList.SetItemText(16, 1, (CString)qcresultdata.rbcdata.hgb);
	m_QcXrTestList.SetItemText(17, 1, (CString)qcresultdata.rbcdata.hct);
	m_QcXrTestList.SetItemText(18, 1, (CString)qcresultdata.rbcdata.mcv);
	m_QcXrTestList.SetItemText(19, 1, (CString)qcresultdata.rbcdata.mch);
	m_QcXrTestList.SetItemText(20, 1, (CString)qcresultdata.rbcdata.mchc);
	m_QcXrTestList.SetItemText(21, 1, (CString)qcresultdata.rbcdata.rdw);

	m_QcXrTestList.SetItemText(22, 1, (CString)qcresultdata.pltdata.plt);
	m_QcXrTestList.SetItemText(23, 1, (CString)qcresultdata.pltdata.mpv);
	m_QcXrTestList.SetItemText(24, 1, (CString)qcresultdata.pltdata.pdw);
	m_QcXrTestList.SetItemText(25, 1, (CString)qcresultdata.pltdata.pct);

}

void CQcXrTestView::UpdateQcXrTestList2()
{
	USES_CONVERSION;
	//str.Format(_T("%s"), qcresultdata.wbcdata.wbc);
	m_QcXrTestList.SetItemText(0, 2, (CString)qcresultdata.wbcdata.wbc);
	m_QcXrTestList.SetItemText(1, 2, (CString)qcresultdata.wbcdata.lymp);
	m_QcXrTestList.SetItemText(2, 2, (CString)qcresultdata.wbcdata.neup);
	m_QcXrTestList.SetItemText(3, 2, (CString)qcresultdata.wbcdata.monop);
	m_QcXrTestList.SetItemText(4, 2, (CString)qcresultdata.wbcdata.eosp);
	m_QcXrTestList.SetItemText(5, 2, (CString)qcresultdata.wbcdata.basp);
	m_QcXrTestList.SetItemText(6, 2, (CString)qcresultdata.wbcdata.alyp);
	m_QcXrTestList.SetItemText(7, 2, (CString)qcresultdata.wbcdata.licp);
	m_QcXrTestList.SetItemText(8, 2, (CString)qcresultdata.wbcdata.lym);
	m_QcXrTestList.SetItemText(9, 2, (CString)qcresultdata.wbcdata.neu);
	m_QcXrTestList.SetItemText(10, 2, (CString)qcresultdata.wbcdata.mono);
	m_QcXrTestList.SetItemText(11, 2, (CString)qcresultdata.wbcdata.eos);
	m_QcXrTestList.SetItemText(12, 2, (CString)qcresultdata.wbcdata.bas);
	m_QcXrTestList.SetItemText(13, 2, (CString)qcresultdata.wbcdata.aly);
	m_QcXrTestList.SetItemText(14, 2, (CString)qcresultdata.wbcdata.lic);

	m_QcXrTestList.SetItemText(15, 2, (CString)qcresultdata.rbcdata.rbc);
	m_QcXrTestList.SetItemText(16, 2, (CString)qcresultdata.rbcdata.hgb);
	m_QcXrTestList.SetItemText(17, 2, (CString)qcresultdata.rbcdata.hct);
	m_QcXrTestList.SetItemText(18, 2, (CString)qcresultdata.rbcdata.mcv);
	m_QcXrTestList.SetItemText(19, 2, (CString)qcresultdata.rbcdata.mch);
	m_QcXrTestList.SetItemText(20, 2, (CString)qcresultdata.rbcdata.mchc);
	m_QcXrTestList.SetItemText(21, 2, (CString)qcresultdata.rbcdata.rdw);

	m_QcXrTestList.SetItemText(22, 2, (CString)qcresultdata.pltdata.plt);
	m_QcXrTestList.SetItemText(23, 2, (CString)qcresultdata.pltdata.mpv);
	m_QcXrTestList.SetItemText(24, 2, (CString)qcresultdata.pltdata.pdw);
	m_QcXrTestList.SetItemText(25, 2, (CString)qcresultdata.pltdata.pct);

	/*******************************************************************/

	m_QcXrTestList.SetItemText(0, 3, (CString)qcresultdataAve.wbcdata.wbc);
	m_QcXrTestList.SetItemText(1, 3, (CString)qcresultdataAve.wbcdata.lymp);
	m_QcXrTestList.SetItemText(2, 3, (CString)qcresultdataAve.wbcdata.neup);
	m_QcXrTestList.SetItemText(3, 3, (CString)qcresultdataAve.wbcdata.monop);
	m_QcXrTestList.SetItemText(4, 3, (CString)qcresultdataAve.wbcdata.eosp);
	m_QcXrTestList.SetItemText(5, 3, (CString)qcresultdataAve.wbcdata.basp);
	m_QcXrTestList.SetItemText(6, 3, (CString)qcresultdataAve.wbcdata.alyp);
	m_QcXrTestList.SetItemText(7, 3, (CString)qcresultdataAve.wbcdata.licp);
	m_QcXrTestList.SetItemText(8, 3, (CString)qcresultdataAve.wbcdata.lym);
	m_QcXrTestList.SetItemText(9, 3, (CString)qcresultdataAve.wbcdata.neu);
	m_QcXrTestList.SetItemText(10, 3, (CString)qcresultdataAve.wbcdata.mono);
	m_QcXrTestList.SetItemText(11, 3, (CString)qcresultdataAve.wbcdata.eos);
	m_QcXrTestList.SetItemText(12, 3, (CString)qcresultdataAve.wbcdata.bas);
	m_QcXrTestList.SetItemText(13, 3, (CString)qcresultdataAve.wbcdata.aly);
	m_QcXrTestList.SetItemText(14, 3, (CString)qcresultdataAve.wbcdata.lic);

	m_QcXrTestList.SetItemText(15, 3, (CString)qcresultdataAve.rbcdata.rbc);
	m_QcXrTestList.SetItemText(16, 3, (CString)qcresultdataAve.rbcdata.hgb);
	m_QcXrTestList.SetItemText(17, 3, (CString)qcresultdataAve.rbcdata.hct);
	m_QcXrTestList.SetItemText(18, 3, (CString)qcresultdataAve.rbcdata.mcv);
	m_QcXrTestList.SetItemText(19, 3, (CString)qcresultdataAve.rbcdata.mch);
	m_QcXrTestList.SetItemText(20, 3, (CString)qcresultdataAve.rbcdata.mchc);
	m_QcXrTestList.SetItemText(21, 3, (CString)qcresultdataAve.rbcdata.rdw);

	m_QcXrTestList.SetItemText(22, 3, (CString)qcresultdataAve.pltdata.plt);
	m_QcXrTestList.SetItemText(23, 3, (CString)qcresultdataAve.pltdata.mpv);
	m_QcXrTestList.SetItemText(24, 3, (CString)qcresultdataAve.pltdata.pdw);
	m_QcXrTestList.SetItemText(25, 3, (CString)qcresultdataAve.pltdata.pct);

	/***********************************************************************/
	m_QcXrTestList.SetItemText(0, 4, (CString)qcresultdataRan.wbcdata.wbc);
	m_QcXrTestList.SetItemText(1, 4, (CString)qcresultdataRan.wbcdata.lymp);
	m_QcXrTestList.SetItemText(2, 4, (CString)qcresultdataRan.wbcdata.neup);
	m_QcXrTestList.SetItemText(3, 4, (CString)qcresultdataRan.wbcdata.monop);
	m_QcXrTestList.SetItemText(4, 4, (CString)qcresultdataRan.wbcdata.eosp);
	m_QcXrTestList.SetItemText(5, 4, (CString)qcresultdataRan.wbcdata.basp);
	m_QcXrTestList.SetItemText(6, 4, (CString)qcresultdataRan.wbcdata.alyp);
	m_QcXrTestList.SetItemText(7, 4, (CString)qcresultdataRan.wbcdata.licp);
	m_QcXrTestList.SetItemText(8, 4, (CString)qcresultdataRan.wbcdata.lym);
	m_QcXrTestList.SetItemText(9, 4, (CString)qcresultdataRan.wbcdata.neu);
	m_QcXrTestList.SetItemText(10, 4, (CString)qcresultdataRan.wbcdata.mono);
	m_QcXrTestList.SetItemText(11, 4, (CString)qcresultdataRan.wbcdata.eos);
	m_QcXrTestList.SetItemText(12, 4, (CString)qcresultdataRan.wbcdata.bas);
	m_QcXrTestList.SetItemText(13, 4, (CString)qcresultdataRan.wbcdata.aly);
	m_QcXrTestList.SetItemText(14, 4, (CString)qcresultdataRan.wbcdata.lic);

	m_QcXrTestList.SetItemText(15, 4, (CString)qcresultdataRan.rbcdata.rbc);
	m_QcXrTestList.SetItemText(16, 4, (CString)qcresultdataRan.rbcdata.hgb);
	m_QcXrTestList.SetItemText(17, 4, (CString)qcresultdataRan.rbcdata.hct);
	m_QcXrTestList.SetItemText(18, 4, (CString)qcresultdataRan.rbcdata.mcv);
	m_QcXrTestList.SetItemText(19, 4, (CString)qcresultdataRan.rbcdata.mch);
	m_QcXrTestList.SetItemText(20, 4, (CString)qcresultdataRan.rbcdata.mchc);
	m_QcXrTestList.SetItemText(21, 4, (CString)qcresultdataRan.rbcdata.rdw);

	m_QcXrTestList.SetItemText(22, 4, (CString)qcresultdataRan.pltdata.plt);
	m_QcXrTestList.SetItemText(23, 4, (CString)qcresultdataRan.pltdata.mpv);
	m_QcXrTestList.SetItemText(24, 4, (CString)qcresultdataRan.pltdata.pdw);
	m_QcXrTestList.SetItemText(25, 4, (CString)qcresultdataRan.pltdata.pct);



}

//此处尚未做完
void CQcXrTestView::UpdateQcXrTestHeadInfo()
{
	//time(&systime);
	//caltime = localtime(&systime);
	//qcresultdata->time = (caltime->tm_hour) * 10000 + (caltime->tm_min) * 100 + caltime->tm_sec;
	//sprintf(qcresultdata->date, "%04d-%02d-%02d", caltime->tm_year + 1900, caltime->tm_mon + 1, caltime->tm_mday);//mny,20171219
	CString str;;
	str.Format(L"%s", qcresultdataAve.date);
	//str = qcresultdataAve.date;
	SetDlgItemText(IDC_QC_XR_TEST_DATE, (str) );	//此处有问题
	
	str.Format(L"%d", qcresultdataAve.time);
	SetDlgItemText(IDC_QC_XR_TEST_TIME, str);

	
	//SetDlgItemText(IDC_QC_XR_TEST_SEQ, L"");



}