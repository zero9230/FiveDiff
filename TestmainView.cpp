// TestmainView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "TestmainView.h"
#include "PatientResultView2.h"
#include "ResultDetails.h"
//#include "MainFrm.h"
//#include "Includes_app.h"
#include "ThreadAS.h"
#include "Resource.h"
#include "MainFrm.h"

// CTestmainView
extern bool Allow_ASOnLine;
extern bool AS_OnLine;				//自动进样系统与主机建立连接-1(START)，未建立连接-0(OVER)
extern bool ASCur_EN;				//当前测试使能。1有效才能工作。请求血样，否则不请求血样(执行自动维护或提示数据库满，需临时暂停)
doctor_info* CTestmainView::doctordata = NULL;

//开机空白测试数据
bool			StartupBlankTestsflag = FALSE;				//为1时表示目前正在进行开机空白测试，需做两次
char			StartupBlankTestsTimes;		//开机测试进行空白测试的次数<=2
float			StartupBlankTestswbc;
float			StartupBlankTestsrbc;
float			StartupBlankTestsplt;
bool			IsBlankTest = FALSE;

char			studyPara[8][6];		//研究参数:Blasts(%),Blasts(#),LEFT(%),LEFT(#),NRBC(%),NRBC(#),P-LCC(%),P-LCC(#)	//xx22  P-LCC(%),P-LCC(#)暂时没有
int				test = 0;

static unsigned char 	AlertMotorShow;	//电机错误显示为1，其它为0
static unsigned char 	NumOverwashfrequency;	//测试满washfrequency需要自动清洗  满为1，不满为0
static unsigned char 	DataBaseFull;	//数据库满(955-999)  955-999为1，其它为0
static unsigned char 	ReagentEmpty;	//试剂不足为1，其它为0
extern unsigned char graphbu[3500];
IMPLEMENT_DYNCREATE(CTestmainView, CBCGPChartExampleView)



//画图相关宏定义
#define LMNE_LEFT		0
#define LMNE_BOTTOM 	0
#define LMNE_WIDTH		255//540-340  [0,255]->[340,540]
#define LMNE_HEIGHT		255

CTestmainView::CTestmainView()
: CBCGPChartExampleView(CTestmainView::IDD)
{

	BlockErr_Flag;
	i = 0;
	BlockErrStore = 0;
	NumChanged = FALSE;
	//AfxMessageBox(_T("12"));
}

CTestmainView::~CTestmainView()
{
	//KillTimer(SLEEP_TIMER1);
	//KillTimer(ERROR_TIMER);
	//KillTimer(CHECKERR_TIMER);
	//KillTimer(POLL_TIMER);

}
void CTestmainView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, m_resultList);
	DDX_Control(pDX, IDC_LIST1, m_WBCresultList);
	DDX_Control(pDX, IDC_LIST2, m_RBCresultList);
	DDX_Control(pDX, IDC_LIST3, m_PLTresultList);
	DDX_Control(pDX, IDC_CHART, m_LMNEChart);
	DDX_Control(pDX, IDC_CHART1, m_BASOChart);
	DDX_Control(pDX, IDC_CHART2, m_RBCChart);
	DDX_Control(pDX, IDC_CHART3, m_PLTChart);
	//  DDX_Control(pDX, IDC_CHART4, m_ProportionChart);
	DDX_Control(pDX, IDC_CHART4, m_PieChart);
	DDX_Control(pDX, IDC_LIST8, m_WBCFlagListBox);
	DDX_Control(pDX, IDC_LIST4, m_RETresultList);
	DDX_Control(pDX, IDC_LIST5, m_CRPresultList);
	DDX_Control(pDX, IDC_LIST9, m_RBCFlagListBox);
	DDX_Control(pDX, IDC_LIST10, m_PLTFlagListBox);
	DDX_Control(pDX, IDC_LIST11, m_RETFlagListBox);
	//AfxMessageBox(_T("56"));
	DDX_Control(pDX, IDC_COMBO_SEX, m_sexcombo);
	DDX_Control(pDX, IDC_COMBO_DOCTOR, m_doctorcombo);
	DDX_Control(pDX, IDC_TESTMAIN_NUMBER, TestMain_number);
}

BEGIN_MESSAGE_MAP(CTestmainView, CBCGPChartExampleView)

	//	ON_WM_ERASEBKGND()
	//	ON_STN_CLICKED(IDC_CHART4, &CTestmainView::OnStnClickedChart4)
	//ON_MESSAGE(WM_MEASUREITEM + WM_REFLECT_BASE, &CTestmainView::MeasureItem)
	//ON_WM_MEASUREITEM_REFLECT()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_MAINBLANKTEST, &CTestmainView::OnMainblanktest)
	ON_MESSAGE(WM_DISABLEVIEW, &CTestmainView::OnDisableview)
	ON_MESSAGE(WM_ENABLEVIEW, &CTestmainView::OnEnableview)
	ON_WM_TIMER()
	ON_MESSAGE(WM_BLOCKER, &CTestmainView::OnBlocker)
	ON_MESSAGE(WM_ACKSPI, &CTestmainView::OnAckspi)
	ON_MESSAGE(WM_AUTOCLEAN, &CTestmainView::OnAutoclean)
	ON_MESSAGE(WM_CONCENCLEAN, &CTestmainView::OnConcenclean)
	ON_MESSAGE(WM_MAINTEST, &CTestmainView::OnMaintest)

	ON_MESSAGE(WM_GETBARCODE, &CTestmainView::OnGetbarcode)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTestmainView::OnLvnItemchangedList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CTestmainView::OnLvnItemchangedList2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST4, &CTestmainView::OnLvnItemchangedList4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST5, &CTestmainView::OnLvnItemchangedList5)
	ON_EN_CHANGE(IDC_TESTMAIN_BARCODE, &CTestmainView::OnEnChangeTestmainBarcode)
	//ON_BN_CLICKED(IDC_BUTTON1, &CTestmainView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestmainView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestmainView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestmainView::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestmainView 诊断

#ifdef _DEBUG
void CTestmainView::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestmainView::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
	//AfxMessageBox(_T("90"));
}
#endif
#endif //_DEBUG

/**************************/
// CTestmainView 消息处理程序
void CTestmainView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();
	// TODO:  在此添加专用代码和/或调用基类
	loadDoctors();
	InitControl();
	InitData();
	InitForm(&sampledata);
	PrintChart(&sampledata);
	InitWBCFlagBox();

	DWORD   dw1, dw2;
	if (systemcfg3.structure == 3)
	{
		systemcfg2.PcConMode = 2;
		CreateThread(NULL, 0, CreateAutoSampleThread, NULL, 0, &dw1);
		Allow_ASOnLine = TRUE;
		Sleep(100);
	}
	else
	{
		if (1 == systemcfg2.PcConMode)//如果是串口，则打开串口，否则不打开串口
		{
			long baudrate;
			if (systemcfg.com.baudrate == 0)
				baudrate = 9600;
			else if (systemcfg.com.baudrate == 1)
				baudrate = 19200;
			else if (systemcfg.com.baudrate == 2)
				baudrate = 57600;
			else if (systemcfg.com.baudrate == 3)
				baudrate = 115200;
			else//异常情况
				baudrate = 115200;

			/*if ((ret = OpenCom(0, "/dev/ttyS1", baudrate)) == -1)
			return -1;*/
			//----------------------------------------
			//联机软件线程
			CreateThread(NULL, 0, ThreadPC, NULL, 0, &dw2);    		//创建联机软件线程
		}
	}

	DWORD TestmainThreadId1;
	HANDLE   hThread;
	TestmainEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	hThread = CreateThread(NULL, 0, BarcodeCheck, LPVOID(this), 0, &TestmainThreadId1);

	if (hThread == NULL)
	{
		MessageBox(L"CreateThread   failed.", L"main", MB_OK);
	}
	else
	{
		//OutputDebugString(L"prepare   post   message\r\n");
		Sleep(1000);//等待线程创建好了   
	}

	//CreateThread(NULL, 0, ThreadB2, NULL, 0, &dw2);
	//Sleep(100);
	//AfxMessageBox(_T("1011"));

	DWORD TestmainThreadId2;
	HANDLE   hThread2;
	TestmainEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	hThread2 = CreateThread(NULL, 0, SwitchStateCheck, LPVOID(this), 0, &TestmainThreadId2);

	if (hThread2 == NULL)
	{
		MessageBox(L"CreateThread SwitchStateCheck failed.", L"main", MB_OK);
	}
	else
	{
		//OutputDebugString(L"prepare   post   message\r\n");
		Sleep(1000);//等待线程创建好了   
	}

}

int CTestmainView::loadDoctors()
{
	CString			zStatement;
	CString			filename;
	_ConnectionPtr  m_pDB;
	_RecordsetPtr	m_pRs;

	filename.Format(_T("appdata.accdb"));
	//打开数据库
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
	{
		return -1;
	}
	//根据编号获取病人信息表对应记录
	CString numofrs;
	//numofrs = pThisResult->numofrs[pThisResult->nownum];
	CString select_doctordata = _T("select * from doctordata");// where number = '") + numofrs + "';";
	//CString select_sampledata = _T("select * from sampledata'");// where number = '") + numofrs + "';";
	_variant_t var;
	ExeSql(m_pDB, m_pRs, select_doctordata);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空");
			return FALSE;
		}
		while (!m_pRs->adoEOF)
		{


			/*******************************************/
			//显示信息，第一个参数为行，第二个参数为列，第三个参数为内容

			var = m_pRs->GetCollect("doct_name");
			CString strName;
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			//	m_PatientResultList.SetItemText(i, 4, strName);
			m_doctorcombo.AddString(strName);

			i++;
			m_pRs->MoveNext();
		}
		//	ThisResult2.totalnums = m_PatientResultList.GetItemCount();
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}

	//loaddoctor(m_pDB, m_pRs, *doctordata);
	//根据编号获取样本数据表的对应记录
	CloseDataBase(m_pDB, m_pRs);
}

void CTestmainView::InitControl()
{
	m_sexcombo.AddString(L"男");
	m_sexcombo.AddString(L"女");
	m_sexcombo.AddString(L"空");

}

//表格批量初始化，调用其余的表格初始化函数
BOOL CTestmainView::InitForm(sample_info* psampledata)
{
	//InitWBCForm(psampledata);
	InitRBCForm(psampledata);
	InitPLTForm(psampledata);
	InitCRPForm();
	InitRETForm();
	//AfxMessageBox(_T("1112"));
	TestMain_number.EnableWindow(false);
	return TRUE;

}

BOOL CTestmainView::UpdateForm(sample_info* psampledata)
{
	UpdateWBCForm(psampledata);
	UpdateRBCForm(psampledata);
	UpdatePLTForm(psampledata);
	UpdateRETForm();
	UpdateCRPForm();
	return TRUE;
}

BOOL CTestmainView::InitWBCForm(sample_info* psampledata)
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_WBCresultList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_WBCresultList.SetExtendedStyle(m_WBCresultList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_WBCresultList.SetRowHeigt(20);

	m_WBCresultList.DeleteAllItems();//清空列表刷新

	m_WBCresultList.DeleteColumn(0);
	m_WBCresultList.DeleteColumn(1);
	m_WBCresultList.DeleteColumn(2);
	m_WBCresultList.DeleteColumn(3);
	m_WBCresultList.DeleteColumn(4);
	m_WBCresultList.DeleteColumn(5);

	// 为WBC列表视图控件添加四列   
	m_WBCresultList.InsertColumn(0, _T("WBC项目"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_WBCresultList.InsertColumn(1, _T("数据"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_WBCresultList.InsertColumn(2, _T("单位"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_WBCresultList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_WBCresultList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_WBCresultList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	uchar type = systemcfg.range.type;
	//uchar LL, UL;

	CString itemName[] = { _T("WBC"), _T("LYM%"), _T("NEU%"), _T("MONO%"), _T("EOS%"),
		_T("BASO%"), _T("ALY%"), _T("LIC%"), _T("LYM%"), _T("NEU#"),
		_T("MONO#"), _T("EOS#"), _T("BASO#"), _T("ALY#"), _T("LIC#") };
	CString unit[] = { _T("10^9/L"), _T("%"), _T("%"), _T("%"), _T("%"),
		_T("%"), _T("%"), _T("%"), _T("10^9/L"), _T("10^9/L"),
		_T("10^9/L"), _T("10^9/L"), _T("10^9/L"), _T("10^9/L"), _T("10^9/L") };
	int itemCount = 15;
	//CString showbuffer;
	////showbuffer.Format(L"%0.1f", atof(psampledata->pltdata.plt)/10);
	//showbuffer.Format(L"%0.1f", atof(psampledata->pltdata.plt));
	CString showbuffer;

	// 在WBC列表视图控件中插入列表项，并设置列表子项文本   
	for (int i = 0; i < itemCount; i++){
		m_WBCresultList.InsertItem(i, itemName[i]);
		m_WBCresultList.SetItemText(i, 2, unit[i]);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i]);
		m_WBCresultList.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + 28]);
		m_WBCresultList.SetItemText(i, 4, showbuffer);
		//m_WBCresultList.SetItemText(i, 5, _T("Flagi"));
		m_WBCresultList.SetItemText(i, 5, _T(" "));

	}

	/*
	// 在WBC列表视图控件中插入列表项，并设置列表子项文本
	m_WBCresultList.InsertItem(0, _T("WBC"));
	m_WBCresultList.SetItemText(0, 2, _T("10^9/L"));
	m_WBCresultList.InsertItem(1, _T("LYM%"));
	m_WBCresultList.SetItemText(1, 2, _T("%"));
	m_WBCresultList.InsertItem(2, _T("NEU%"));
	m_WBCresultList.SetItemText(2, 2, _T("%"));
	m_WBCresultList.InsertItem(3, _T("MONO%"));
	m_WBCresultList.SetItemText(3, 2, _T("%"));
	m_WBCresultList.InsertItem(4, _T("EOS%"));
	m_WBCresultList.SetItemText(4, 2, _T("%"));
	m_WBCresultList.InsertItem(5, _T("BASO%"));
	m_WBCresultList.SetItemText(5, 2, _T("%"));
	m_WBCresultList.InsertItem(6, _T("ALY%"));
	m_WBCresultList.SetItemText(6, 2, _T("%"));
	m_WBCresultList.InsertItem(7, _T("LIC%"));
	m_WBCresultList.SetItemText(7, 2, _T("%"));
	m_WBCresultList.InsertItem(8, _T("LYM%"));
	m_WBCresultList.SetItemText(8, 2, _T("10^9/L"));
	m_WBCresultList.InsertItem(9, _T("NEU#"));
	m_WBCresultList.SetItemText(9, 2, _T("10^9/L"));
	m_WBCresultList.InsertItem(10, _T("MONO#"));
	m_WBCresultList.SetItemText(10, 2, _T("10^9/L"));
	m_WBCresultList.InsertItem(11, _T("EOS#"));
	m_WBCresultList.SetItemText(11, 2, _T("10^9/L"));
	m_WBCresultList.InsertItem(12, _T("BASO#"));
	m_WBCresultList.SetItemText(12, 2, _T("10^9/L"));
	m_WBCresultList.InsertItem(13, _T("ALY#"));
	m_WBCresultList.SetItemText(13, 2, _T("10^9/L"));
	m_WBCresultList.InsertItem(14, _T("LIC#"));
	m_WBCresultList.SetItemText(14, 2, _T("10^9/L"));
	*/
	m_WBCresultList.SetItemText(0, 1, (CString)psampledata->wbcdata.wbc);
	//MessageBox((CString)psampledata->wbcdata.wbc);
	m_WBCresultList.SetItemText(1, 1, (CString)psampledata->wbcdata.lymp);
	m_WBCresultList.SetItemText(2, 1, (CString)psampledata->wbcdata.neup);
	m_WBCresultList.SetItemText(3, 1, (CString)psampledata->wbcdata.monop);
	m_WBCresultList.SetItemText(4, 1, (CString)psampledata->wbcdata.eosp);
	m_WBCresultList.SetItemText(5, 1, (CString)psampledata->wbcdata.basp);
	m_WBCresultList.SetItemText(6, 1, (CString)psampledata->wbcdata.alyp);
	m_WBCresultList.SetItemText(7, 1, (CString)psampledata->wbcdata.licp);
	m_WBCresultList.SetItemText(8, 1, (CString)psampledata->wbcdata.lym);
	m_WBCresultList.SetItemText(9, 1, (CString)psampledata->wbcdata.neu);
	m_WBCresultList.SetItemText(10, 1, (CString)psampledata->wbcdata.mono);
	m_WBCresultList.SetItemText(11, 1, (CString)psampledata->wbcdata.eos);
	m_WBCresultList.SetItemText(12, 1, (CString)psampledata->wbcdata.bas);
	m_WBCresultList.SetItemText(13, 1, (CString)psampledata->wbcdata.aly);
	m_WBCresultList.SetItemText(14, 1, (CString)psampledata->wbcdata.lic);
	//AfxMessageBox(_T("1213"));
	return TRUE;
}
BOOL CTestmainView::UpdateWBCForm(sample_info* psampledata)
{
	uchar type = systemcfg.range.type;

	m_WBCresultList.SetItemText(0, 1, ChartsToCString((psampledata->wbcdata.wbc), sizeof(psampledata->wbcdata.wbc) / sizeof(char)));
	if (atof(psampledata->wbcdata.wbc)<systemcfg.range.normal[type][0])
		m_WBCresultList.SetItemText(0, 5, _T("L"));
	else if (atof(psampledata->wbcdata.wbc)>systemcfg.range.normal[type][0 + 28])
		m_WBCresultList.SetItemText(0, 5, _T("H"));

	m_WBCresultList.SetItemText(1, 1, ChartsToCString((psampledata->wbcdata.lymp), sizeof(psampledata->wbcdata.lymp) / sizeof(char)));
	if (atof(psampledata->wbcdata.lymp)<systemcfg.range.normal[type][1])
		m_WBCresultList.SetItemText(1, 5, _T("L"));
	else if (atof(psampledata->wbcdata.lymp)>systemcfg.range.normal[type][1 + 28])
		m_WBCresultList.SetItemText(1, 5, _T("H"));

	m_WBCresultList.SetItemText(2, 1, ChartsToCString((psampledata->wbcdata.neup), sizeof(psampledata->wbcdata.neup) / sizeof(char)));
	if (atof(psampledata->wbcdata.neup)<systemcfg.range.normal[type][2])
		m_WBCresultList.SetItemText(2, 5, _T("L"));
	else if (atof(psampledata->wbcdata.neup)>systemcfg.range.normal[type][2 + 28])
		m_WBCresultList.SetItemText(2, 5, _T("H"));

	m_WBCresultList.SetItemText(3, 1, ChartsToCString((psampledata->wbcdata.monop), sizeof(psampledata->wbcdata.monop) / sizeof(char)));
	if (atof(psampledata->wbcdata.monop)<systemcfg.range.normal[type][3])
		m_WBCresultList.SetItemText(3, 5, _T("L"));
	else if (atof(psampledata->wbcdata.monop)>systemcfg.range.normal[type][3 + 28])
		m_WBCresultList.SetItemText(3, 5, _T("H"));

	m_WBCresultList.SetItemText(4, 1, ChartsToCString((psampledata->wbcdata.eosp), sizeof(psampledata->wbcdata.eosp) / sizeof(char)));
	if (atof(psampledata->wbcdata.eosp)<systemcfg.range.normal[type][4])
		m_WBCresultList.SetItemText(4, 5, _T("L"));
	else if (atof(psampledata->wbcdata.eosp)>systemcfg.range.normal[type][4 + 28])
		m_WBCresultList.SetItemText(4, 5, _T("H"));

	m_WBCresultList.SetItemText(5, 1, ChartsToCString((psampledata->wbcdata.basp), sizeof(psampledata->wbcdata.basp) / sizeof(char)));
	if (atof(psampledata->wbcdata.basp)<systemcfg.range.normal[type][5])
		m_WBCresultList.SetItemText(5, 5, _T("L"));
	else if (atof(psampledata->wbcdata.basp)>systemcfg.range.normal[type][5 + 28])
		m_WBCresultList.SetItemText(5, 5, _T("H"));

	m_WBCresultList.SetItemText(6, 1, ChartsToCString((psampledata->wbcdata.alyp), sizeof(psampledata->wbcdata.alyp) / sizeof(char)));
	if (atof(psampledata->wbcdata.alyp)<systemcfg.range.normal[type][6])
		m_WBCresultList.SetItemText(6, 5, _T("L"));
	else if (atof(psampledata->wbcdata.alyp)>systemcfg.range.normal[type][6 + 28])
		m_WBCresultList.SetItemText(6, 5, _T("H"));

	m_WBCresultList.SetItemText(7, 1, ChartsToCString((psampledata->wbcdata.licp), sizeof(psampledata->wbcdata.licp) / sizeof(char)));
	if (atof(psampledata->wbcdata.licp)<systemcfg.range.normal[type][7])
		m_WBCresultList.SetItemText(7, 5, _T("L"));
	else if (atof(psampledata->wbcdata.licp)>systemcfg.range.normal[type][7 + 28])
		m_WBCresultList.SetItemText(7, 5, _T("H"));

	m_WBCresultList.SetItemText(8, 1, ChartsToCString((psampledata->wbcdata.lym), sizeof(psampledata->wbcdata.lym) / sizeof(char)));
	if (atof(psampledata->wbcdata.lym)<systemcfg.range.normal[type][8])
		m_WBCresultList.SetItemText(8, 5, _T("L"));
	else if (atof(psampledata->wbcdata.lym)>systemcfg.range.normal[type][8 + 28])
		m_WBCresultList.SetItemText(8, 5, _T("H"));

	m_WBCresultList.SetItemText(9, 1, ChartsToCString((psampledata->wbcdata.neu), sizeof(psampledata->wbcdata.neu) / sizeof(char)));
	if (atof(psampledata->wbcdata.neu)<systemcfg.range.normal[type][9])
		m_WBCresultList.SetItemText(9, 5, _T("L"));
	else if (atof(psampledata->wbcdata.neu)>systemcfg.range.normal[type][9 + 28])
		m_WBCresultList.SetItemText(9, 5, _T("H"));

	m_WBCresultList.SetItemText(10, 1, ChartsToCString((psampledata->wbcdata.mono), sizeof(psampledata->wbcdata.mono) / sizeof(char)));
	if (atof(psampledata->wbcdata.mono)<systemcfg.range.normal[type][10])
		m_WBCresultList.SetItemText(10, 5, _T("L"));
	else if (atof(psampledata->wbcdata.mono)>systemcfg.range.normal[type][10 + 28])
		m_WBCresultList.SetItemText(10, 5, _T("H"));

	m_WBCresultList.SetItemText(11, 1, ChartsToCString((psampledata->wbcdata.eos), sizeof(psampledata->wbcdata.eos) / sizeof(char)));
	if (atof(psampledata->wbcdata.eos)<systemcfg.range.normal[type][11])
		m_WBCresultList.SetItemText(11, 5, _T("L"));
	else if (atof(psampledata->wbcdata.eos)>systemcfg.range.normal[type][11 + 28])
		m_WBCresultList.SetItemText(11, 5, _T("H"));

	m_WBCresultList.SetItemText(12, 1, ChartsToCString((psampledata->wbcdata.bas), sizeof(psampledata->wbcdata.bas) / sizeof(char)));
	if (atof(psampledata->wbcdata.bas)<systemcfg.range.normal[type][12])
		m_WBCresultList.SetItemText(12, 5, _T("L"));
	else if (atof(psampledata->wbcdata.bas)>systemcfg.range.normal[type][12 + 28])
		m_WBCresultList.SetItemText(12, 5, _T("H"));

	m_WBCresultList.SetItemText(13, 1, ChartsToCString((psampledata->wbcdata.aly), sizeof(psampledata->wbcdata.aly) / sizeof(char)));
	if (atof(psampledata->wbcdata.aly)<systemcfg.range.normal[type][13])
		m_WBCresultList.SetItemText(13, 5, _T("L"));
	else if (atof(psampledata->wbcdata.aly)>systemcfg.range.normal[type][13 + 28])
		m_WBCresultList.SetItemText(13, 5, _T("H"));

	m_WBCresultList.SetItemText(14, 1, ChartsToCString((psampledata->wbcdata.lic), sizeof(psampledata->wbcdata.lic) / sizeof(char)));
	if (atof(psampledata->wbcdata.lic)<systemcfg.range.normal[type][14])
		m_WBCresultList.SetItemText(14, 5, _T("L"));
	else if (atof(psampledata->wbcdata.lic)>systemcfg.range.normal[type][14 + 28])
		m_WBCresultList.SetItemText(14, 5, _T("H"));

	return TRUE;
}

BOOL CTestmainView::InitRBCForm(sample_info* psampledata)
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_RBCresultList.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	m_RBCresultList.SetExtendedStyle(m_RBCresultList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_RBCresultList.SetRowHeigt(20);

	m_RBCresultList.DeleteAllItems();//清空列表刷新
	m_RBCresultList.DeleteColumn(0);
	m_RBCresultList.DeleteColumn(1);
	m_RBCresultList.DeleteColumn(2);
	m_RBCresultList.DeleteColumn(3);
	m_RBCresultList.DeleteColumn(4);
	m_RBCresultList.DeleteColumn(5);
	// 为RBC列表视图控件添加四列  

	m_RBCresultList.InsertColumn(0, _T("RBC项目"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_RBCresultList.InsertColumn(1, _T("数据"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_RBCresultList.InsertColumn(2, _T("单位"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_RBCresultList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_RBCresultList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_RBCresultList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	CString itemNames[] = { _T("RBC"), _T("HGB"), _T("HCT"), _T("MCV"),
		_T("MCH"), _T("MCHC"), _T("RDW-CV"), _T("RDW-SD") };
	CString unit[] = { _T("10^12/L"), _T("g/L"), _T("%"), _T("fL"),
		_T("pg"), _T("g/L"), _T("%"), _T("fL") };

	uchar type = systemcfg.range.type;
	CString showbuffer;
	int preCount = 15;
	int rbcNum = 8;

	// 在RBC列表视图控件中插入列表项，并设置列表子项文本

	//m_RBCresultList.InsertItem(0, _T("RBC"));
	//m_RBCresultList.SetItemText(0, 2, _T("10^12/L"));
	//m_RBCresultList.InsertItem(1, _T("HGB"));
	//m_RBCresultList.SetItemText(1, 2, _T("g/L"));
	//m_RBCresultList.InsertItem(2, _T("HCT"));
	//m_RBCresultList.SetItemText(2, 2, _T("%"));
	//m_RBCresultList.InsertItem(3, _T("MCV"));
	//m_RBCresultList.SetItemText(3, 2, _T("fL"));
	//m_RBCresultList.InsertItem(4, _T("MCH"));
	//m_RBCresultList.SetItemText(4, 2, _T("pg"));
	//m_RBCresultList.InsertItem(5, _T("MCHC"));
	//m_RBCresultList.SetItemText(5, 2, _T("g/L"));
	//m_RBCresultList.InsertItem(6, _T("RDW-CV"));
	//m_RBCresultList.SetItemText(6, 2, _T("%"));
	//m_RBCresultList.InsertItem(7, _T("RDW-SD"));
	//m_RBCresultList.SetItemText(7, 2, _T("fL"));
	//
	for (int i = 0; i < rbcNum; i++){
		m_RBCresultList.InsertItem(i, itemNames[i]);
		m_RBCresultList.SetItemText(i, 2, unit[i]);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + preCount]);
		m_RBCresultList.SetItemText(i, 3, showbuffer);
		showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][i + preCount + 28]);
		m_RBCresultList.SetItemText(i, 4, showbuffer);
		m_RBCresultList.SetItemText(i, 5, _T(" "));
	}

	m_RBCresultList.SetItemText(0, 1, (CString)psampledata->rbcdata.rbc);
	m_RBCresultList.SetItemText(1, 1, (CString)psampledata->rbcdata.hgb);
	m_RBCresultList.SetItemText(2, 1, (CString)psampledata->rbcdata.hct);
	m_RBCresultList.SetItemText(3, 1, (CString)psampledata->rbcdata.mcv);
	m_RBCresultList.SetItemText(4, 1, (CString)psampledata->rbcdata.mch);
	m_RBCresultList.SetItemText(5, 1, (CString)psampledata->rbcdata.mchc);
	m_RBCresultList.SetItemText(6, 1, (CString)psampledata->rbcdata.rdwcv);
	m_RBCresultList.SetItemText(7, 1, (CString)psampledata->rbcdata.rdwsd);
	//AfxMessageBox(_T("1314"));
	return TRUE;
}
BOOL CTestmainView::UpdateRBCForm(sample_info* psampledata)
{
	uchar type = systemcfg.range.type;
	int wbcNum = 15;
	m_RBCresultList.SetItemText(0, 1, ChartsToCString((psampledata->rbcdata.rbc), sizeof(psampledata->rbcdata.rbc) / sizeof(char)));
	if (atof(psampledata->rbcdata.rbc)<systemcfg.range.normal[type][0 + wbcNum])
		m_RBCresultList.SetItemText(0, 5, _T("L"));
	else if (atof(psampledata->rbcdata.rbc)>systemcfg.range.normal[type][0 + wbcNum + 28])
		m_RBCresultList.SetItemText(0, 5, _T("H"));

	m_RBCresultList.SetItemText(1, 1, ChartsToCString((psampledata->rbcdata.hgb), sizeof(psampledata->rbcdata.hgb) / sizeof(char)));
	if (atof(psampledata->rbcdata.hgb)<systemcfg.range.normal[type][1 + wbcNum])
		m_RBCresultList.SetItemText(1, 5, _T("L"));
	else if (atof(psampledata->rbcdata.hgb)>systemcfg.range.normal[type][1 + wbcNum + 28])
		m_RBCresultList.SetItemText(1, 5, _T("H"));

	m_RBCresultList.SetItemText(2, 1, ChartsToCString((psampledata->rbcdata.hct), sizeof(psampledata->rbcdata.hct) / sizeof(char)));
	if (atof(psampledata->rbcdata.hct)<systemcfg.range.normal[type][2 + wbcNum])
		m_RBCresultList.SetItemText(2, 5, _T("L"));
	else if (atof(psampledata->rbcdata.hct)>systemcfg.range.normal[type][2 + wbcNum + 28])
		m_RBCresultList.SetItemText(2, 5, _T("H"));

	m_RBCresultList.SetItemText(3, 1, ChartsToCString((psampledata->rbcdata.mcv), sizeof(psampledata->rbcdata.mcv) / sizeof(char)));
	if (atof(psampledata->rbcdata.mcv)<systemcfg.range.normal[type][3 + wbcNum])
		m_RBCresultList.SetItemText(3, 5, _T("L"));
	else if (atof(psampledata->rbcdata.mcv)>systemcfg.range.normal[type][3 + wbcNum + 28])
		m_RBCresultList.SetItemText(3, 5, _T("H"));

	m_RBCresultList.SetItemText(4, 1, ChartsToCString((psampledata->rbcdata.mch), sizeof(psampledata->rbcdata.mch) / sizeof(char)));
	if (atof(psampledata->rbcdata.mch)<systemcfg.range.normal[type][4 + wbcNum])
		m_RBCresultList.SetItemText(4, 5, _T("L"));
	else if (atof(psampledata->rbcdata.mch)>systemcfg.range.normal[type][4 + wbcNum + 28])
		m_RBCresultList.SetItemText(4, 5, _T("H"));

	m_RBCresultList.SetItemText(5, 1, ChartsToCString((psampledata->rbcdata.mchc), sizeof(psampledata->rbcdata.mchc) / sizeof(char)));
	if (atof(psampledata->rbcdata.mchc)<systemcfg.range.normal[type][5 + wbcNum])
		m_RBCresultList.SetItemText(5, 5, _T("L"));
	else if (atof(psampledata->rbcdata.mchc)>systemcfg.range.normal[type][5 + wbcNum + 28])
		m_RBCresultList.SetItemText(5, 5, _T("H"));

	m_RBCresultList.SetItemText(6, 1, ChartsToCString((psampledata->rbcdata.rdwcv), sizeof(psampledata->rbcdata.rdwcv) / sizeof(char)));
	if (atof(psampledata->rbcdata.rdwcv)<systemcfg.range.normal[type][6 + wbcNum])
		m_RBCresultList.SetItemText(6, 5, _T("L"));
	else if (atof(psampledata->rbcdata.rdwcv)>systemcfg.range.normal[type][6 + wbcNum + 28])
		m_RBCresultList.SetItemText(6, 5, _T("H"));
	//MessageBox((CString)psampledata->rbcdata.rdwcv);
	m_RBCresultList.SetItemText(7, 1, ChartsToCString((psampledata->rbcdata.rdwsd), sizeof(psampledata->rbcdata.rdwsd) / sizeof(char)));
	if (atof(psampledata->rbcdata.rdwsd)<systemcfg.range.normal[type][7 + wbcNum])
		m_RBCresultList.SetItemText(7, 5, _T("L"));
	else if (atof(psampledata->rbcdata.rdwsd)>systemcfg.range.normal[type][7 + wbcNum + 28])
		m_RBCresultList.SetItemText(7, 5, _T("H"));

	return TRUE;
}

BOOL CTestmainView::InitPLTForm(sample_info* psampledata)
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_PLTresultList.GetClientRect(&rect);
	m_PLTresultList.SetRowHeigt(20);

	m_PLTresultList.DeleteAllItems();//清空列表刷新

	m_PLTresultList.DeleteColumn(0);
	m_PLTresultList.DeleteColumn(1);
	m_PLTresultList.DeleteColumn(2);
	m_PLTresultList.DeleteColumn(3);
	m_PLTresultList.DeleteColumn(4);
	m_PLTresultList.DeleteColumn(5);

	// 为列表视图控件添加全行选中和栅格风格   
	m_PLTresultList.SetExtendedStyle(m_PLTresultList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	// 为PLT列表视图控件添加四列
	m_PLTresultList.InsertColumn(0, _T("PLT项目"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_PLTresultList.InsertColumn(1, _T("数据"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_PLTresultList.InsertColumn(2, _T("单位"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_PLTresultList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_PLTresultList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_PLTresultList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	CString showbuffer;
	uchar type = systemcfg.range.type;

	// 在PLT列表视图控件中插入列表项，并设置列表子项文本
	m_PLTresultList.InsertItem(0, _T("PLT"));
	m_PLTresultList.SetItemText(0, 2, _T("10^9/L"));
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][23]);
	m_PLTresultList.SetItemText(0, 3, showbuffer);
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][23 + 28]);
	m_PLTresultList.SetItemText(0, 4, showbuffer);
	m_PLTresultList.SetItemText(0, 5, _T(" "));

	m_PLTresultList.InsertItem(1, _T("MPV"));
	m_PLTresultList.SetItemText(1, 2, _T("fL"));
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][24]);
	m_PLTresultList.SetItemText(1, 3, showbuffer);
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][24 + 28]);
	m_PLTresultList.SetItemText(1, 4, showbuffer);
	m_PLTresultList.SetItemText(1, 5, _T(" "));

	m_PLTresultList.InsertItem(2, _T("PDW"));
	m_PLTresultList.SetItemText(2, 2, _T("fL"));
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][25]);
	m_PLTresultList.SetItemText(2, 3, showbuffer);
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][25 + 28]);
	m_PLTresultList.SetItemText(2, 4, showbuffer);
	m_PLTresultList.SetItemText(2, 5, _T(" "));

	m_PLTresultList.InsertItem(3, _T("PCT"));
	m_PLTresultList.SetItemText(3, 2, _T("%"));
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][26]);
	m_PLTresultList.SetItemText(3, 3, showbuffer);
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][26 + 28]);
	m_PLTresultList.SetItemText(3, 4, showbuffer);
	m_PLTresultList.SetItemText(3, 5, _T(" "));

	m_PLTresultList.InsertItem(4, _T("P-LCR"));
	m_PLTresultList.SetItemText(4, 2, _T("%"));
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][27]);
	m_PLTresultList.SetItemText(4, 3, showbuffer);
	showbuffer.Format(L"%0.1f", systemcfg.range.normal[type][27 + 28]);
	m_PLTresultList.SetItemText(4, 4, showbuffer);
	m_PLTresultList.SetItemText(4, 5, _T(" "));

	//CString showbuffer;
	//showbuffer.Format(L"%0.1f", atof(psampledata->pltdata.plt)/10);
	showbuffer.Format(L"%0.1f", atof(psampledata->pltdata.plt));
	m_PLTresultList.SetItemText(0, 1, showbuffer);
	m_PLTresultList.SetItemText(1, 1, (CString)psampledata->pltdata.mpv);
	m_PLTresultList.SetItemText(2, 1, (CString)psampledata->pltdata.pdw);
	m_PLTresultList.SetItemText(3, 1, (CString)psampledata->pltdata.pct);
	m_PLTresultList.SetItemText(4, 1, (CString)psampledata->pltdata.plcr);

	//AfxMessageBox(_T("1415"));
	return TRUE;
}

//**//**待添加flag判断
BOOL CTestmainView::UpdatePLTForm(sample_info* psampledata)
{
	uchar type = systemcfg.range.type;
	int preNum = 23
		;
	m_PLTresultList.SetItemText(0, 1, ChartsToCString((psampledata->pltdata.plt), sizeof(psampledata->pltdata.plt) / sizeof(char)));
	if (atof(psampledata->pltdata.plt)<systemcfg.range.normal[type][0 + preNum])
		m_PLTresultList.SetItemText(0, 5, _T("L"));
	else if (atof(psampledata->pltdata.plt)>systemcfg.range.normal[type][0 + preNum + 28])
		m_PLTresultList.SetItemText(0, 5, _T("H"));

	m_PLTresultList.SetItemText(1, 1, ChartsToCString((psampledata->pltdata.mpv), sizeof(psampledata->pltdata.mpv) / sizeof(char)));
	if (atof(psampledata->pltdata.mpv)<systemcfg.range.normal[type][1 + preNum])
		m_PLTresultList.SetItemText(1, 5, _T("L"));
	else if (atof(psampledata->pltdata.mpv)>systemcfg.range.normal[type][1 + preNum + 28])
		m_PLTresultList.SetItemText(1, 5, _T("H"));

	m_PLTresultList.SetItemText(2, 1, ChartsToCString((psampledata->pltdata.pdw), sizeof(psampledata->pltdata.pdw) / sizeof(char)));
	if (atof(psampledata->pltdata.pdw)<systemcfg.range.normal[type][2 + preNum])
		m_PLTresultList.SetItemText(2, 5, _T("L"));
	else if (atof(psampledata->pltdata.pdw)>systemcfg.range.normal[type][2 + preNum + 28])
		m_PLTresultList.SetItemText(2, 5, _T("H"));

	m_PLTresultList.SetItemText(3, 1, ChartsToCString((psampledata->pltdata.pct), sizeof(psampledata->pltdata.pct) / sizeof(char)));
	if (atof(psampledata->pltdata.pct)<systemcfg.range.normal[type][3 + preNum])
		m_PLTresultList.SetItemText(3, 5, _T("L"));
	else if (atof(psampledata->pltdata.pct)>systemcfg.range.normal[type][3 + preNum] + 28)
		m_PLTresultList.SetItemText(3, 5, _T("H"));

	m_PLTresultList.SetItemText(4, 1, ChartsToCString((psampledata->pltdata.plcr), sizeof(psampledata->pltdata.plcr) / sizeof(char)));
	if (atof(psampledata->pltdata.plcr)<systemcfg.range.normal[type][4 + preNum])
		m_PLTresultList.SetItemText(4, 5, _T("L"));
	else if (atof(psampledata->pltdata.plcr)>systemcfg.range.normal[type][4 + preNum + 28])
		m_PLTresultList.SetItemText(4, 5, _T("H"));

	return TRUE;
}
BOOL CTestmainView::InitRETForm()
{
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小   
	m_RETresultList.GetClientRect(&rect);
	m_RETresultList.SetRowHeigt(20);
	// 为列表视图控件添加全行选中和栅格风格   
	m_RETresultList.SetExtendedStyle(m_RETresultList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_RETresultList.DeleteAllItems();//清空列表刷新
	m_RETresultList.DeleteColumn(0);
	m_RETresultList.DeleteColumn(1);
	m_RETresultList.DeleteColumn(2);
	m_RETresultList.DeleteColumn(3);
	m_RETresultList.DeleteColumn(4);
	m_RETresultList.DeleteColumn(5);

	// 为RET列表视图控件添加四列
	m_RETresultList.InsertColumn(0, _T("RET项目"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_RETresultList.InsertColumn(1, _T("数据"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_RETresultList.InsertColumn(2, _T("单位"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_RETresultList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_RETresultList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_RETresultList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// 在RET列表视图控件中插入列表项，并设置列表子项文本
	m_RETresultList.InsertItem(0, _T("RET%"));
	m_RETresultList.SetItemText(0, 2, _T("10^9/L"));
	m_RETresultList.InsertItem(1, _T("RET#"));
	m_RETresultList.SetItemText(1, 2, _T("fL"));
	m_RETresultList.InsertItem(2, _T("RETL"));
	m_RETresultList.SetItemText(2, 2, _T("fL"));
	m_RETresultList.InsertItem(3, _T("RETM"));
	m_RETresultList.SetItemText(3, 2, _T("%"));
	m_RETresultList.InsertItem(4, _T("RETH"));
	m_RETresultList.SetItemText(4, 2, _T("%"));
	m_RETresultList.InsertItem(5, _T("MFI"));
	m_RETresultList.SetItemText(5, 2, _T("%"));
	m_RETresultList.InsertItem(6, _T("IMM"));
	m_RETresultList.SetItemText(6, 2, _T("%"));
	m_RETresultList.InsertItem(7, _T("MRV"));
	m_RETresultList.SetItemText(7, 2, _T("fL"));
	m_RETresultList.InsertItem(8, _T("IRF"));
	m_RETresultList.SetItemText(8, 2, _T("%"));
	m_RETresultList.InsertItem(9, _T("CRC"));
	m_RETresultList.SetItemText(9, 2, _T("%"));
	//AfxMessageBox(_T("1516"));
	return TRUE;
}
BOOL CTestmainView::UpdateRETForm()
{
	return TRUE;
}
BOOL CTestmainView::InitCRPForm()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_CRPresultList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_CRPresultList.SetExtendedStyle(m_CRPresultList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_CRPresultList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_CRPresultList.SetRowHeigt(20);

	m_CRPresultList.DeleteAllItems();//清空列表刷新
	m_CRPresultList.DeleteColumn(0);
	m_CRPresultList.DeleteColumn(1);
	m_CRPresultList.DeleteColumn(2);
	m_CRPresultList.DeleteColumn(3);
	m_CRPresultList.DeleteColumn(4);
	m_CRPresultList.DeleteColumn(5);

	// 为CRP列表视图控件添加四列
	m_CRPresultList.InsertColumn(0, _T("CRP项目"), LVCFMT_CENTER, rect.Width() / 6, 0);
	m_CRPresultList.InsertColumn(1, _T("数据"), LVCFMT_CENTER, rect.Width() / 6, 1);
	m_CRPresultList.InsertColumn(2, _T("单位"), LVCFMT_CENTER, rect.Width() / 6, 2);
	m_CRPresultList.InsertColumn(3, _T("LL"), LVCFMT_CENTER, rect.Width() / 6, 3);
	m_CRPresultList.InsertColumn(4, _T("UL"), LVCFMT_CENTER, rect.Width() / 6, 4);
	m_CRPresultList.InsertColumn(5, _T("Flag"), LVCFMT_CENTER, rect.Width() / 6, 5);

	// 在CRP列表视图控件中插入列表项，并设置列表子项文本
	m_CRPresultList.InsertItem(0, _T("CRP"));
	m_CRPresultList.SetItemText(0, 2, _T("10^9/L"));

	//AfxMessageBox(_T("1617"));
	return TRUE;
}
BOOL CTestmainView::UpdateCRPForm()
{
	return TRUE;
}

void CTestmainView::PrintChart(sample_info *psampledata)
{
	//PrintLMNEChart(psampledata);
	PrintBASOChart(psampledata);
	PrintRBCChart(psampledata);
	PrintPLTChart(psampledata);
	PrintPieChart();
	//AfxMessageBox(_T("1718"));
}

//////////////////////////////////////////////////////////////////////////////////////////	
//Description:	动态初始化LMNE散点图各区域界标值						  	//
//Called by: LmneAnalysis																	//
//Params illustration:																		//
//Data Access:																			//
//Other:																					//
//*History:																				//
//	(1)Created:20150121																	//
//////////////////////////////////////////////////////////////////////////////////////////

void CTestmainView::Init_B_LMNE(float	coefficient, B_LMNE* p_blmne)
{
	float		coe_rtoabs;

	//Resistance
	p_blmne->X_NOL = (uchar)systemcfg.range.thresholds[NoL] * coefficient;
	p_blmne->X_NON = (uchar)systemcfg.range.thresholds[NoN] * coefficient;
	p_blmne->X_LL = (uchar)systemcfg.range.thresholds[LL] * coefficient;
	p_blmne->X_LN = (uchar)systemcfg.range.thresholds[LN] * coefficient;
	p_blmne->X_AL = (uchar)systemcfg.range.thresholds[AL] * coefficient;
	p_blmne->X_LMN = (uchar)systemcfg.range.thresholds[LMN] * coefficient;
	p_blmne->X_LMU = (uchar)systemcfg.range.thresholds[LMU] * coefficient;
	p_blmne->X_MN = (uchar)systemcfg.range.thresholds[MN] * coefficient;
	p_blmne->X_LMD = (uchar)systemcfg.range.thresholds[LMD] * coefficient;

	p_blmne->X_NOE = (uchar)systemcfg.range.thresholds[NoE] * 1.0;
	p_blmne->X_RM = (uchar)systemcfg.range.thresholds[RM] * 1.0;
	p_blmne->X_RN = (uchar)systemcfg.range.thresholds[RN] * 1.0;

	coe_rtoabs = coefficient * 1.0;
	//Absorbance
	p_blmne->Y_NL = (uchar)systemcfg.range.thresholds[NL] * coe_rtoabs;
	p_blmne->Y_RMN = (uchar)systemcfg.range.thresholds[RMN] * coe_rtoabs;
	p_blmne->Y_NE = (uchar)systemcfg.range.thresholds[NE] * coe_rtoabs;
}
/***********************************************************
*Function:
*Description:	画散点图
*Called by:
*Params illustration:
*Data Access:	读全局变量
*History:	create	lgq		2010.12.31
************************************************************/
void CTestmainView::LmneGraphPaint(sample_info *psampledata, const unsigned char rangetype, CDC &MemDC)
{
	TRACE(L"Hello World");
	unsigned int i;
	unsigned char res = 0, scatter = 0;	//电阻抗信号，光散射信号
	unsigned char rangeFlag = ' ', doubtFlag = ' ';
	char showbuff[9] = { 0 };
	unsigned char graphbuff[MATRIX_DATA_MAX] = { 0 };

	B_LMNE		m_blmne;
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_CHART);
	pWnd->GetClientRect(&rect); // 获取控件屏幕坐标
	CDC* pDC = pWnd->GetDC();
	//CDC MemDC;
	//	CBitmap bmp;
	//	MemDC.CreateCompatibleDC(pDC);
	//	bmp.CreateCompatibleBitmap(&MemDC,rect.Width(),rect.Height());
	//	MemDC.SelectObject(&bmp);
	//	MemDC.FillSolidRect(rect,RGB(255,255,255));

	if ((*psampledata).coeoflmne > 1.3)
		psampledata->coeoflmne = 1.3;
	else if ((*psampledata).coeoflmne < 0.7)
		psampledata->coeoflmne = 0.7;

	Init_B_LMNE((*psampledata).coeoflmne, &m_blmne);
	//SetTextColor(hdc, COLOR_black);
	if ((*psampledata).wbcdata.wbc[0] == '*')//未做测试
	{
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.lymp);
		//TextOut(hdc, 85, 35 + 18, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.neup);
		//TextOut(hdc, 85, 35 + 36, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.monop);
		//TextOut(hdc, 85, 35 + 54, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.eosp);
		//TextOut(hdc, 85, 35 + 72, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.alyp);
		//TextOut(hdc, 85, 35 + 108, showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.licp);
		//TextOut(hdc, 85, 35 + 126, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.lym));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.lym);
		//TextOut(hdc, 85, 35 + 144, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.neu));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.neu);
		//TextOut(hdc, 85, 35 + 162, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.mono));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.mono);
		//TextOut(hdc, 85, 35 + 180, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.eos));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.eos);
		//TextOut(hdc, 85, 35 + 198, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.aly));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.aly);
		//TextOut(hdc, 85, 35 + 234, showbuff);

		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.lic));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.lic);
		//TextOut(hdc, 85, 35 + 252, showbuff);
	}
	else//做了测试
	{
		if (1 == (*psampledata).flag_wrp[0])
			doubtFlag = ' ';
		else if (2 == (*psampledata).flag_wrp[0])
			doubtFlag = '?';
		else
			doubtFlag = '*';
		//判断数据越界，用rangeflag标记
		//LYMP
		if (atof((*psampledata).wbcdata.lymp) < systemcfg.range.normal[rangetype][LYMP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.lymp) > systemcfg.range.normal[rangetype][LYMP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.lymp);
		m_WBCresultList.SetItemText(LYMP, 3, (CString)showbuff);

		//NEUP
		if (atof((*psampledata).wbcdata.neup) < systemcfg.range.normal[rangetype][NEUP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.neup) > systemcfg.range.normal[rangetype][NEUP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.neup);
		m_WBCresultList.SetItemText(NEUP, 3, (CString)showbuff);
		//MONOP
		if (atof((*psampledata).wbcdata.monop) < systemcfg.range.normal[rangetype][MONOP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.monop) > systemcfg.range.normal[rangetype][MONOP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.monop);
		m_WBCresultList.SetItemText(MONOP, 3, (CString)showbuff);
		//EOSP
		if (atof((*psampledata).wbcdata.eosp) < systemcfg.range.normal[rangetype][EOSP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.eosp) > systemcfg.range.normal[rangetype][EOSP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.eosp);
		m_WBCresultList.SetItemText(EOSP, 3, (CString)showbuff);
		//ALYP
		if (atof((*psampledata).wbcdata.alyp) < systemcfg.range.normal[rangetype][ALYP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.alyp) > systemcfg.range.normal[rangetype][ALYP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.alyp);
		m_WBCresultList.SetItemText(ALYP, 3, (CString)showbuff);
		//LICP
		if (atof((*psampledata).wbcdata.licp) < systemcfg.range.normal[rangetype][LICP])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.licp) > systemcfg.range.normal[rangetype][LICP + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.licp);
		m_WBCresultList.SetItemText(LICP, 3, (CString)showbuff);

		//LYM
		if (atof((*psampledata).wbcdata.lym) < systemcfg.range.normal[rangetype][LYMS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.lym) > systemcfg.range.normal[rangetype][LYMS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.lym));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.lym);
		m_WBCresultList.SetItemText(LYMS, 3, (CString)showbuff);
		//NEU
		if (atof((*psampledata).wbcdata.neu) < systemcfg.range.normal[rangetype][NEUS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.neu) > systemcfg.range.normal[rangetype][NEUS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.neu));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.neu);
		m_WBCresultList.SetItemText(NEUS, 3, (CString)showbuff);
		//MONO
		if (atof((*psampledata).wbcdata.mono) < systemcfg.range.normal[rangetype][MONOS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.mono) > systemcfg.range.normal[rangetype][MONOS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.mono));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.mono);
		m_WBCresultList.SetItemText(MONOS, 3, (CString)showbuff);
		//EOS
		if (atof((*psampledata).wbcdata.eos) < systemcfg.range.normal[rangetype][EOSS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.eos) > systemcfg.range.normal[rangetype][EOSS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.eos));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.eos);
		m_WBCresultList.SetItemText(EOSS, 3, (CString)showbuff);
		//ALY
		if (atof((*psampledata).wbcdata.aly) < systemcfg.range.normal[rangetype][ALYS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.aly) > systemcfg.range.normal[rangetype][ALYS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.aly));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.aly);
		m_WBCresultList.SetItemText(ALYS, 3, (CString)showbuff);
		//LIC
		if (atof((*psampledata).wbcdata.lic) < systemcfg.range.normal[rangetype][LICS])
			rangeFlag = 'L';
		else if (atof((*psampledata).wbcdata.lic) > systemcfg.range.normal[rangetype][LICS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.lic));
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.lic);
		m_WBCresultList.SetItemText(LICS, 3, (CString)showbuff);
	}

	//SetTextColor(hdc, COLOR_red);

	UpdateWBClmneFlagBox(psampledata);
	//------------------------------------------------
	//LMNE散点图		
	//将对0x00的特殊处理去除,恢复原始数据
	for (i = 0; i < MATRIX_DATA_MAX - 1; i++){
		graphbuff[i] = (*psampledata).lmnegraph[i] - 1;
		//	graphbu[i] = graphbuff[i];
	}

	for (i = 0; i < MATRIX_POINT_MAX - 1; i++)
	{
		res = graphbuff[(i << 1)];
		scatter = graphbuff[(i << 1) + 1];
		if (scatter >= m_blmne.Y_NE)
		{
			if (res < m_blmne.X_NOE)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			else
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(255, 0, 0));
		}
		else if (scatter >= m_blmne.Y_RMN)
		{
			if (res < m_blmne.X_NON)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			else if (res < m_blmne.X_LN)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			else if (m_blmne.X_RN)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			else
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
		}
		else if (scatter >= m_blmne.Y_NL)
		{
			if (res < m_blmne.X_NON)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			else if (res < m_blmne.X_LN)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			else if (res < m_blmne.X_LMN)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
			else if (res < m_blmne.X_MN)
			{
				if ((res - m_blmne.X_LMN)*(m_blmne.Y_RMN - m_blmne.Y_NL) < (m_blmne.X_MN - m_blmne.X_LMN)*(scatter - m_blmne.Y_NL))
					MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 250, 0));
				else
					MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			}
			else if (res < m_blmne.X_RM)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			else
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
		}
		else
		{
			if (res < m_blmne.X_NOL)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 0));
			else if (res < m_blmne.X_LL)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 255));
			else if (res< m_blmne.X_AL)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 255));
			else if (res < m_blmne.X_LMU)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(0, 0, 255));
			else if (res < m_blmne.X_LMD)
			{
				if ((m_blmne.X_LMD - res*m_blmne.Y_NL) >(m_blmne.X_LMD - m_blmne.X_LMU)*scatter)
					MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter * LMNE_HEIGHT / 255, RGB(0, 0, 255));
				else
					MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter* LMNE_HEIGHT / 255, RGB(230, 30, 70));
			}
			else if (res < m_blmne.X_RM)
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
			else
				MemDC.SetPixel(res*LMNE_WIDTH / 255 + LMNE_LEFT, LMNE_BOTTOM - scatter*LMNE_HEIGHT / 255, RGB(230, 30, 70));
		}
	}
	//	pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);
	//MemDC.DeleteDC();
	//bmp.DeleteObject();
	//MemDC.MoveTo(0, -100);
	//MemDC.LineTo(100, 200);
}
void CTestmainView::PrintLMNEChart(sample_info *psampledata)//绘制LMNE的内框线
{
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_CHART);
	pWnd->GetClientRect(&rect); // 获取控件屏幕坐标
	CDC* pDC = pWnd->GetDC();

	CDC MemDC;
	CBitmap bmp;
	MemDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, 267, 282);
	MemDC.SelectObject(&bmp);

	MemDC.FillSolidRect(rect.left, rect.top, 267, 282, RGB(255, 255, 255));
	//	MemDC.MoveTo(0, 0);
	//	MemDC.LineTo(100, 100);
	MemDC.SetViewportOrg(0, 280 - rect.Height());



	MemDC.SetViewportOrg(0, 0);
	MemDC.SelectStockObject(WHITE_BRUSH);
	MemDC.Rectangle(rect);
	CPen cpen, pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	MemDC.SelectObject(&pen);
	MemDC.SetViewportOrg(0, 0);
	MemDC.LineTo(0, rect.Height());
	MemDC.LineTo(rect.Width(), rect.Height());
	MemDC.LineTo(rect.Width(), 0);
	MemDC.LineTo(0, 0);
	pen.~CPen();

	pen.CreatePen(PS_SOLID, 1, RGB(96, 96, 96));
	MemDC.SelectObject(&pen);
	MemDC.SetViewportOrg(0, 280);
	MemDC.LineTo(255, 0);
	MemDC.LineTo(255, -255);
	MemDC.LineTo(0, -255);
	MemDC.LineTo(0, 0);
	MemDC.TextOut(0, -280, "LMNE:");

	//MemDC.MoveTo(255, 0);
	//MemDC.LineTo(265, 0);
	//MemDC.LineTo(265, -255);
	//MemDC.LineTo(255, -255);

	unsigned char i;

	int 		x1, x2, y1, y2;
	B_LMNE		m_blmne;
	double		coe_w = LMNE_WIDTH / 255.0;
	double		coe_h = LMNE_HEIGHT / 255.0;

	if ((*psampledata).coeoflmne > 1.3)
		psampledata->coeoflmne = 1.3;
	else if ((*psampledata).coeoflmne < 0.7)
		psampledata->coeoflmne = 0.7;
	Init_B_LMNE((*psampledata).coeoflmne, &m_blmne);
	//------------------------------------------------
	//LMNE
	//line 1 (NOL,0)->(NOL,NL)
	x1 = m_blmne.X_NOL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 2 (NON,NL)->(NON,NE)
	x1 = m_blmne.X_NON * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);
	//line 3 (LL,0)->(LL,NL)
	x1 = m_blmne.X_LL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		MemDC.MoveTo(x1, y2 + i * 3);
		MemDC.LineTo(x1, y2 + i * 3 + 3);
		i += 2;	// ....  ....  ....
	}
	//line 4 (LN,NL)->(LN,NE)
	x1 = m_blmne.X_LN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		MemDC.MoveTo(x1, y2 + i * 3);
		MemDC.LineTo(x1, y2 + i * 3 + 3);
		i += 2;
	}

	//line 5 (NOE,NE)->(NOE,256)
	x1 = m_blmne.X_NOE*coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NE*coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - LMNE_HEIGHT;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 6/10 (LMN,NL)->(MN,RMN)
	x1 = m_blmne.X_LMN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_MN * coe_w + LMNE_LEFT;
	y2 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 7 (AL,0)->(AL,NL)
	x1 = m_blmne.X_AL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NL*coe_h;
	for (i = 0; i * 3 < y1 - y2;)
	{
		MemDC.MoveTo(x1, y2 + i * 3);
		MemDC.LineTo(x1, y2 + i * 3 + 3);
		i += 2;
	}

	//line 8/9 (LMU,NL)->(LMD,0)
	x1 = m_blmne.X_LMU * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_LMD * coe_w + LMNE_LEFT;
	y2 = LMNE_BOTTOM;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 11 (RM,0)->(RM,RMN)
	x1 = m_blmne.X_RM * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 12 (RN,RMN)->(RN,NE)
	x1 = m_blmne.X_RN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	x2 = x1;
	y2 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 13 (NOL,NL)->(LMU,NL)
	x1 = m_blmne.X_NOL * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NL * coe_h;
	x2 = m_blmne.X_LMU * coe_w + LMNE_LEFT;
	y2 = y1;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 14 (MN,RMN)->(256,RMN)
	x1 = m_blmne.X_MN * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_RMN * coe_h;
	x2 = LMNE_WIDTH + LMNE_LEFT;
	y2 = y1;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	//line 15 (NON,NE)->(256,NE)
	x1 = m_blmne.X_NON * coe_w + LMNE_LEFT;
	y1 = LMNE_BOTTOM - m_blmne.Y_NE * coe_h;
	x2 = LMNE_WIDTH + LMNE_LEFT;
	y2 = y1;
	MemDC.MoveTo(x1, y1);
	MemDC.LineTo(x2, y2);

	if (sampledata.mode == WHOLEDIFF || sampledata.mode == DILUENTDIFF)
		LmneGraphPaint(&sampledata, patientdata.rangetype, MemDC);

	MemDC.SetViewportOrg(0, 0);
	pDC->BitBlt(0, rect.Height() - 280, 267, 282, &MemDC, 0, 0, SRCCOPY);
	MemDC.DeleteDC();
	bmp.DeleteObject();
	GetDlgItem(IDC_CHART)->EnableWindow(FALSE);
	//pDC->MoveTo(rect.left, rect.top);
	//pDC->LineTo(rect.right, rect.top);
	//pDC->LineTo(rect.right, rect.bottom);
	//pDC->LineTo(rect.left, rect.bottom);
	//pDC->LineTo(rect.left, rect.top);
}
void CTestmainView::UpdatePrintChart(sample_info *psampledata)
{
	UpdateData();
	OnPaint();
	UpdatePrintBASOChart(psampledata, patientdata.rangetype);
	UpdatePrintRBCChart(psampledata, patientdata.rangetype);
	UpdatePrintPLTChart(psampledata, patientdata.rangetype);
	UpdatePrintPieChart();
}

void CTestmainView::PrintBASOChart(sample_info *psampledata)
{
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };


	//------------------------------------------------
	//BASO直方图
	CBCGPChartVisualObject* pChart = m_BASOChart.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartArea, BCGP_CT_SIMPLE);
	pChart->SetChartTitle(_T("BASO"));
	pChart->ShowChartTitle(TRUE, TRUE);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->SetCurveType(BCGPChartFormatSeries::CCT_SPLINE);
	pChart->SetColors((CBCGPChartTheme::ChartTheme)3);//0:蓝色；1：青色；2：墨色；3：绿色；4：天蓝色；5：橙黄；6：淡红； 7：black and yellow ；8：红色......

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));

	//将对0x00的特殊处理去除
	for (i = 0; i < 255; i++)	//255存的是结束标志，里边内容无需显示
		graphbuff[i] = (psampledata->basograph[i] - 1);

	//横坐标[0,204]，204不显示。去掉一些点，每五个元素去掉中间一个点
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	SetDefaultLineWidth();
	SetObjectColors();

	pChart->SetSeriesShadow();

	//AfxMessageBox(_T("2021"));

}

void CTestmainView::UpdatePrintBASOChart(sample_info *psampledata, const unsigned char rangetype)
{
	UpdateData();
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };
	uchar 		rangeFlag = ' ', doubtFlag = ' ';
	char 		showbuff[9 + 1] = { 0 };	//PLT***->**.*(单位:10^4uL)，多了一个字符长度

	if ((*psampledata).wbcdata.wbc[0] == '*')//未做测试
	{
		if (systemcfg.unitWBC == 2)
			sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.wbc));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.wbc);
		m_WBCresultList.SetItemText(WBCS - WBCS, 3, (CString)showbuff);

		//5DIFF模式下才显示
		if (systemcfg.mode == 0 || systemcfg.mode == 2)
		{
			sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.basp);
			m_WBCresultList.SetItemText(BASOP - WBCS, 3, (CString)showbuff);

			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%s%.1f", "   ", 10 * atof((*psampledata).wbcdata.bas));
			else
				sprintf(showbuff, "%s%s", "   ", (*psampledata).wbcdata.bas);
			m_WBCresultList.SetItemText(BASOS - WBCS, 3, (CString)showbuff);
		}
	}
	else//做了测试
	{
		if (1 == (*psampledata).flag_wrp[0])
			doubtFlag = ' ';
		else if (2 == (*psampledata).flag_wrp[0])
			doubtFlag = '?';
		else
			doubtFlag = '*';

		//WBC
		if (atof((*psampledata).wbcdata.wbc) < 0.5)//线性范围下限不显示'?'
		{
			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%c%c %.1f", 'L', 'L', 10 * atof((*psampledata).wbcdata.wbc));
			else
				sprintf(showbuff, "%c%c %s", 'L', 'L', (*psampledata).wbcdata.wbc);
		}
		else if (atof((*psampledata).wbcdata.wbc) > 80)//线性范围上限不显示'?'
		{
			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%c%c %.1f", 'H', 'H', 10 * atof((*psampledata).wbcdata.wbc));
			else
				sprintf(showbuff, "%c%c %s", 'H', 'H', (*psampledata).wbcdata.wbc);
		}
		else
		{
			if (atof((*psampledata).wbcdata.wbc) < systemcfg.range.normal[rangetype][WBCS])
				rangeFlag = 'L';
			else if (atof((*psampledata).wbcdata.wbc) > systemcfg.range.normal[rangetype][WBCS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.wbc));
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.wbc);
		}
		m_WBCresultList.SetItemText(WBCS - WBCS, 3, (CString)showbuff);

		if (systemcfg.mode == 0 || systemcfg.mode == 2)      //5DIFF模式下才显示
		{
			//BASOP
			if (atof((*psampledata).wbcdata.basp) < systemcfg.range.normal[rangetype][BASOP])
				rangeFlag = 'L';
			else if (atof((*psampledata).wbcdata.basp) > systemcfg.range.normal[rangetype][BASOP + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.basp);
			m_WBCresultList.SetItemText(BASOP - WBCS, 3, (CString)showbuff);
			//BASO
			if (atof((*psampledata).wbcdata.bas) < systemcfg.range.normal[rangetype][BASOS])
				rangeFlag = 'L';
			else if (atof((*psampledata).wbcdata.bas) > systemcfg.range.normal[rangetype][BASOS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitWBC == 2)
				sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, 10 * atof((*psampledata).wbcdata.bas));
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).wbcdata.bas);
			m_WBCresultList.SetItemText(BASOS - WBCS, 3, (CString)showbuff);
		}
	}
	UpdateWBCBasoFlagBox(psampledata);
	//------------------------------------------------
	//BASO直方图
	CBCGPChartVisualObject* pChart = m_BASOChart.GetChart();
	ASSERT_VALID(pChart);
	//CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));

	int num = pChart->GetSeriesCount();
	CBCGPChartSeries* pSeries1 = pChart->GetSeries(num - 1);
	pSeries1->RemoveAllDataPoints();
	//将对0x00的特殊处理去除
	for (i = 0; i < 255; i++)	//255存的是结束标志，里边内容无需显示
		graphbuff[i] = (psampledata->basograph[i] - 1);

	//横坐标[0,204]，204不显示。去掉一些点，每五个元素去掉中间一个点
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	SetDefaultLineWidth();
	SetObjectColors();
	pChart->SetSeriesShadow();
	pChart->Redraw();

}

void CTestmainView::PrintRBCChart(sample_info *psampledata)
{
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_RBCChart.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartArea, BCGP_CT_SIMPLE);
	pChart->SetChartTitle(_T("RBC"));
	pChart->ShowChartTitle(TRUE, TRUE);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->SetCurveType(BCGPChartFormatSeries::CCT_SPLINE);
	pChart->SetColors((CBCGPChartTheme::ChartTheme)8);//0:蓝色；1：青色；2：墨色；3：绿色；4：天蓝色；5：橙黄；6：淡红； 7：black and yellow ；8：红色......
	//pChart->SetChartFillColor(const CBCGPBrush& 0);
	CBCGPChartSeries* pSeries1 = pChart->CreateSeries("RBC");

	COleDateTime today = COleDateTime::GetCurrentTime();

	for (i = 0; i < 255; i++)	//其实经过纵坐标压缩放大处理后，计数值已经小于RBC_HEIGHT<255了，所以其实rbcgraph高字节存的都是0
		graphbuff[i] = ((psampledata->rbcgraph[(i << 1) + 1] - 1) << 8) + psampledata->rbcgraph[i << 1] - 1;

	//横坐标[0,204]，204不显示。去掉一些点，每五个元素去掉中间一个点
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}
	pChart->Redraw();

}

void CTestmainView::UpdatePrintRBCChart(sample_info *psampledata, const unsigned char rangetype)
{
	UpdateData();
	unsigned short int i;
	uchar 		rangeFlag = ' ', doubtFlag = ' ';
	char 		showbuff[9 + 1] = { 0 };	//PLT***->**.*(单位:10^4uL)，多了一个字符长度

	if ((*psampledata).rbcdata.rbc[0] == '*')//未做测试
	{
		if (systemcfg.unitRBC == 2)
			sprintf(showbuff, "%s%.0f", "   ", 100 * atof((*psampledata).rbcdata.rbc));
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).rbcdata.rbc);
		m_RBCresultList.SetItemText(RBCS - RBCS, 3, (CString)showbuff);

		if (systemcfg.unitHGB == 1)
			sprintf(showbuff, "%s%.2f", "   ", atof((*psampledata).rbcdata.hgb) / 10);
		else if (systemcfg.unitHGB == 2)
			sprintf(showbuff, "%s%.2f", "   ", atof((*psampledata).rbcdata.hgb) / 68);	//68=68000/1000(血红蛋白的相对分子质量，好几处用到68)    68000 FDparam
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).rbcdata.hgb);
		m_RBCresultList.SetItemText(HGBS - RBCS, 3, (CString)showbuff);

		sprintf(showbuff, "%s%s", "   ", (*psampledata).rbcdata.hct);
		m_RBCresultList.SetItemText(HCTS - RBCS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).rbcdata.mcv);
		m_RBCresultList.SetItemText(MCVS - RBCS, 3, (CString)showbuff);

		if (systemcfg.unitMCH == 1)
			sprintf(showbuff, "%s%.2f", "   ", atof((*psampledata).rbcdata.mch) / 68);
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).rbcdata.mch);
		m_RBCresultList.SetItemText(MCHS - RBCS, 3, (CString)showbuff);

		if (systemcfg.unitMCHC == 1)
			sprintf(showbuff, "%s%.2f", "   ", atof((*psampledata).rbcdata.mchc) / 10);
		else if (systemcfg.unitMCHC == 2)
			sprintf(showbuff, "%s%.2f", "   ", atof((*psampledata).rbcdata.mchc) / 68);
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).rbcdata.mchc);
		m_RBCresultList.SetItemText(MCHCS - RBCS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).rbcdata.rdwcv);
		m_RBCresultList.SetItemText(RDWCVS - RBCS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).rbcdata.rdwsd);
		m_RBCresultList.SetItemText(RDWSDS - RBCS, 3, (CString)showbuff);
	}
	else//做了测试
	{
		//if(1 == count_rbc_flag)
		if (1 == (*psampledata).flag_wrp[1])
			doubtFlag = ' ';
		//else if(2 == count_rbc_flag)
		else if (2 == (*psampledata).flag_wrp[1])
			doubtFlag = '?';
		else
			doubtFlag = '*';

		//RBC
		if (atof((*psampledata).rbcdata.rbc) < 0.2)
		{
			if (systemcfg.unitRBC == 2)
				sprintf(showbuff, "%c%c %.0f", 'L', 'L', 100 * atof((*psampledata).rbcdata.rbc));
			else
				sprintf(showbuff, "%c%c %s", 'L', 'L', (*psampledata).rbcdata.rbc);
		}
		else if (atof((*psampledata).rbcdata.rbc) > 7.5)
		{
			if (systemcfg.unitRBC == 2)
				sprintf(showbuff, "%c%c %.0f", 'H', 'H', 100 * atof((*psampledata).rbcdata.rbc));
			else
				sprintf(showbuff, "%c%c %s", 'H', 'H', (*psampledata).rbcdata.rbc);
		}
		else
		{
			if (atof((*psampledata).rbcdata.rbc) < systemcfg.range.normal[rangetype][RBCS])
				rangeFlag = 'L';
			else if (atof((*psampledata).rbcdata.rbc) > systemcfg.range.normal[rangetype][RBCS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitRBC == 2)
				sprintf(showbuff, "%c%c %.0f", rangeFlag, doubtFlag, 100 * atof((*psampledata).rbcdata.rbc));
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).rbcdata.rbc);
		}
		m_RBCresultList.SetItemText(RBCS - RBCS, 3, (CString)showbuff);
		//HGB
		if (atof((*psampledata).rbcdata.hgb) < 25)
		{
			if (systemcfg.unitHGB == 1)
				sprintf(showbuff, "%c%c %.2f", 'L', 'L', atof((*psampledata).rbcdata.hgb) / 10);
			else if (systemcfg.unitHGB == 2)
				sprintf(showbuff, "%c%c %.2f", 'L', 'L', atof((*psampledata).rbcdata.hgb) / 68);
			else
				sprintf(showbuff, "%c%c %s", 'L', 'L', (*psampledata).rbcdata.hgb);
		}
		else if (atof((*psampledata).rbcdata.hgb) > 230)
		{
			if (systemcfg.unitHGB == 1)
				sprintf(showbuff, "%c%c %.2f", 'H', 'H', atof((*psampledata).rbcdata.hgb) / 10);
			else if (systemcfg.unitHGB == 2)
				sprintf(showbuff, "%c%c %.2f", 'H', 'H', atof((*psampledata).rbcdata.hgb) / 68);
			else
				sprintf(showbuff, "%c%c %s", 'H', 'H', (*psampledata).rbcdata.hgb);
		}
		else
		{
			if (atof((*psampledata).rbcdata.hgb) < systemcfg.range.normal[rangetype][HGBS])
				rangeFlag = 'L';
			else if (atof((*psampledata).rbcdata.hgb) > systemcfg.range.normal[rangetype][HGBS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitHGB == 1)
				sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*psampledata).rbcdata.hgb) / 10);
			else if (systemcfg.unitHGB == 2)
				sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*psampledata).rbcdata.hgb) / 68);
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).rbcdata.hgb);
		}
		m_RBCresultList.SetItemText(HGBS - RBCS, 3, (CString)showbuff);
		//HCT
		if (atof((*psampledata).rbcdata.hct) < 11.6)
		{
			sprintf(showbuff, "%c%c %s", 'L', 'L', (*psampledata).rbcdata.hct);
		}
		else if (atof((*psampledata).rbcdata.hct) > 55)
		{
			sprintf(showbuff, "%c%c %s", 'H', 'H', (*psampledata).rbcdata.hct);
		}
		else
		{
			if (atof((*psampledata).rbcdata.hct) < systemcfg.range.normal[rangetype][HCTS])
				rangeFlag = 'L';
			else if (atof((*psampledata).rbcdata.hct) > systemcfg.range.normal[rangetype][HCTS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).rbcdata.hct);
		}
		m_RBCresultList.SetItemText(HCTS - RBCS, 3, (CString)showbuff);
		//MCV
		if (atof((*psampledata).rbcdata.mcv) < systemcfg.range.normal[rangetype][MCVS])
			rangeFlag = 'L';
		else if (atof((*psampledata).rbcdata.mcv) > systemcfg.range.normal[rangetype][MCVS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).rbcdata.mcv);
		m_RBCresultList.SetItemText(MCVS - RBCS, 3, (CString)showbuff);
		//MCH
		if (atof((*psampledata).rbcdata.mch) < systemcfg.range.normal[rangetype][MCHS])
			rangeFlag = 'L';
		else if (atof((*psampledata).rbcdata.mch) > systemcfg.range.normal[rangetype][MCHS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitMCH == 1)
			sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*psampledata).rbcdata.mch) / 68);
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).rbcdata.mch);
		m_RBCresultList.SetItemText(MCHS - RBCS, 3, (CString)showbuff);
		//MCHC
		if (atof((*psampledata).rbcdata.mchc) < systemcfg.range.normal[rangetype][MCHCS])
			rangeFlag = 'L';
		else if (atof((*psampledata).rbcdata.mchc) > systemcfg.range.normal[rangetype][MCHCS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		if (systemcfg.unitMCHC == 1)
			sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*psampledata).rbcdata.mchc) / 10);
		else if (systemcfg.unitMCHC == 2)
			sprintf(showbuff, "%c%c %.2f", rangeFlag, doubtFlag, atof((*psampledata).rbcdata.mchc) / 68);
		else
			sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).rbcdata.mchc);
		m_RBCresultList.SetItemText(MCHCS - RBCS, 3, (CString)showbuff);
		//RDW-CV
		if (atof((*psampledata).rbcdata.rdwcv) < systemcfg.range.normal[rangetype][RDWCVS])
			rangeFlag = 'L';
		else if (atof((*psampledata).rbcdata.rdwcv) > systemcfg.range.normal[rangetype][RDWCVS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).rbcdata.rdwcv);
		m_RBCresultList.SetItemText(RDWCVS - RBCS, 3, (CString)showbuff);
		//RDW-SD
		if (atof((*psampledata).rbcdata.rdwsd) < systemcfg.range.normal[rangetype][RDWSDS])
			rangeFlag = 'L';
		else if (atof((*psampledata).rbcdata.rdwsd) > systemcfg.range.normal[rangetype][RDWSDS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).rbcdata.rdwsd);
		m_RBCresultList.SetItemText(RDWSDS - RBCS, 3, (CString)showbuff);
	}
	UpdateRBCFlagBox(psampledata);

	//RBC直方图
	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_RBCChart.GetChart();
	ASSERT_VALID(pChart);
	//CBCGPChartSeries* pSeries1 = pChart->CreateSeries("RBC");
	int num = pChart->GetSeriesCount();
	CBCGPChartSeries* pSeries1 = pChart->GetSeries(num - 1);
	pSeries1->RemoveAllDataPoints();
	COleDateTime today = COleDateTime::GetCurrentTime();

	for (i = 0; i < 255; i++)	//其实经过纵坐标压缩放大处理后，计数值已经小于RBC_HEIGHT<255了，所以其实rbcgraph高字节存的都是0
		graphbuff[i] = ((psampledata->rbcgraph[(i << 1) + 1] - 1) << 8) + psampledata->rbcgraph[i << 1] - 1;

	//横坐标[0,204]，204不显示。去掉一些点，每五个元素去掉中间一个点
	for (i = 0; i < 204; i++)
	{
		graphbuff[i] = graphbuff[i + (i + 2) / 4];
		pSeries1->AddDataPoint(graphbuff[i]);
	}
	UpdateRBCFlagBox(psampledata);

	pChart->Redraw();
}

void CTestmainView::PrintPLTChart(sample_info *psampledata)
{
	unsigned short int i;
	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_PLTChart.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetChartType(BCGPChartArea, BCGP_CT_SIMPLE);
	pChart->SetChartTitle(_T("PLT"));
	pChart->ShowChartTitle(TRUE, TRUE);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->SetCurveType(BCGPChartFormatSeries::CCT_SPLINE);
	pChart->SetColors((CBCGPChartTheme::ChartTheme)5);//0:蓝色；1：青色；2：墨色；3：绿色；4：天蓝色；5：橙黄；6：淡红； 7：black and yellow ；8：红色......

	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));

	//将对0x00的特殊处理去除		
	for (i = 0; i < 255; i++)
		graphbuff[i] = psampledata->pltgraph[i] - 1;

	for (i = 0; i < 204; i++)
	{
		pSeries1->AddDataPoint(graphbuff[i]);
	}


	SetDefaultLineWidth();
	SetObjectColors();

	pChart->SetSeriesShadow();


	pChart->Redraw();
}
void CTestmainView::UpdatePrintPLTChart(sample_info *psampledata, const unsigned char rangetype)
{
	UpdateData();
	unsigned short int i;
	uchar 		rangeFlag = ' ', doubtFlag = ' ';
	char 		showbuff[9 + 1] = { 0 };	//PLT***->**.*(单位:10^4uL)，多了一个字符长度

	unsigned char graphbuff[256] = { 0 };
	CBCGPChartVisualObject* pChart = m_PLTChart.GetChart();
	ASSERT_VALID(pChart);

	//CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Series 1"));
	int num = pChart->GetSeriesCount();
	CBCGPChartSeries* pSeries1 = pChart->GetSeries(num - 1);
	pSeries1->RemoveAllDataPoints();
	//将对0x00的特殊处理去除		
	for (i = 0; i < 255; i++)
		graphbuff[i] = psampledata->pltgraph[i] - 1;

	for (i = 0; i < 204; i++)
	{
		pSeries1->AddDataPoint(graphbuff[i]);
	}

	SetDefaultLineWidth();
	SetObjectColors();

	//ZWH 20170221添加
	if ((*psampledata).pltdata.plt[0] == '*')//未做测试
	{
		if (systemcfg.unitPLT == 2)
			sprintf(showbuff, "%s%.1f", "   ", atof((*psampledata).pltdata.plt) / 10);
		else
			sprintf(showbuff, "%s%s", "   ", (*psampledata).pltdata.plt);
		m_PLTresultList.SetItemText(PLTS - PLTS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).pltdata.mpv);
		m_PLTresultList.SetItemText(MPVS - PLTS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).pltdata.pdw);
		m_PLTresultList.SetItemText(PDWS - PLTS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).pltdata.pct);
		m_PLTresultList.SetItemText(PCTS - PLTS, 3, (CString)showbuff);
		sprintf(showbuff, "%s%s", "   ", (*psampledata).pltdata.plcr);
		m_PLTresultList.SetItemText(PLCRS - PLTS, 3, (CString)showbuff);
	}
	else//做了测试
	{
		//if(1 == count_plt_flag)
		if (1 == (*psampledata).flag_wrp[2])
			doubtFlag = ' ';
		//else if(2 == count_plt_flag)
		else if (2 == (*psampledata).flag_wrp[2])
			doubtFlag = '?';
		else
			doubtFlag = '*';

		//PLT
		if (atof((*psampledata).pltdata.plt) < 10)
		{
			if (systemcfg.unitPLT == 2)
				sprintf(showbuff, "%c%c %.1f", 'L', 'L', atof((*psampledata).pltdata.plt) / 10);
			else
				sprintf(showbuff, "%c%c %s", 'L', 'L', (*psampledata).pltdata.plt);
		}
		else if (atof((*psampledata).pltdata.plt) > 1000)
		{
			if (systemcfg.unitPLT == 2)
				sprintf(showbuff, "%c%c %.1f", 'H', 'H', atof((*psampledata).pltdata.plt) / 10);
			else
				sprintf(showbuff, "%c%c %s", 'H', 'H', (*psampledata).pltdata.plt);
		}
		else
		{
			if (atof((*psampledata).pltdata.plt) < systemcfg.range.normal[rangetype][PLTS])
				rangeFlag = 'L';
			else if (atof((*psampledata).pltdata.plt) > systemcfg.range.normal[rangetype][PLTS + 28])
				rangeFlag = 'H';
			else
				rangeFlag = ' ';
			if (systemcfg.unitPLT == 2)
				sprintf(showbuff, "%c%c %.1f", rangeFlag, doubtFlag, atof((*psampledata).pltdata.plt) / 10);
			else
				sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).pltdata.plt);
		}
		m_PLTresultList.SetItemText(PLTS - 23, 3, (CString)showbuff);
		//MPV
		if (atof((*psampledata).pltdata.mpv) < systemcfg.range.normal[rangetype][MPVS])
			rangeFlag = 'L';
		else if (atof((*psampledata).pltdata.mpv) > systemcfg.range.normal[rangetype][MPVS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).pltdata.mpv);
		m_PLTresultList.SetItemText(MPVS - 23, 3, (CString)showbuff);
		//PDW
		if (atof((*psampledata).pltdata.pdw) < systemcfg.range.normal[rangetype][PDWS])
			rangeFlag = 'L';
		else if (atof((*psampledata).pltdata.pdw) > systemcfg.range.normal[rangetype][PDWS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).pltdata.pdw);
		m_PLTresultList.SetItemText(PDWS - 23, 3, (CString)showbuff);
		//PCT
		if (atof((*psampledata).pltdata.pct) < systemcfg.range.normal[rangetype][PCTS])
			rangeFlag = 'L';
		else if (atof((*psampledata).pltdata.pct) > systemcfg.range.normal[rangetype][PCTS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).pltdata.pct);
		m_PLTresultList.SetItemText(PCTS - 23, 3, (CString)showbuff);
		//PLCR
		if (atof((*psampledata).pltdata.plcr) < systemcfg.range.normal[rangetype][PLCRS])
			rangeFlag = 'L';
		else if (atof((*psampledata).pltdata.plcr) > systemcfg.range.normal[rangetype][PLCRS + 28])
			rangeFlag = 'H';
		else
			rangeFlag = ' ';
		sprintf(showbuff, "%c%c %s", rangeFlag, doubtFlag, (*psampledata).pltdata.plcr);
		m_PLTresultList.SetItemText(PLCRS - 23, 3, (CString)showbuff);
	}
	UpdatePLTFlagBox(psampledata);

	pChart->SetSeriesShadow();
	pChart->Redraw();

}
void CTestmainView::PrintPieChart()
{
	unsigned short int i;
	m_PieChart.EnableTooltip();

	CBCGPChartVisualObject* pChart = m_PieChart.GetChart();
	ASSERT_VALID(pChart);
	pChart->SetChartType(BCGPChartPie3D);

	//m_wndRotate.GetRotationObject()->SetAutorepeatMode(100);
	//m_wndRotate.GetRotationObject()->SetColorTheme(CBCGPRotationObject::BCGP_COLOR_THEME_VISUAL_MANAGER);

	//pChart->SetChartTitle(_T(" Proportion of blood cells"));
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);

	pChart->AddChartData(_T("NEU%"), 6700);
	pChart->AddChartData(_T("MONO%"), 4500);
	pChart->AddChartData(_T("EOS%"), 2200);
	pChart->AddChartData(_T("ALY%"), 1500);
	pChart->AddChartData(_T("LYM%"), 1400);

	pChart->ShowDataLabels(TRUE);
	int m_nDataLabelPosition = 0;
	BCGPChartDataLabelOptions dataLabelOptions = pChart->GetDataLabelOptions();
	dataLabelOptions.m_position = (BCGPChartDataLabelOptions::LabelPosition)m_nDataLabelPosition;
	dataLabelOptions.m_bUnderlineDataLabel = TRUE;
	dataLabelOptions.m_content = BCGPChartDataLabelOptions::LC_PIE_NAME_PERCENTAGE; //:BCGPChartDataLabelOptions::LC_DP_INDEX;
	dataLabelOptions.m_bDrawDataLabelBorder = dataLabelOptions.m_position != BCGPChartDataLabelOptions::LP_DEFAULT_POS && dataLabelOptions.m_position != BCGPChartDataLabelOptions::LP_OUTSIDE_END;

	pChart->SetDataLabelsOptions(dataLabelOptions);
	//AfxMessageBox(_T("2324"));
	pChart->Redraw();
}
void CTestmainView::UpdatePrintPieChart()
{
	UpdateData();
	m_PieChart.EnableTooltip();

	CBCGPChartVisualObject* pChart = m_PieChart.GetChart();
	ASSERT_VALID(pChart);
	pChart->SetChartType(BCGPChartPie3D);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->CleanUpChartData();
	pChart->AddChartData(_T("NEU%"), 5700);
	pChart->AddChartData(_T("MONO%"), 4500);
	pChart->AddChartData(_T("EOS%"), 2200);
	pChart->AddChartData(_T("ALY%"), 1500);
	pChart->AddChartData(_T("LYM%"), 2400);

	pChart->ShowDataLabels(TRUE);
	int m_nDataLabelPosition = 0;
	BCGPChartDataLabelOptions dataLabelOptions = pChart->GetDataLabelOptions();
	dataLabelOptions.m_position = (BCGPChartDataLabelOptions::LabelPosition)m_nDataLabelPosition;
	dataLabelOptions.m_bUnderlineDataLabel = TRUE;
	dataLabelOptions.m_content = BCGPChartDataLabelOptions::LC_PIE_NAME_PERCENTAGE; //:BCGPChartDataLabelOptions::LC_DP_INDEX;
	dataLabelOptions.m_bDrawDataLabelBorder = dataLabelOptions.m_position != BCGPChartDataLabelOptions::LP_DEFAULT_POS && dataLabelOptions.m_position != BCGPChartDataLabelOptions::LP_OUTSIDE_END;

	pChart->SetDataLabelsOptions(dataLabelOptions);

	pChart->Redraw();
}

void CTestmainView::InitWBCFlagBox()
{


}

void CTestmainView::InitRBCFlagBox()
{


}

void CTestmainView::InitPLTFlagBox()
{


}

void CTestmainView::UpdateWBClmneFlagBox(sample_info *psampledata)
{
	//WBC警告信息
	if (2 == (*psampledata).lmneflg[0])
		m_WBCFlagListBox.AddString(_T("NO"));
	if (2 == (*psampledata).lmneflg[1])
		m_WBCFlagListBox.AddString(_T("LL"));
	if (2 == (*psampledata).lmneflg[2])
		m_WBCFlagListBox.AddString(_T("LL1"));
	if (2 == (*psampledata).lmneflg[3])
		m_WBCFlagListBox.AddString(_T("NL"));
	if (2 == (*psampledata).lmneflg[4])
		m_WBCFlagListBox.AddString(_T("MN"));
	if (2 == (*psampledata).lmneflg[5])
		m_WBCFlagListBox.AddString(_T("RM"));
	if (2 == (*psampledata).lmneflg[6])
		m_WBCFlagListBox.AddString(_T("LN"));
	if (2 == (*psampledata).lmneflg[7])
		m_WBCFlagListBox.AddString(_T("RN"));
	if (2 == (*psampledata).lmneflg[8])
		m_WBCFlagListBox.AddString(_T("NE"));
}

void CTestmainView::UpdateWBCBasoFlagBox(sample_info *psampledata)
{
	if (2 == (*psampledata).basoflg[0])
		m_WBCFlagListBox.AddString(_T("L1"));
}

void CTestmainView::UpdateRBCFlagBox(sample_info *psampledata)
{
	//RBC警告信息
	if (2 == (*psampledata).rbcflg[0])			//RBC警告信息
		m_RBCFlagListBox.AddString(_T("MIC"));
	if (2 == (*psampledata).rbcflg[1])
		m_RBCFlagListBox.AddString(_T("MAC"));

}

void CTestmainView::UpdatePLTFlagBox(sample_info *psampledata)
{
	//PLT警告信息
	if (2 == (*psampledata).pltflg[0])	//PLT警告信息
		m_PLTFlagListBox.AddString(_T("MIC"));
	if (2 == (*psampledata).pltflg[1])
		m_PLTFlagListBox.AddString(_T("SCL"));
	if (2 == (*psampledata).pltflg[2])
		m_PLTFlagListBox.AddString(_T("PL"));
	if (2 == (*psampledata).pltflg[3])
		m_PLTFlagListBox.AddString(_T("AG"));
}

void CTestmainView::SetObjectColors()
{
	/*m_brFill1 = m_bIsDarkBackground ? CBCGPBrush(CBCGPColor::CadetBlue, .5) : CBCGPBrush(CBCGPColor::RoyalBlue, .2);
	m_brFill2 = m_bIsDarkBackground ? CBCGPBrush(CBCGPColor::ForestGreen, .5) : CBCGPBrush(CBCGPColor::Peru, .2);
	m_brFill3 = CBCGPBrush(CBCGPColor::LightSkyBlue, CBCGPColor::White, CBCGPBrush::BCGP_GRADIENT_DIAGONAL_LEFT, m_bIsDarkBackground ? .9 : .4);
	m_brFill4 = CBCGPBrush(CBCGPColor::LightYellow);
	m_brLine1 = CBCGPBrush(CBCGPColor::DarkRed);
	m_brLine2 = CBCGPBrush(CBCGPColor::DeepSkyBlue);
	m_brText1 = CBCGPBrush(CBCGPColor::SteelBlue);
	m_brText2 = CBCGPBrush(CBCGPColor::Brown);

	OnUpdateChart();*/
	//AfxMessageBox(_T("2627"));
}
///////////////////////////////////////////////////////////////////////////////////
void ClipChildren(HWND hwnd, HRGN parent)
{
	//HWND child = ::GetWindow(hwnd, GW_CHILD);
	//	while (child)
	//	{
	RECT rect;
	GetWindowRect(hwnd, &rect);
	ScreenToClient(hwnd, (LPPOINT)&rect.left);
	ScreenToClient(hwnd, (LPPOINT)&rect.right);
	HRGN rgn = CreateRectRgnIndirect(&rect);
	CombineRgn(parent, parent, rgn, RGN_DIFF);
	DeleteObject(rgn);
	//child = GetWindow(child, GW_HWNDNEXT);
	//}
}
//////////////////////////////////////////////////////////////////
/*
BOOL CTestmainView::OnCreate()
{
return true;

}
*/

BOOL CTestmainView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//AfxMessageBox(_T("2728"));
	//OnPaint();
	/*
	RECT clientRect;
	GetClientRect(&clientRect);
	HRGN rgn = CreateRectRgnIndirect(&clientRect);
	ClipChildren(m_hWnd, rgn);
	SelectClipRgn(pDC->m_hDC, rgn);
	DeleteObject(rgn);
	FillRect(pDC->m_hDC, &clientRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	*/
	return TRUE;
	//CBCGPChartExampleView::OnEraseBkgnd(pDC);

	/*
	CBCGPChartExampleView::OnEraseBkgnd(pDC);
	pDC->TextOutW(300, 300, "ERASEING");
	return true;
	*/

}

void CTestmainView::OnPaint()
{
	CPaintDC dc(this);
	//CDC* pDC = GetDC();

	CRect rc;
	GetClientRect(&rc);
	//rc.OffsetRect(-rc.left - 2, -rc.top - 2);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(&dc, rc.Width() + 2, rc.Height() + 2);
	HBITMAP oldBmp = (HBITMAP)MemDC.SelectObject(&MemBitmap);
	int Width = rc.Width() + 2;
	int Height = rc.Height() + 2;
	MemDC.FillSolidRect(rc.left, rc.top, Width, Height, RGB(255, 255, 255));

	SendMessage(WM_PRINT, (WPARAM)MemDC.m_hDC, (LPARAM)PRF_CHILDREN | PRF_CLIENT | PRF_NONCLIENT);

#ifdef TEST
	MemDC.SelectObject(oldBmp);
	OpenClipboard();
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, MemBitmap);
	CloseClipboard();
	oldBmp = (HBITMAP)MemDC.SelectObject(&MemBitmap);
#endif

	dc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &MemDC, 2, 2, SRCCOPY);
	//LmneGraphPaint(&sampledata, patientdata.rangetype,MemDC);

	MemDC.SelectObject(oldBmp);

	UpdateTestMode(((CMainFrame*)AfxGetMainWnd())->GetTestMode());
	PrintLMNEChart(&sampledata);
	DeleteObject(MemBitmap.m_hObject);
	DeleteObject(MemDC);


	UINT id = 0;
	CWnd *pWnd = 0;

	pWnd = GetDlgItem(IDC_STATIC1);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC2);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC3);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC4);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC5);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC6);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC7);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC8);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC9);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC10);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_STATIC11);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);

	pWnd = GetDlgItem(IDC_CHART1);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_CHART2);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_CHART3);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_CHART4);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);

	pWnd = GetDlgItem(IDC_CHART);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);

	//patientPaint(&patientdata);

}

void CTestmainView::patientPaint(patient_info *ppatientdata)
{

	CString technician, age, code, name, doctor;
	name.Format(L"%s", ppatientdata->name);
	technician.Format(L"%s", ppatientdata->technician);
	age.Format(L"%s", ppatientdata->age);
	code.Format(L"%s", ppatientdata->code);
	doctor.Format(L"%s", ppatientdata->doctor);


	if (0 == ((ppatientdata)->sex))
		m_sexcombo.SetCurSel(0);
	else if (1 == (ppatientdata)->sex)
		m_sexcombo.SetCurSel(1);
	else if (2 == (ppatientdata)->sex)
		m_sexcombo.SetCurSel(2);

	GetDlgItem(IDC_TESTMAIN_TECKNICIAN)->SetWindowText(technician);//姓名
	GetDlgItem(IDC_TESTMAIN_NAME)->SetWindowText(name);//姓名
	GetDlgItem(IDC_TESTMAIN_TECKNICIAN)->SetWindowText(technician);//科室
	GetDlgItem(IDC_TESTMAIN_AGE)->SetWindowText(age);//年龄
	GetDlgItem(IDC_TESTMAIN_BARCODE)->SetWindowText(code);//条码

}
//初始化sampledata和patientdata
void CTestmainView::InitData(void)//这部分初始化数据，是要显示的
{
	unsigned int i;
	//默认字符为""
	patientdata.number = 0000000000;
	strcpy(patientdata.name, "");
	patientdata.sex = 1;
	patientdata.rangetype = systemcfg.range.type;
	strcpy(patientdata.age, "");
	strcpy(patientdata.code, "");
	strcpy(patientdata.technician, "");
	strcpy(patientdata.doctor, "");

	//WBC
	strcpy(sampledata.wbcdata.wbc, "**.**");

	strcpy(sampledata.wbcdata.lymp, "**.*");
	strcpy(sampledata.wbcdata.neup, "**.*");
	strcpy(sampledata.wbcdata.monop, "*.*");
	strcpy(sampledata.wbcdata.eosp, "*.*");
	strcpy(sampledata.wbcdata.basp, "*.*");
	strcpy(sampledata.wbcdata.alyp, "*.*");
	strcpy(sampledata.wbcdata.licp, "*.*");

	strcpy(sampledata.wbcdata.lym, "*.**");
	strcpy(sampledata.wbcdata.neu, "*.**");
	strcpy(sampledata.wbcdata.mono, "*.**");
	strcpy(sampledata.wbcdata.eos, "*.**");
	strcpy(sampledata.wbcdata.bas, "*.**");
	strcpy(sampledata.wbcdata.aly, "*.**");
	strcpy(sampledata.wbcdata.lic, "*.**");
	//RBC
	strcpy(sampledata.rbcdata.rbc, "*.**");
	strcpy(sampledata.rbcdata.hgb, "***.*");
	strcpy(sampledata.rbcdata.hct, "**.*");
	strcpy(sampledata.rbcdata.mcv, "***.*");
	strcpy(sampledata.rbcdata.mch, "**.*");
	strcpy(sampledata.rbcdata.mchc, "***.*");
	strcpy(sampledata.rbcdata.rdwcv, "**.*");
	strcpy(sampledata.rbcdata.rdwsd, "**.*");
	//PLT
	strcpy(sampledata.pltdata.plt, "***");
	strcpy(sampledata.pltdata.mpv, "**.**");
	strcpy(sampledata.pltdata.pct, "**.**");
	strcpy(sampledata.pltdata.pdw, "**.*");
	strcpy(sampledata.pltdata.plcr, "**.*");

	//散点图
	for (i = 0; i < MATRIX_DATA_MAX; i++)
		sampledata.lmnegraph[i] = 1;
	//BASO直方图
	for (i = 0; i < 256; i++)
		sampledata.basograph[i] = 1;
	//RBC直方图
	for (i = 0; i < 512; i++)
		sampledata.rbcgraph[i] = 1;
	//PLT直方图
	for (i = 0; i < 256; i++)
		sampledata.pltgraph[i] = 1;
	//界标
	for (i = 0; i < 9; i++)
		sampledata.lmneflg[i] = 1;
	sampledata.basoflg[0] = 1;
	for (i = 0; i < 2; i++)
		sampledata.rbcflg[i] = 1;
	for (i = 0; i < 4; i++)
		sampledata.pltflg[i] = 1;
	sampledata.mode = systemcfg.mode;
	for (i = 0; i < 4; i++)
		sampledata.flag_wrp[i] = 1;
	sampledata.coeoflmne = 1.0;

	for (i = 0; i < 8; i++)
		strcpy(studyPara[i], "**.*");
	//AfxMessageBox(_T("2829"));
}

void CTestmainView::GetASBarcode(char buffRe[])
{
	static unsigned char i;
	for (i = 0; i < 21; i++)
		patientdata.code[i] = buffRe[i + 7];
	patientdata.code[21] = 0;
	//AfxMessageBox(_T("2930"));
}

void CTestmainView::CommonExecution(const char* Mess, uchar CMD, unsigned int m_ntime)
{
	//ARM_GPIOCMD(EN_RED);
	TRACE(Mess);
	DSP_status = Busy;
	sdata_cmd[0] = CMD;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME2, m_ntime, 0);
	//AfxMessageBox(_T("3031"));
}

void CTestmainView::AutoClean(const char* Mess)
{
	CommonExecution(Mess, SPI_CMD_AUTOCLEAN, SPI_POLL_TIME3000);
}

void  CTestmainView::ConcentratedCleaning_1(const char* Mess)
{
	CommonExecution(Mess, SPI_CMD_CONCENTRATE_CLEAN1, SPI_POLL_TIME1000);
}

void  CTestmainView::ConcentratedCleaning_2(const char* Mess)
{
	CommonExecution(Mess, SPI_CMD_CONCENTRATE_CLEAN2, SPI_POLL_TIME1000);
}

void  CTestmainView::YealyMaintenance(const char* Mess)
{
	CommonExecution(Mess, SPI_CMD_MONTHLYMAINTAIN, SPI_POLL_TIME3000);
}

void  CTestmainView::EM_RINSEBATHS(const char* Mess)
{
	CommonExecution(Mess, SPI_CMD_RINSEBATHS, SPI_POLL_TIME3000);
}

void CTestmainView::UpdateTestMode(int nTheme)
{

	if (nTheme != 3)
	{
		TRACE1("...............GetTestMode()=%d..............\n", ((CMainFrame*)AfxGetMainWnd())->GetTestMode());
		m_CRPresultList.SetItemText(0, 1, _T("*"));
	}
	else m_CRPresultList.SetItemText(0, 1, _T(""));
	//AfxMessageBox(_T("3132"));
}

void CTestmainView::GetErrInfo()
{
	int		i;

	for (i = 0; i < ERRNUM + 1; i++)
	{
		errorReceive[i] = 0;
	}
	sdata_cmd[0] = SPI_CMD_REQERROR;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	PC_RECEIVE_FRAME(errorReceive, SPI_TYPE_ERRORRES);
	errorNumber = 0;

	for (i = 1; i < ERRNUM + 1; i++)
		if (1 == errorReceive[i])
		{
			logfile.alertnum[i]++;
			errorMessage[errorNumber] = i;
			errorNumber++;
		}
	//AfxMessageBox(_T("3334"));
}

void CTestmainView::DisplayErrMess()
{
	errorShowMess = errorMessage[errorShowNum];

	if (errorShowMess == 8)       //WBC堵孔
	{
		SendMessage(WM_BLOCKER, (WPARAM)1, 0L);
	}
	else if (errorShowMess == 13)		  //鞘流堵孔
	{
		SendMessage(WM_BLOCKER, (WPARAM)2, 0L);
	}
	else if (errorShowMess == 9)		  //RBC堵孔
	{
		SendMessage(WM_BLOCKER, (WPARAM)3, 0L);
	}
	else
	{
		//InvalidateRect(hDlg, FAULT, TRUE);
	}

	UpdateErrMessage();
	//AfxMessageBox(_T("3435"));
}
void CTestmainView::SendCmdToDSP(uchar CMD_Name)
{
	char Mess[50];

	sdata_cmd[0] = CMD_Name;

	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME2, SPI_POLL_TIME3000, 0);
	//AfxMessageBox(_T("3536"));
}

void CTestmainView::DealwithBlockErr(uchar CMD_Name, uchar ErrNum)
{
	if (!BlockErr_Flag)
	{
		BlockErr_Flag = TRUE;

		BlockErrStore = ErrNum;
		SetTimer(CHECKERR_TIMER, 200, 0);
	}
	else
		puts("CHECKERR_TIMER is open!");

	SendCmdToDSP(CMD_Name);
	//AfxMessageBox(_T("3637"));
}

void CTestmainView::AutoClean_MainWnd(RECT* STATUS)
{
	if (DSP_status == Free)
	{
		//ActivateScreen();
		TRACE("..........active in the function autoclean_mainwnd..............\n");

		NumFromBoot = 0;	//归0

		AutoClean("IDM_MIAN_HYDR_AUTOCLEAN---------#\n");

		statusShowMess = 4;

		//InvalidateRect(hDlg, &STATUS, TRUE);
	}
	//AfxMessageBox(_T("3738"));
}

void CTestmainView::GetPatientInfo(patient_info* ppatientdata)
{
	CString m_sex,m_technician,m_name, m_age, m_doctor, m_barcode;

	//GetDlgItem(IDC_TESTMAIN_NUMBER)->GetWindowText(m_number);
	GetDlgItem(IDC_TESTMAIN_NAME)->GetWindowText(m_name);
	GetDlgItem(IDC_TESTMAIN_AGE)->GetWindowText(m_age);
	GetDlgItem(IDC_TESTMAIN_BARCODE)->GetWindowText(m_barcode);	
	GetDlgItem(IDC_TESTMAIN_TECKNICIAN)->GetWindowText(m_technician);

	USES_CONVERSION;
	char* temp = W2A(m_name);
	strcpy(ppatientdata->name, temp);

	temp = W2A(m_age);	
	strcpy(ppatientdata->age, temp);
	//sprintf(ppatientdata->age, "%s", temp);


	temp = W2A(m_barcode);
	sprintf(ppatientdata->code, "%s", temp);

	temp = W2A(m_technician);
	strcpy(ppatientdata->technician, temp);
	//sprintf(ppatientdata->technician, "%s", temp);
		
	//ppatientdata->number = _ttoi(m_number);

	ppatientdata->sex = m_sexcombo.GetCurSel();
	CString doctortemp;
	((CComboBox*)GetDlgItem(IDC_COMBO_DOCTOR))->GetWindowText(m_doctor);
	temp = W2A(m_doctor);
	sprintf(ppatientdata->doctor, "%s", temp);

}

void CTestmainView::Generatetask(task_info* ptaskdata)
{
	CString m_name, m_age, m_doctor;
	GetDlgItem(IDC_EDIT3)->GetWindowText(m_name);
	GetDlgItem(IDC_EDIT4)->GetWindowText(m_age);
	USES_CONVERSION;
	char* temp = W2A(m_name);
	sprintf(ptaskdata->name, "%s", temp);
	temp = W2A(m_age);
	sprintf(ptaskdata->age, "%s", temp);

	ptaskdata->sex = m_sexcombo.GetCurSel();
	CString doctortemp;
	((CComboBox*)GetDlgItem(IDC_COMBO_DOCTOR))->GetWindowText(m_doctor);
	temp = W2A(m_doctor);
	sprintf(ptaskdata->doctor, "%s", temp);
}

//TODO: 使视图上控件不可用
afx_msg LRESULT CTestmainView::OnDisableview(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);

	GetDlgItem(IDC_COMBO_SEX)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_DOCTOR)->EnableWindow(FALSE);

	GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST2)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST3)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST4)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST5)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST8)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST9)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST10)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST11)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC)->EnableWindow(FALSE);
	//AfxMessageBox(_T("4041"));

	return 0;
}

//TODO: 使视图上控件可用
afx_msg LRESULT CTestmainView::OnEnableview(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);

	GetDlgItem(IDC_COMBO_SEX)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_DOCTOR)->EnableWindow(TRUE);

	GetDlgItem(IDC_LIST1)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST2)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST3)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST4)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST5)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST8)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST9)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST10)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST11)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC)->EnableWindow(TRUE);
	//AfxMessageBox(_T("4142"));
	return 0;
}

afx_msg LRESULT CTestmainView::OnBlocker(WPARAM wParam, LPARAM lParam)
{
	switch (wParam){
	case 1:
	{
		IsBlocking = 1;
		//DealwithBlockErr(hDlg, SPI_CMD_BACKSWING_WBCPH, 8);
		break;
	}
	case 2:
		//DealwithBlockErr(hDlg, SPI_CMD_BACKSWING_LMNEPH, 13);
		break;
	case 3:
	{
		IsBlocking = 3;
		//DealwithBlockErr(hDlg, SPI_CMD_BACKSWING_RBCPH, 9);
		break;
	}
	default:
		break;
	}
	//AfxMessageBox(_T("4243"));
	return 0;
}

bool			CTestmainView::ErrorTimer_Flag = FALSE;
bool			CTestmainView::TempReq_EN = FALSE;
int				CTestmainView::addtime = 0;
int				CTestmainView::reagenttemp = 0;
int				CTestmainView::cuptemp = 0;
int				CTestmainView::oritemp_rea = 0;
int				CTestmainView::oritemp_cup = 0;
int				CTestmainView::TimesofTest = 0;
unsigned char	CTestmainView::ErrFlag = 0;
unsigned char	CTestmainView::IsBlocking = 0;
unsigned char	CTestmainView::EN_Repeat = 0;


//TODO:空白测试
afx_msg LRESULT CTestmainView::OnMainblanktest(WPARAM wParam, LPARAM lParam)
{
	TRACE(_T("进入空白测试"));
	InitData();
	if (StartupBlankTestsflag)//若是开机的空白自检测试，则初始化
	{
		StartupBlankTestswbc = 0.0;
		StartupBlankTestsrbc = 0.0;
		StartupBlankTestsplt = 0.0;
	}
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_CBC5DIFF_MODE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	statusShowMess = 1;
	errorShowMess = 0;
	if (ErrorTimer_Flag)
	{
		ErrorTimer_Flag = FALSE;
		KillTimer(ERROR_TIMER);
	}
	if (BlockErr_Flag)
	{
		BlockErr_Flag = FALSE;
		KillTimer(CHECKERR_TIMER);
	}
	PC_status = WAITING_DATA;

	SetTimer(SLEEP_TIMER1, 3000, 0);	//FDparam 比SPI_STATE_DATAISOK早一点
	//AfxMessageBox(_T("4344"));
	return 0;
}

extern HWND mainhwnd;
void CTestmainView::UpdateErrMessage()
{
	int			messFlag=0;	//标志位，用于记录是否打开报警，0：关闭；1：打开
	printf("errorShowMess++\n");
	
	if (systemcfg.language == CHINESE)
	{
		//错误信息在此更新，需更新时调用
		switch (errorShowMess){
		case 0:
			::PostMessage(mainhwnd, WM_REAGENT_ALARM, errorShowMess, 1);
			break;
		case 11:
			if (true == systemcfg2.warn_diluent){
				messFlag = 1;
				break;
			}
			else{
				messFlag = 0;
			}

		case 12:
			if (true == systemcfg2.warn_waste)
			{
				messFlag = 1;
				break;
			}
			else
				messFlag = 0;
		case 13:
			//messFlag = 1;
			//break;
		case 14:

			if (true == systemcfg2.warn_rinse)
			{
				messFlag = 1;
				break;
			}
			else
				messFlag = 0;

		case 15:
			if (true == systemcfg2.warn_hgb)
			{
				messFlag = 1;
				break;
			}
			else
				messFlag = 0;
		case 16:
			if (true == systemcfg2.warn_fix)
			{
				messFlag = 1;
				break;
			}
			else
				messFlag = 0;
		case 17:
			if (true == systemcfg2.warn_baso)
			{
				messFlag = 1;
				break;
			}
			else
				messFlag = 0;
		default:
			break;

		}
	}
		//if (0 == errorShowMess)
		//{
		//	::PostMessage(mainhwnd, WM_REAGENT_ALARM, errorShowMess, 1);
		//}
		//else
		//{
		//	//SetTextColor(*dcErr, COLOR_red);
		//	if (11 == errorShowMess)//排废液时间过长
		//	{
		//		if (true == systemcfg2.warn_diluent)
		//		{
		//			messFlag = 1;
		//		}
		//		else
		//			messFlag = 0;
		//	}
		//	else if (12 == errorShowMess)//排废液时间过长
		//	{
		//		if (true == systemcfg2.warn_waste)
		//		{
		//			messFlag = 1;
		//			//ARM_GPIOCMD(EN_BUZZER);
		//		}
		//		else
		//			messFlag = 0;
		//	}
		//	else if (13 == errorShowMess)
		//	{
		//		messFlag = 1;
		//		//
		//	}
		//	//add by jxq 20170309
		//	else if (14 == errorShowMess)
		//	{
		//		if (true == systemcfg2.warn_rinse)
		//		{
		//			messFlag = 1;
		//			//ARM_GPIOCMD(EN_BUZZER);					
		//		}
		//		else
		//			messFlag = 0;
		//	}
		//	else if (15 == errorShowMess)
		//	{
		//		//printf("15 == errorShowMess\n");
		//		if (true == systemcfg2.warn_hgb)
		//		{
		//			messFlag = 1;
		//		}
		//		else
		//			messFlag = 0;
		//	}
		//	else if (16 == errorShowMess)
		//	{
		//		if (true == systemcfg2.warn_fix)
		//		{
		//			messFlag = 1;
		//		}
		//		else
		//			messFlag = 0;
		//	}
		//	else if (17 == errorShowMess)
		//	{
		//		if (true == systemcfg2.warn_baso)
		//		{
		//			messFlag = 1;
		//		}
		//		else
		//			messFlag = 0;
		//	}
		//	else{// 缺省处理
		//			//
		//	}
	if (messFlag == 1){
		errorShowNum = 0;
		ErrFlag = 0;
		ErrorTimer_Flag = FALSE;
		KillTimer(ERROR_TIMER);
	}
	else{

	}
	::PostMessage(mainhwnd, WM_REAGENT_ALARM, errorShowMess, messFlag);
		//::PostMessage(mainhwnd, WM_REAGENT_ALARM, 5, 0);
	

	//else if (systemcfg.language == ENGLISH)
	//{
	//	if (0 == errorShowMess)
	//	{
	//		/*SetTextColor(*dcErr, COLOR_blue);
	//		if(0 == logfile.regent.rinse && True == systemcfg2.warn_rinse)
	//		ErrFun(ErroInfo_EN[0]);
	//		else if(0 == logfile.regent.hgblyse && True == systemcfg2.warn_hgb)
	//		ErrFun(ErroInfo_EN[1]);
	//		else if(0 == logfile.regent.fix && True == systemcfg2.warn_fix)
	//		ErrFun(ErroInfo_EN[2]);
	//		else if(0 == logfile.regent.wbclyse && True == systemcfg2.warn_baso)
	//		ErrFun(ErroInfo_EN[3]);
	//		else
	//		{
	//		SetTextColor(*dcErr, COLOR_black);
	//		ErrFun("NORMAL");
	//		}*/
	//		SetTextColor(*dcErr, COLOR_black);
	//		ErrFun("NORMAL");
	//	}
	//	else
	//	{
	//		SetTextColor(*dcErr, COLOR_red);
	//		if (errorShowMess> 0 && errorShowMess<11)
	//			ErrFun(MotorErrInfo_EN[errorShowMess - 1]);
	//		else if (11 == errorShowMess)//排废液时间过长
	//		{
	//			if (True == systemcfg2.warn_diluent)
	//			{
	//				ErrFun(MotorErrInfo_EN[errorShowMess - 1]);
	//			}
	//			else
	//				ErrFun("NORMAL");
	//		}
	//		else if (12 == errorShowMess)//排废液时间过长
	//		{
	//			if (True == systemcfg2.warn_waste)
	//			{
	//				ErrFun(MotorErrInfo_EN[errorShowMess - 1]);
	//			}
	//			else
	//				ErrFun("NORMAL");
	//		}
	//		else if (13 == errorShowMess)
	//		{
	//			ErrFun(MotorErrInfo_EN[errorShowMess - 1]);
	//		}
	//		//add by jxq 20170309
	//		else if (14 == errorShowMess)
	//		{
	//			if (True == systemcfg2.warn_rinse)
	//			{
	//				ErrFun(MotorErrInfo_EN[errorShowMess - 1]);
	//			}
	//			else
	//				ErrFun("NORMAL");
	//		}
	//		else if (15 == errorShowMess)
	//		{
	//			if (True == systemcfg2.warn_hgb)
	//			{
	//				ErrFun(MotorErrInfo_EN[errorShowMess - 1]);
	//			}
	//			else
	//				ErrFun("NORMAL");
	//		}
	//		else if (16 == errorShowMess)
	//		{
	//			if (True == systemcfg2.warn_fix)
	//			{
	//				ErrFun(MotorErrInfo_EN[errorShowMess - 1]);
	//			}
	//			else
	//				ErrFun("NORMAL");
	//		}
	//		else if (17 == errorShowMess)
	//		{
	//			if (True == systemcfg2.warn_baso)
	//			{
	//				ErrFun(MotorErrInfo_EN[errorShowMess - 1]);
	//			}
	//			else
	//				ErrFun("NORMAL");
	//		}
	//		else//缺省处理
	//			ErrFun("Unknown Error");
	//	}
	//}
}


afx_msg LRESULT CTestmainView::OnMaintest(WPARAM wParam, LPARAM lParam)
{
	//MessageBox(L"hello world");
	TRACE("===============MainTest==========\n");
	//UpdateErrMessage();

	//hw_add:20150104
	errorShowMess = 0;
	//if(errorNumber > 0)
	if (ErrorTimer_Flag)
	{
		ErrorTimer_Flag = FALSE;
		KillTimer(ERROR_TIMER);
	}
	if (BlockErr_Flag)
	{
		BlockErr_Flag = FALSE;
		KillTimer(CHECKERR_TIMER);
	}
	TimesofTest++;
	logfile.totaltimesoftest++;
	InitData();
	NumFromBoot++;
	//向控制机发送测试命令
	DSP_status = Busy;
	if (systemcfg.mode == WHOLEDIFF || systemcfg.mode == DILUENTDIFF)
		sdata_cmd[0] = SPI_CMD_CBC5DIFF_MODE;
	else if (systemcfg.mode == WHOLECBC || systemcfg.mode == DILUENTCBC)
		sdata_cmd[0] = SPI_CMD_CBC_MODE;

	if (WAIT_OBJECT_0 == WaitForSingleObject(SendMutex, INFINITE))// 收到激发态的消息  
	{
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	}
	else
	{
		MessageBox(L"仪器运行中无法进行操作!", L"提醒!", MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	statusShowMess = 1;
	//InvalidateRect(hDlg, &STATUS, TRUE);
	UpdateData(true);

	if (3 == systemcfg3.structure)//自动进样
	{
		PC_status = WAITING_PUNCTURE_OVER;
		//设定轮询控制机状态的定时器		
		SetTimer(POLLTIME, SPI_POLL_TIME3000, 0);    //轮询时间定时器		
	}
	else
	{
		PC_status = WAITING_DATA;

		SetTimer(SLEEP_TIMER1, 3000, 0);	//FDparam 比SPI_STATE_DATAISOK早一点
	}
	return 0;
}

afx_msg LRESULT CTestmainView::OnAutoclean(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

afx_msg LRESULT CTestmainView::OnConcenclean(WPARAM wParam, LPARAM lParam)
{
	MessageBox(_T("浓缩清洗"));
	return 0;
}

afx_msg LRESULT CTestmainView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)//*下位机传上来的spi参数
	{
		//"穿刺结束"
	case SPI_STATE_PUNCTURE_OVER:	//自动进样模式下才用到
		TRACE(_T("SPI_STATE_PUNCTURE_OVER"));
		printf("Puncture is over----------#\n");
		if (PC_status != WAITING_PUNCTURE_OVER)
			break;
		PC_status = WAITING_DATA;
		break;
		//------------------------------------------------
		//接收测试数据处理		
		//DSP状态变成SPI_STATE_DATAISOK的下一个状态时要确保数据已接收完
	case SPI_STATE_ERROR_DRM:
		TRACE(_T("SPI_STATE_ERROR_DRM"));
		if (systemcfg.language == CHINESE)
			MessageBox(_T("排液超时,请关机检查"), _T("警告!"), MB_OK | MB_ICONINFORMATION);
		else if (systemcfg.language == ENGLISH)
			//CreateWarningBoxNonCHDlg(hDlg, "Drain over time,please shutdown and have a check", "Warning!");
			//MessageBox(_T("排液超时,请关机检查"), _T("警告!"), MB_OK | MB_ICONINFORMATION);
			MessageBox(_T("Drain over time,please shutdown and have a check"), _T("Warning!"), MB_OK | MB_ICONINFORMATION);
		while (1)
			Sleep(10);
		break;
	case SPI_STATE_ERROR_YM:
		MessageBox(_T("SPI_STATE_ERROR_YM"));
		if (systemcfg.language == CHINESE)
			MessageBox(_T("YM电机复位故障,请关机检查"), _T("警告!"), MB_OK | MB_ICONINFORMATION);
		else if (systemcfg.language == ENGLISH)
			//CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Reseting YM motor fault,please shutdown and have a check", "Warning!");
			MessageBox(_T("排液超时,请关机检查"), _T("警告!"), MB_OK | MB_ICONINFORMATION);
		while (1)
			Sleep(10);
		break;
	case SPI_STATE_DATAISOK:
		printf("Data is over----------#\n");
		TRACE(_T("SPI_STATE_DATAISOK"));
		if (PC_status != WAITING_DATA)
			break;
		PC_status = WAITING_TEST_OVER;
		KillTimer(POLLTIME2);
		//------------------------------------------------------------------------------------------------
		m_datatrans.GetNormalTestData(systemcfg.mode, &sampledata);
		//------------------------------------------------------------------------------------------------
		//日志文件的修改
		//试剂剩余量
		//if (systemcfg2.warn_diluent || systemcfg2.warn_baso || systemcfg2.warn_fix || systemcfg2.warn_hgb
		//	|| systemcfg2.warn_rinse || systemcfg2.warn_waste)
		//{
			if (WHOLEDIFF == systemcfg.mode || DILUENTDIFF == systemcfg.mode)
			{
				//if (systemcfg2.warn_rinse)//systemcfg.regentfull.rinse;
				//{
					if (logfile.regent.rinse > 11)
						logfile.regent.rinse = logfile.regent.rinse - 11;
					else
						logfile.regent.rinse = 0;
				//}
				//if (systemcfg2.warn_hgb)//systemcfg.regentfull.hgblyse
				//{
					if (logfile.regent.hgblyse > 4)
						logfile.regent.hgblyse = logfile.regent.hgblyse - 4;
					else
						logfile.regent.hgblyse = 0;
				//}
				//if (systemcfg2.warn_fix)//systemcfg.regentfull.eoslyse
				//{
					if (logfile.regent.eoslyse > 10)
						logfile.regent.eoslyse = logfile.regent.eoslyse - 10;
					else
						logfile.regent.eoslyse = 0;
				//}
				//if (systemcfg2.warn_baso)// systemcfg.regentfull.baslyse
				//{
					if (logfile.regent.baslyse > 21)
						logfile.regent.baslyse = logfile.regent.baslyse - 21;
					else
						logfile.regent.baslyse = 0;
				//}
			}
			else
			{
				if (systemcfg2.warn_rinse)
				{
					if (logfile.regent.rinse > 11)
						logfile.regent.rinse = logfile.regent.rinse - 11;
					else
						logfile.regent.rinse = 0;
				}
				if (systemcfg2.warn_hgb)
				{
					if (logfile.regent.hgblyse > 4)
						logfile.regent.hgblyse = logfile.regent.hgblyse - 4;
					else
						logfile.regent.hgblyse = 0;
				}
				if (systemcfg2.warn_baso)
				{
					if (logfile.regent.baslyse > 20)
						logfile.regent.baslyse = logfile.regent.baslyse - 20;
					else
						logfile.regent.baslyse = 0;
				}
				//logfile.regent.fix = logfile.regent.eoslyse - 10;		//CBC模式不消耗
			}
		//}
		//接收错误状态
		GetErrInfo();
		//日志文件处理		
		if (errorNumber > 0 || systemcfg2.warn_baso || systemcfg2.warn_diluent || systemcfg2.warn_fix
			|| systemcfg2.warn_hgb || systemcfg2.warn_rinse || systemcfg2.warn_waste)
		{
			if (errorNumber > 0)
			{
				ErrFlag = 1;
				errorShowNum = 0;
				ErrorTimer_Flag = TRUE;

				DisplayErrMess();//显示错误信息，待处理

				//UpdateErrMessage();//此处更新错误信息

				SetTimer(ERROR_TIMER, 200, 0);
			}
		}
		//SetTimer(UPDATE_STATUS, 200, 0);
		//------------------------------------------------------------------------------------------------
		//数据接收成功，进行处理的过程
		//分析数据
		{
			//uchar* 	pIsSuper = (uchar*)GetWindowAdditionalData(hDlg);
			int		recv = 0;

			m_dataprocess.BasoLmneRbcPlt_2Analyse(&sampledata);//没问题

			m_dataprocess.WbcBasoAnalysis(&sampledata, pIsSuper);
			if (WHOLEDIFF == systemcfg.mode || DILUENTDIFF == systemcfg.mode)
			{
				recv = m_dataprocess.LmneAnalysis(&sampledata, pIsSuper);	//必须放在BASO分析后面
				//若接收数据全部为0，则重新接收
				if (recv == -1)
				{
					for (i = 0; i < 3; i++)
					{
						sdata_cmd[0] = SPI_CMD_REQLMNE;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (0 == PC_RECEIVE_FRAME((unsigned char*)sampledata.lmnegraph, SPI_TYPE_LMNERES))
						{
							printf("LMNE transfer times=%d---------#\n", i + 1);
							break;
						}
					}
					recv = m_dataprocess.LmneAnalysis(&sampledata, pIsSuper);
				}
			}
			m_dataprocess.HgbAnalysis(&sampledata);		//必须放在RBC分析前面
			m_dataprocess.RbcAnalysis(&sampledata, pIsSuper);
			m_dataprocess.PltAnalysis(&sampledata);
		}
		//------------------------------------------------------------------------------------------------	
		if (!StartupBlankTestsflag)	//不是开机空白测试
		{
			//向样本数据表插入记录
			GetRowNo((sampledata.row), (sampledata.number));//获取本次测试的记录号及编号
			if (NumChanged)
			{
				char trans[20] = { 0 };
				strcpy(trans, &SampNum[2]);
				sampledata.number = atoi(trans);
				NumChanged = FALSE;
			}
			if (EN_Repeat)
				sampledata.number -= 1;
			AddSampleRecord(&sampledata);
			//向病人信息表插入病人编号，注册以和病人数据表记录同步
			patientdata.row = sampledata.row;
			patientdata.number = sampledata.number;

			TestMain_number.EnableWindow(true);
			GetPatientInfo(&patientdata);//获取窗口病人信息//此处可能有乱码
			AddPatientRecord(&patientdata);
			//UpdateData(TRUE);
			CString p_num;
			p_num.Format(_T("%d"), sampledata.number);
			TestMain_number.SetWindowTextW(p_num);

			TestMain_number.EnableWindow(false);
			/*if (1 == systemcfg.printercfg.mode)//如果打印模式为自动
			{
			PrintResults(&sampledata, &patientdata);
			}
			if (!systemcfg.com.upload)	//自动上传
			{
			if (systemcfg2.PcConMode == 2)
			PCNetSend(systemcfg2.ipaddr, systemcfg2.netport, &sampledata, &patientdata);
			else
			{
			SendDataToPc_EN = 1;
			psampledataToSend = &sampledata;
			}
			}*/
			//----------------------------------------
			//是否需暂停自动进样系统工作进行维护操作
			DataBaseFull = 0;
			if (sampledata.row >= 995 && sampledata.row <= 999)//数据库995,996,997,998,999提示数据库备份，连续提示5次
			{
				DataBaseFull = 1;
			}//else 未满995组数据则可以连续做第二次   满1000的时候就不提示数据库操作了，直接顶出一个row最小的记录可以连续做第二次	

			ReagentEmpty = 0;
			if (logfile.regent.rinse == 0 || logfile.regent.hgblyse == 0 || logfile.regent.eoslyse == 0 || logfile.regent.baslyse == 0)//试剂不足
			{
				ReagentEmpty = 1;
			}//else 试剂还有

			AlertMotorShow = 0;
			if (errorNumber > 0)//有错误
			{
				for (i = 0; i < errorNumber; i++)//电机错误
				{
					if (errorMessage[i] >= 1 && errorMessage[i] <= 7)
					{
						AlertMotorShow = 1;     //此处只能表示有电机错误，并不能确定是哪几个
						break;
					}
				}
			}//else 没有电机错误
			NumOverwashfrequency = 0;
			if (NumFromBoot >= systemcfg.washfrequency)
			{
				printf("NumFromBoot >= washfrequency----------#\n");
				NumOverwashfrequency = 1;
			}

			if (DataBaseFull || ReagentEmpty || AlertMotorShow || NumOverwashfrequency)//数据库满或需自动清洗  自动进样系统暂停下来
			{
				ASCur_EN = FALSE;
			}
			else
			{
				if (1 != IsBlocking && 3 != IsBlocking)
					DSP_status = Clean;	//准备在清洗过程中接收下一次检测命令
			}
			UpdateForm(&sampledata);
			UpdatePrintChart(&sampledata);
			InitWBCFlagBox();
			//----------------------------------------
		}
		if (1 == IsBlocking || 3 == IsBlocking)
		{
			key_status = FALSE;
			statusShowMess = 5;
		}
		else
		{
			statusShowMess = 0;
			//ARM_GPIOCMD(EN_GREEN);
		}
		SetTimer(POLLTIME2, SPI_POLL_TIME3000, 0);
		break;
		//------------------------------------------------
		//测试过程状态
	case SPI_STATE_INFO_END:
		//ARM_GPIOCMD(EN_GREEN);
		TRACE(_T("SPI_STATE_INFO_END"));
		KillTimer(POLLTIME2);
		IsBlocking = 0;
		DSP_status = Free;
		statusShowMess = 0;
		//InvalidateRect(hDlg, &STATUS, TRUE);
		key_status = TRUE;
		//Standby_EN = TRUE;
		ASCur_EN = TRUE;
		break;
	case SPI_STATE_TESTISOVER:
		TRACE("MSG_TIMER:POLLTIME is killed -------------#\n");
		TRACE("MSG_ACKSPI: Test Proc is over -------------#\n");
		TRACE(_T("SPI_TEST_IS OVER"));
		if (PC_status != WAITING_TEST_OVER)
			return -1;
		EN_Repeat = 0;
		//----------
		ErrFlag = 0;
		KillTimer(POLLTIME2);
		//KillTimer(UPDATE_STATUS);

		//InvalidateRect(hDlg, NULL, TRUE);
		UpdateData(FALSE);
		//----------
		PC_status = TEST_OVER;		//必须在SendMessage之前，在后会导致第二次开机空白测试不接受数据
		if (IsBlankTest)
			IsBlankTest = FALSE;
		//------------------------------------------------
		if (StartupBlankTestsflag)//开机测试  恢复到正常状态
		{
			StartupBlankTestsTimes++;
			if (1 == StartupBlankTestsTimes)
			{
				if (StartupBlankTestswbc < 0.3 && StartupBlankTestsrbc < 0.05 && StartupBlankTestsplt < 10)//对检测结果进行判断，第一次空白测试合格					
				{
					TRACE("Startup BlankTest first time Qualified----------\n");
					StartupBlankTestsflag = FALSE;

					TempReq_EN = TRUE;
				}
				else//第一次空白测试不合格
				{
					TRACE("Startup BlankTest first time not Qualified----------\n");
					TempReq_EN = FALSE;
					SendMessage(WM_MAINBLANKTEST, 0);	//进入空白测试
				}
			}
			else if (2 == StartupBlankTestsTimes)
			{
				if (StartupBlankTestswbc < 0.3 && StartupBlankTestsrbc < 0.05 && StartupBlankTestsplt < 10)//对检测结果进行判断，第二次空白测试合格			
				{
					TempReq_EN = TRUE;
					printf("Startup BlankTest second time Qualified----------\n");
				}
				else//第二次空白测试不合格					
				{
					TempReq_EN = FALSE;
					printf("Startup BlankTest second time not Qualified----------\n");
					if (systemcfg.language == CHINESE)
						MessageBox(_T("空白测试不合格\n  请检查仪器!"), _T("警告!"), MB_OK | MB_ICONINFORMATION);
					else if (systemcfg.language == ENGLISH)
						//CreateWarningBoxNonCHDlg(hDlg, "Blank test wrong!\nPlease check device!", "Warning!");
						MessageBox(_T("空白测试不合格\n  请检查仪器!"), _T("警告!"), MB_OK | MB_ICONINFORMATION);
				}
				TempReq_EN = TRUE;      //第二次空白测试结果不管怎样都检测温度
				StartupBlankTestsflag = FALSE;
			}
			if (TempReq_EN)
			{
				addtime = 0;
				statusShowMess = 3;
				//InvalidateRect(hDlg, &STATUS, TRUE);
				UpdateData(FALSE);
				SetTimer(SLEEP_TIMER1, 2000, 0);     //6000
			}
		}
		else//不是开机测试
		{
			if (1 == IsBlocking)
			{
				DealwithBlockErr(SPI_CMD_BACKSWING_WBCPH, 8);
			}
			else if (3 == IsBlocking)
			{
				DealwithBlockErr(SPI_CMD_BACKSWING_RBCPH, 9);
			}
			else
			{
				DSP_status = Free;
				key_status = TRUE;
			}
		}
		//------------------------------------------------影响自动进样的	
		if (1 == DataBaseFull || 1 == ReagentEmpty || 1 == AlertMotorShow || 1 == NumOverwashfrequency)
		{
			if (1 == DataBaseFull)	//做主菜单的空白测试，正常的测试都会触发这个
			{
				if (systemcfg.language == CHINESE)
					MessageBox(_T("数据库已满，请备份。否则以前数据丢失!"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				else if (systemcfg.language == ENGLISH)
					//CreateWarningBoxNonCHDlg(hDlg, "Database is full,Please backup database.Otherwise,Previous database will be lost!", "Presentation");
					MessageBox(_T("数据库已满，请备份。否则以前数据丢失!"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//CreateEmptyDatabaseDlg(hDlg);
			}
			if (1 == ReagentEmpty)	//检查试剂
			{
				if (systemcfg.language == CHINESE)
					MessageBox(_T("请检查试剂!"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				else if (systemcfg.language == ENGLISH)
					//CreateWarningBoxNonCHDlg(hDlg, "Check the Reagent Please!", "Presentation");
					MessageBox(_T("请检查试剂!"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				//CreateRegentAmountDlg(hDlg);
			}
			if (1 == AlertMotorShow)//检查电机
			{
				if (systemcfg.language == CHINESE)
					MessageBox(_T("请检查电机!"), _T("提示"), MB_OK | MB_ICONINFORMATION);
				else if (systemcfg.language == ENGLISH)
					//CreateWarningBoxNonCHDlg(hDlg, "Check the Motor Please!", "Presentation");
					MessageBox(_T("Check the Motor Please!"), _T("Presentation"), MB_OK | MB_ICONINFORMATION);
				//CreateAlertShowDlg(hDlg);
				break;//检查完，不使能自动进样系统，不执行自动清洗
			}
			if (1 == NumOverwashfrequency)
			{
				SendMessage(WM_AUTOCLEAN, 0);
				//自动清洗执行完执行ASCur_EN = 1
			}
			else
			{
				ASCur_EN = TRUE;	//不需要做自动清洗的时候，可以使能自动进样系统(只有自动进样系统用到)
			}
		}
		if (TimesofTest >= 500)   //Add:20150430
		{
			int 		response;
			MesBox	Message;

			if (systemcfg.language == CHINESE)
			{
				response = MessageBox(_T("测试样本已达500,请执行浓缩清洗"), _T("浓缩清洗提示"), MB_YESNO);
			}
			else if (systemcfg.language == ENGLISH)
			{
				Message.caption = "Tip of Concentrated Clean";
				Message.message = "You have tested 500 samples,\na Concentrated Clean is necessary";
				Message.type = MBOX_YESNO;
				//CreateYesNoDlg(hDlg, &response, &Message);
			}
			if (response == IDYES)
				SendMessage(WM_CONCENCLEAN, 0L);
		}
		ReleaseMutex(SendMutex);
		//------------------------------------------------	
		break;
		//----------------------------------------
	default:
		break;
	}
}

void CTestmainView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case SLEEP_TIMER1:
	{
		if (!TempReq_EN)
		{
			TRACE(_T("SLEEP_TIMER1"));
			KillTimer(SLEEP_TIMER1);
			TRACE("MSG_TIMER:SLEEP_TIMER1 is due -------------#\n");
			//设定轮询控制机状态的定时器		
			SetTimer(POLLTIME2, SPI_POLL_TIME1000, 0);    //轮询时间定时器	
		}
		else
		{
			TRACE(_T("SLEEP_TIMER2"));
			addtime++;
			if (addtime <= 30)      //10分钟
			{
				for (i = 0; i < 3; i++)	//循环三次，防止数据传输异常
				{
					sdata_cmd[0] = SPI_CMD_REQTEM;
					PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
					memset(temperature, 0, 8);
					if (0 == PC_RECEIVE_FRAME(temperature, SPI_TYPE_TEMRES))
					{
						break;
					}
				}
				if (addtime == 1)
				{
					oritemp_rea = temperature[0] * 1000 + temperature[1] * 100 + temperature[2] * 10 + temperature[3];
					oritemp_cup = temperature[4] * 1000 + temperature[5] * 100 + temperature[6] * 10 + temperature[7];
				}
				reagenttemp = temperature[0] * 1000 + temperature[1] * 100 + temperature[2] * 10 + temperature[3];
				cuptemp = temperature[4] * 1000 + temperature[5] * 100 + temperature[6] * 10 + temperature[7];
				tempcup_base = (unsigned int)systemcfg.tmp.env * 100;
				tempreagent_base = (unsigned int)systemcfg.tmp.incub * 100;

				//if(reagenttemp > tempreagent_base && cuptemp > tempcup_base && reagenttemp < 4000 && cuptemp < 4000 )     //条件改变
				if (reagenttemp > tempreagent_base - 200 && reagenttemp < 4000)
				{
					KillTimer(SLEEP_TIMER1);
					//等温度正常之后才能进行其他测试
					DSP_status = Free;
					Allow_ASOnLine = TRUE;
					ASCur_EN = TRUE;
					statusShowMess = 0;
					addtime = 0;
					TempReq_EN = FALSE;
				}
			}
			else
			{
				TRACE(_T("SLEEP_TIMER3"));
				char str_show[100] = "";
				char str_cat[20] = "";

				if (reagenttemp - oritemp_rea < 100)
				{
					if (systemcfg.language == CHINESE)
						MessageBox(_T("温控系统1: 试剂不加热"), _T("警告!"));
					else if (systemcfg.language == ENGLISH)
						MessageBox(_T("Temerature control system 1 : reagent doesn't heat"), _T("Warning!"));
				}
				if (reagenttemp<200)
				{
					if (systemcfg.language == CHINESE)
						MessageBox(_T("温控系统1: 试剂温度为0"), _T("警告!"));
					else if (systemcfg.language == ENGLISH)
						MessageBox(_T("Temerature control system 1 : reagent temperature is 0"), _T("Warning!"));
				}
				if (reagenttemp > tempreagent_base - 400)
				{
					if (systemcfg.language == CHINESE)
						strcpy(str_show, "环境温度太低");
					else if (systemcfg.language == ENGLISH)
						strcpy(str_show, "Environment temerature is too low");
					sprintf(str_cat, "\n %d", reagenttemp);
					strcat(str_show, str_cat);

					if (systemcfg.language == CHINESE)
						MessageBox((LPCTSTR)str_show, _T("警告!"));
					else if (systemcfg.language == ENGLISH)
						MessageBox((LPCTSTR)str_show, _T("Warning!"));
				}
				if (reagenttemp < tempreagent_base - 400 && reagenttemp > 200)
				{
					if (systemcfg.language == CHINESE)
						strcpy(str_show, "温控系统1: 试剂温度太低");
					else if (systemcfg.language == ENGLISH)
						strcpy(str_show, "Temerature control system 1 : reagent temperature is too low");
					sprintf(str_cat, "\n %d", reagenttemp);
					strcat(str_show, str_cat);

					if (systemcfg.language == CHINESE)
						MessageBox((LPCTSTR)str_show, _T("警告!"));
					else if (systemcfg.language == ENGLISH)
						MessageBox((LPCTSTR)str_show, _T("Warning!"));
				}
				KillTimer(SLEEP_TIMER1);
				DSP_status = Free;
				Allow_ASOnLine = TRUE;
				ASCur_EN = TRUE;
				statusShowMess = 0;
				addtime = 0;
				TempReq_EN = FALSE;
			}
		}
		break;
	}
	case ERROR_TIMER:
	{
		errorShowNum++;
		if (errorShowNum >= errorNumber)
		{
			errorShowNum = 0;
			ErrFlag = 0;
			ErrorTimer_Flag = FALSE;
			KillTimer(ERROR_TIMER);
		}
		else
			DisplayErrMess();
		break;
	}
	case CHECKERR_TIMER:
	{
		if (ErrorTimer_Flag == FALSE)    //若ErrorTimer关闭    
		{
			BlockErr_Flag = FALSE;
			KillTimer(CHECKERR_TIMER);
			errorShowMess = BlockErrStore;

			if (errorShowMess > 0)
			{

			}
		}
		break;
	}
	case POLLTIME2:
	{
		TRACE(_T("POLLTIME2\n"));
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);

		TRACE(_T("rdata_sate[0]=%X\n"), rdata_state[0]);
		PostMessage(WM_ACKSPI, rdata_state[0], 0);
		break;
	}
	default:
		break;
	}
	CBCGPChartExampleView::OnTimer(nIDEvent);
}

DWORD WINAPI CTestmainView::CreateAutoSampleThread(LPVOID lpParam)
{
	// 定义结构对象  
	PROCESS_INFORMATION pi;
	STARTUPINFO         si;
	BOOL                bRet;

	// 申请空间  
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));

	// 设置进程启动属性  
	si.cb = sizeof(STARTUPINFO);
	si.lpReserved = NULL;
	si.lpDesktop = NULL;
	si.lpTitle = NULL;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	si.cbReserved2 = NULL;
	si.lpReserved2 = NULL;

	CThreadAS m_ThreadAS;
	m_ThreadAS.ThreadAS();
	return 0;
}

DWORD WINAPI CTestmainView::ThreadPC(LPVOID lpParam)
{
	// 定义结构对象  
	PROCESS_INFORMATION pi;
	STARTUPINFO         si;
	BOOL                bRet;

	// 申请空间  
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));

	// 设置进程启动属性  
	si.cb = sizeof(STARTUPINFO);
	si.lpReserved = NULL;
	si.lpDesktop = NULL;
	si.lpTitle = NULL;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	si.cbReserved2 = NULL;
	si.lpReserved2 = NULL;

	//bRet = CreateProcess(_T("C://Program Files//Internet Explorer//IEXPLORE.exe"),
	//	_T("http://blog.csdn.net/wangningyu"),
	//	NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	AfxMessageBox(L"ThreadPC");
	return 0;
}

DWORD WINAPI CTestmainView::BarcodeCheck(LPVOID lpParam)
{
	// 定义结构对象  
	PROCESS_INFORMATION pi;
	STARTUPINFO         si;
	BOOL                bRet;

	// 申请空间  
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));

	// 设置进程启动属性  
	si.cb = sizeof(STARTUPINFO);
	si.lpReserved = NULL;
	si.lpDesktop = NULL;
	si.lpTitle = NULL;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	si.cbReserved2 = NULL;
	si.lpReserved2 = NULL;

	SetEvent(hEvent);
	CTestmainView  *m_Dlg = (CTestmainView*)lpParam;

	CRS232  m_rs232;
	uchar 	recvdata[100] = { 0 };
	CString barcode;
	USES_CONVERSION;
	for (int i = 0; i < 100; i++)
		recvdata[i] = 0;
	while (1)
	{
		m_rs232.ComRd(6, recvdata, 100, 9600);//条码枪波特率 9600
		barcode = A2W((char*)recvdata);
		if (barcode != "")
		{
			TRACE(barcode + "\n");
			m_Dlg->m_barcode = barcode;
			::PostMessage(m_Dlg->m_hWnd, WM_GETBARCODE, 0, 0);
		}
		Sleep(100);
		if (WAIT_OBJECT_0 == WaitForSingleObject(TestmainEvent, 2000))// 收到激发态的消息  
		{
			AfxMessageBox(L"testmain 线程退出");
			return 0;//正常退出  
		}
	}
	return   0;
}

afx_msg LRESULT CTestmainView::OnGetbarcode(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_TESTMAIN_BARCODE)->SetWindowText(m_barcode);
	return 0;
}

void CTestmainView::OnDestroy()
{
	CBCGPChartExampleView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	ResetEvent(TestmainEvent);
}

void CTestmainView::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTestmainView::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTestmainView::OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTestmainView::OnLvnItemchangedList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

void CTestmainView::OnEnChangeTestmainBarcode()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CBCGPChartExampleView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

// 开关状态检测,目前设计为检测一帧，不合理，待改善
DWORD WINAPI CTestmainView::SwitchStateCheck(LPVOID lpParam)
{
	TRACE("======================SwitchStateCheck");
	// 定义结构对象 
	PROCESS_INFORMATION pi;
	STARTUPINFO         si;
	BOOL                bRet;
	// 申请空间 
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	// 设置进程启动属性 
	si.cb = sizeof(STARTUPINFO);
	si.lpReserved = NULL;
	si.lpDesktop = NULL;
	si.lpTitle = NULL;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;
	si.cbReserved2 = NULL;
	si.lpReserved2 = NULL;
	SetEvent(hEvent);
	CTestmainView  *m_Dlg = (CTestmainView*)lpParam;

	//CView* pActiveView = GetActiveView();
	//HWND testwnd = pActiveView->GetSafeHwnd();

	int portNO = 2;

	CRS232  m_rs232;
	uchar  recvdata[100] = { 0 };
	CString switchState;
	//uchar reply[3] = { '1', '\r', '\n' };

	USES_CONVERSION;
	for (int i = 0; i < 100; i++)
		recvdata[i] = 0;
	CString reply[] = { CString('1'), CString('\r'), CString('\n') };
	//int replySize = sizeof(reply);

	while (1)
	{
		m_rs232.ComRd(portNO, recvdata, 10, 9600);//检测开关波特率 9600
		//switchState = A2W((char*)recvdata);
		//TRACE("************recvdata=%X\n", recvdata[0]);
		//recvdata[0] = 0x32;//此句调试时使用

		//int i = 0;
		//bool testState = true;
		//uchar test[] = {'t', 'e' ,'s','t'};
		//while (recvdata[i]!=0){
		//	if (recvdata[i] != test[i]){
		//		testState = false;
		//		break;
		//	}
		//}
		//if (testState)
		if (recvdata[0] == 0x32)//检测到开关按下
		{

			//TRACE(switchState + "\n");			
			//CString str = "111111111111111111";
			for (int i = 0; i < 3; i++)
				m_rs232.ComWrt(portNO, reply[i], 1, 9600);//向下位机反馈

			//if (res)
			//TRACE("send success\n");
			//TRACE("reply=%X\n:",reply[0]);
			::PostMessage(m_Dlg->m_hWnd, WM_MAINTEST, 0, 0);
			recvdata[0] = 0x00;
		}

		Sleep(100);
		if (WAIT_OBJECT_0 == WaitForSingleObject(TestmainEvent, 2000))// 收到激发态的消息 
		{
			AfxMessageBox(L"testmain 线程退出");
			return 0;//正常退出 
		}
	}
	//uchar reply[3] = { '1', '\r', '\n' };

	//CString cs[] = {CString('1'),CString('\r'),CString('\n')};
	//while (1)
	//{

	//	//recvdata[0] = 0x32;//此句调试时使用
	//	//if (recvdata[0]==0x32)//检测到开关按下
	//	//{
	//		
	//		//TRACE(switchState + "\n");			
	//		//CString str = "111111111111111111";
	//	for (int i = 0; i < 3;i++)
	//		 m_rs232.ComWrt(portNO, cs[i], 1, 9600);//向下位机反馈
	//		 //m_rs232.ComWrt(portNO, c2, 1, 9600);//向下位机反馈
	//		 //m_rs232.ComWrt(portNO, c3, 1, 9600);//向下位机反馈

	//		//if (res)
	//		TRACE("send success\n");
	//		//TRACE("reply=%x\n:",reply[0]);
	//		//::PostMessage(m_Dlg->m_hWnd, WM_MAINTEST, 0, 0);
	//		
	//		m_rs232.ComRd(portNO, recvdata, 10, 9600);//检测开关波特率 9600
	//		//switchState = A2W((char*)recvdata);
	//		//for (int i = 0; i < 100; i++)
	//		TRACE("************recvdata=%X\n", recvdata[0]);
	//		recvdata[0] = 0x00;
	//	//}

	//	Sleep(100);
	//	if (WAIT_OBJECT_0 == WaitForSingleObject(TestmainEvent, 2000))// 收到激发态的消息 
	//	{
	//		AfxMessageBox(L"testmain 线程退出");
	//		return 0;//正常退出 
	//	}
	//}
	return   0;

}
//HANDLE InitCom(char* comName)
//{
//	HANDLE hCom;
//	
//	CString cc = comName;
//	LPCWSTR wszClassName = new WCHAR[cc.GetLength() + 1];
//	wcscpy((LPTSTR)wszClassName, T2W((LPTSTR)cc.GetBuffer(NULL)));
//
//	hCom = CreateFile(wszClassName,//COM7口  
//		GENERIC_READ | GENERIC_WRITE, //允许读和写  
//		0, //独占方式  
//		NULL,
//		OPEN_EXISTING, //打开而不是创建  
//		0, //同步方式  
//		NULL);
//	if (hCom == (HANDLE)-1)
//	{
//		return NULL;
//	}
//	SetupComm(hCom, 100, 100); //输入缓冲区和输出缓冲区的大小都是100  
//	COMMTIMEOUTS TimeOuts;
//	//设定读超时  
//	TimeOuts.ReadIntervalTimeout = MAXDWORD;
//	TimeOuts.ReadTotalTimeoutMultiplier = 0;
//	TimeOuts.ReadTotalTimeoutConstant = 0;
//	//在读一次输入缓冲区的内容后读操作就立即返回，  
//	//而不管是否读入了要求的字符。  
//	//设定写超时  
//	TimeOuts.WriteTotalTimeoutMultiplier = 100;
//	TimeOuts.WriteTotalTimeoutConstant = 500;
//	SetCommTimeouts(hCom, &TimeOuts); //设置超时  
//
//	DCB dcb;
//	GetCommState(hCom, &dcb);
//	dcb.BaudRate = 115200; //波特率为9600  
//	dcb.ByteSize = 8; //每个字节有8位  
//	dcb.Parity = NOPARITY; //无奇偶校验位  
//	dcb.StopBits = 1; //两个停止位  
//	SetCommState(hCom, &dcb);
//	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
//	return hCom;
//}
//
//int ReadData(HANDLE handler, char* buffer)
//{
//	char readBuffer[512];
//	memset(readBuffer, 0, 512);
//	DWORD wCount = 512;//读取的字节数  
//	BOOL bReadStat;
//
//	bReadStat = ReadFile(handler, readBuffer, wCount, &wCount, NULL);
//	if (!bReadStat)
//	{
//		AfxMessageBox(L"读串口失败!");
//		return -1;
//	}
//	strcpy(buffer, readBuffer);
//	PurgeComm(handler, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
//	return 0;
//}
//
//int WriteData(HANDLE handler, char* buffer)
//{
//	unsigned long dwBytesWrite;
//	COMSTAT ComStat;
//	DWORD dwErrorFlags;
//	BOOL bWriteStat;
//	ClearCommError(handler, &dwErrorFlags, &ComStat);
//	dwBytesWrite = strlen(buffer);
//	bWriteStat = WriteFile(handler, buffer, dwBytesWrite, &dwBytesWrite, NULL);
//	if (!bWriteStat)
//	{
//		AfxMessageBox(L"写串口失败!");
//		return -1;
//	}
//	return 0;
//}


//void CTestmainView::OnBnClickedButton1()
//{
//	// TODO:  在此添加控件通知处理程序代码
//
//	GetErrInfo();
//	//日志文件处理		
//	if (errorNumber > 0 || systemcfg2.warn_baso || systemcfg2.warn_diluent || systemcfg2.warn_fix
//		|| systemcfg2.warn_hgb || systemcfg2.warn_rinse || systemcfg2.warn_waste)
//	{
//		if (errorNumber > 0)
//		{
//			ErrFlag = 1;
//			errorShowNum = 0;
//			ErrorTimer_Flag = TRUE;
//
//			DisplayErrMess();//显示错误信息，待处理
//
//			//UpdateErrMessage();//此处更新错误信息
//
//			SetTimer(ERROR_TIMER, 200, 0);
//		}
//	}
//}

void CTestmainView::deepClone(char * dest, char * src, int srcLength){
	for (int i= 0; i < srcLength; i++){
		*(dest+i) = *(src+i);
	}
}

/********************测试代码*****************************/
void CTestmainView::OnBnClickedButton1()
{
	//// TODO:  在此添加控件通知处理程序代码
	ULONGLONG size;
	CString strFilePath = "appdata.accdb";
	CFileStatus fileStatus;

	if (CFile::GetStatus(strFilePath, fileStatus))
	{
		size = fileStatus.m_size / 1024 / 1024;
	}
	if (size > 20)
	{
		MessageBox(_T("数据库已满，请手动备份数据库"));
		MessageBox(_T("数据库已满，将数据顶出"));
		CString filename;
		CString number;

		CString delete_patientdata = "delete from patientdata where ID = (select top 1  ID from patientdata order by ID)";
		CString delete_sampledata = "delete from patientdata where ID = (select top 1  ID from sampledata order by ID)";
		if (IDOK == MessageBox(L"确认删除？", L"提示", MB_YESNO | MB_ICONINFORMATION));
		{
			filename.Format(_T("appdata.accdb"));
			_ConnectionPtr m_pDB;
			_RecordsetPtr m_pRs;
			if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
				return;
			ExeSql(m_pDB, m_pRs, delete_patientdata);
			ExeSql(m_pDB, m_pRs, delete_sampledata);
			CloseDataBase(m_pDB, m_pRs);
			MessageBox(L"删除成功！");
			//	OnViewBack();
		}
	}
	USES_CONVERSION;
	GetPatientInfo(&patientdata);
	AddPatientRecord(&patientdata);
	



}

void CTestmainView::OnBnClickedButton2()
{
	//// TODO:  在此添加控件通知处理程序代码
	//CString cs;
	//cs = patientdata.age;

	////memcpy(&(*patientdata->age), &temp, sizeof((*patientdata->age)));
	//MessageBox(cs);
}


void CTestmainView::OnBnClickedButton3()
{
	//TRACE(_T("POLLTIME2\n"));
	//sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
	//PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	//PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);

	//TRACE(_T("rdata_sate[0]=%X\n"), rdata_state[0]);
	//PostMessage(WM_ACKSPI, rdata_state[0], 0);
}
/*******************************************************/