// WorkstationView.cpp : 实现文件
//
#include "stdafx.h"
#include "BCGPChartExample.h"
#include "WorkstationView.h"
#include "afxdialogex.h"


// CWorkstationView 对话框
//开机空白测试数据
bool			StartupBlankTestsflag2 = FALSE;				//为1时表示目前正在进行开机空白测试，需做两次
char			StartupBlankTestsTimes2;						//开机测试进行空白测试的次数<=2
float			StartupBlankTestswbc2;
float			StartupBlankTestsrbc2;
float			StartupBlankTestsplt2;
bool			IsBlankTest2 = FALSE;

char studyPara2[8][6];//研究参数:Blasts(%),Blasts(#),LEFT(%),LEFT(#),NRBC(%),NRBC(#),P-LCC(%),P-LCC(#)	//xx22  P-LCC(%),P-LCC(#)暂时没有

static unsigned char 	AlertMotorShow;	//电机错误显示为1，其它为0
static unsigned char 	NumOverwashfrequency;	//测试满washfrequency需要自动清洗  满为1，不满为0
static unsigned char 	DataBaseFull;	//数据库满(955-999)  955-999为1，其它为0
static unsigned char 	ReagentEmpty;	//试剂不足为1，其它为0


IMPLEMENT_DYNAMIC(CWorkstationView, CDialogEx)

CWorkstationView::CWorkstationView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkstationView::IDD, pParent)
{

}

CWorkstationView::~CWorkstationView()
{

}

void CWorkstationView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
}


BEGIN_MESSAGE_MAP(CWorkstationView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_WORKSHEET_TEST, &CWorkstationView::OnWorkstationtest)
	ON_WM_TIMER()
	ON_MESSAGE(WM_WORKSHEET_ACKSPI, &CWorkstationView::OnAckspi)
	ON_MESSAGE(WM_GETALLTASKINFO, &CWorkstationView::OnGetallTaskInfo)
	ON_MESSAGE(WM_WORKSHEET_CLEAN, &CWorkstationView::OnWorksheetClean)
END_MESSAGE_MAP()


// CWorkstationView 消息处理程序


HBRUSH CWorkstationView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CWorkstationView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}


BOOL CWorkstationView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	updatetabview();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CWorkstationView::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	

}


int CWorkstationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CWorkstationView::updatetabview()
{
	CRect rectTab;
	GetDlgItem(IDC_WORKSTATION_TAB)->GetWindowRect(&rectTab);
	ScreenToClient(&rectTab);

	m_workstationtab.Create(CBCGPTabWnd::STYLE_3D, rectTab, this, 1, CBCGPTabWnd::LOCATION_TOP);

	// m_Tasksheetpage=new CWorkstationTasksheet();
	 //m_Analysispage=new CWorkstationAnalysis();
	 //m_Resultpage=new CWorkstationResult();

	 m_Tasksheetpage.Create(IDD_WORKSTATION_TASKSHEET, &m_workstationtab);
	 m_Analysispage.Create(IDD_WORKSHEET_ANALYSIS,&m_workstationtab);
	 m_Resultpage.Create(IDD_WORKSTATION_RESULT, &m_workstationtab);

	 m_workstationtab.AddTab(&m_Tasksheetpage,L"工作列表",0);
	 m_workstationtab.AddTab(&m_Analysispage, L"分析", 1);
	 m_workstationtab.AddTab(&m_Resultpage, L"结果", 2);

	 CRect rc;
	 m_workstationtab.GetClientRect(rc);
	 m_workstationtab.SetResizeMode(CBCGPTabWnd::RESIZE_VERT);
	 rc.top += 27;
	 rc.bottom -= 5;
	 rc.left += 5;
	 rc.right -= 10;
	 m_Tasksheetpage.MoveWindow(&rc);
	 m_Analysispage.MoveWindow(&rc);
	 m_Resultpage.MoveWindow(&rc);

}

void CWorkstationView::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CWorkstationTasksheet::autogeneratetimes = 0;
	CDialogEx::OnClose();
}


void CWorkstationView::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CWorkstationTasksheet::autogeneratetimes = 0;
	CDialogEx::OnOK();
}


void CWorkstationView::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	CWorkstationTasksheet::autogeneratetimes = 0;
	CDialogEx::OnCancel();

}

bool  CWorkstationView::ErrorTimer_Flag = FALSE;


afx_msg LRESULT CWorkstationView::OnWorkstationtest(WPARAM wParam, LPARAM lParam)
{
	TRACE("===============Workstation Test==========\n");
	task_info* m_taskdata = (task_info*)wParam;
	TRACE("----%d------", m_taskdata->number);
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
	InitData(m_taskdata);
	NumFromBoot++;
	//向控制机发送测试命令
	DSP_status = Busy;
	if (m_taskdata->mode == WHOLEDIFF || m_taskdata->mode == DILUENTDIFF)
		sdata_cmd[0] = SPI_CMD_CBC5DIFF_MODE;
	else if (m_taskdata->mode == WHOLECBC || m_taskdata->mode == DILUENTCBC)
		sdata_cmd[0] = SPI_CMD_CBC_MODE;
	if (WAIT_OBJECT_0 == WaitForSingleObject(SendMutex, INFINITE))// 收到激发态的消息  
	{
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	}
	else
	{
		MessageBox(L"仪器运行中无法进行操作!", L"提醒!", MB_OK | MB_ICONINFORMATION);
		::SendMessage(m_Tasksheetpage, WM_RESTART, 0, 0);
		return 0;
	}
	statusShowMess = 1;
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


afx_msg LRESULT CWorkstationView::OnWorksheetClean(WPARAM wParam, LPARAM lParam)
{
	sdata_cmd[0] = SPI_CMD_STARTUP;
	if (WAIT_OBJECT_0 == WaitForSingleObject(SendMutex, INFINITE))// 收到激发态的消息  
	{
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	}
	else
	{
		MessageBox(L"仪器运行中无法进行操作!", L"提醒!", MB_OK | MB_ICONINFORMATION);
		::SendMessage(m_Tasksheetpage, WM_RESTART, 0, 0);
		return 0;
	}
	SetTimer(POLLTIME, 3000, 0);
	return 0;
}


void CWorkstationView::InitData(task_info* taskdata)
{
	unsigned int i;
	//默认字符为""
	patientdata2.number = taskdata->number;
	strcpy(patientdata2.name, taskdata->name);
	patientdata2.sex = taskdata->sex;
	patientdata2.rangetype = systemcfg.range.type;
	strcpy(patientdata2.age, taskdata->age);
	strcpy(patientdata2.code, taskdata->barcode);
	strcpy(patientdata2.technician, "");
	strcpy(patientdata2.doctor, taskdata->doctor);
	patientdata2.row = sampledata2.row;
	patientdata2.number = sampledata2.number;

	sampledata2.row = taskdata->row;
	sampledata2.number = taskdata->number;
	//WBC
	strcpy(sampledata2.wbcdata.wbc, "**.**");
	strcpy(sampledata2.wbcdata.lymp, "**.*");
	strcpy(sampledata2.wbcdata.neup, "**.*");
	strcpy(sampledata2.wbcdata.monop, "*.*");
	strcpy(sampledata2.wbcdata.eosp, "*.*");
	strcpy(sampledata2.wbcdata.basp, "*.*");
	strcpy(sampledata2.wbcdata.alyp, "*.*");
	strcpy(sampledata2.wbcdata.licp, "*.*");

	strcpy(sampledata2.wbcdata.lym, "*.**");
	strcpy(sampledata2.wbcdata.neu, "*.**");
	strcpy(sampledata2.wbcdata.mono, "*.**");
	strcpy(sampledata2.wbcdata.eos, "*.**");
	strcpy(sampledata2.wbcdata.bas, "*.**");
	strcpy(sampledata2.wbcdata.aly, "*.**");
	strcpy(sampledata2.wbcdata.lic, "*.**");
	//RBC
	strcpy(sampledata2.rbcdata.rbc, "*.**");
	strcpy(sampledata2.rbcdata.hgb, "***.*");
	strcpy(sampledata2.rbcdata.hct, "**.*");
	strcpy(sampledata2.rbcdata.mcv, "***.*");
	strcpy(sampledata2.rbcdata.mch, "**.*");
	strcpy(sampledata2.rbcdata.mchc, "***.*");
	strcpy(sampledata2.rbcdata.rdwcv, "**.*");
	strcpy(sampledata2.rbcdata.rdwsd, "**.*");
	//PLT
	strcpy(sampledata2.pltdata.plt, "***");
	strcpy(sampledata2.pltdata.mpv, "**.**");
	strcpy(sampledata2.pltdata.pct, "**.**");
	strcpy(sampledata2.pltdata.pdw, "**.*");
	strcpy(sampledata2.pltdata.plcr, "**.*");

	//散点图
	for (i = 0; i < MATRIX_DATA_MAX; i++)
		sampledata2.lmnegraph[i] = 1;
	//BASO直方图
	for (i = 0; i < 256; i++)
		sampledata2.basograph[i] = 1;
	//RBC直方图
	for (i = 0; i < 512; i++)
		sampledata2.rbcgraph[i] = 1;
	//PLT直方图
	for (i = 0; i < 256; i++)
		sampledata2.pltgraph[i] = 1;
	//界标
	for (i = 0; i < 9; i++)
		sampledata2.lmneflg[i] = 1;
	sampledata2.basoflg[0] = 1;
	for (i = 0; i < 2; i++)
		sampledata2.rbcflg[i] = 1;
	for (i = 0; i < 4; i++)
		sampledata2.pltflg[i] = 1;
	sampledata2.mode = systemcfg.mode;
	for (i = 0; i < 4; i++)
		sampledata2.flag_wrp[i] = 1;
	sampledata2.coeoflmne = 1.0;

	for (i = 0; i < 8; i++)
		strcpy(studyPara2[i], "**.*");
	//AfxMessageBox(_T("2829"));
}

void CWorkstationView::DisplayErrMess()
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

	}
	//AfxMessageBox(_T("3435"));
}

void CWorkstationView::GetErrInfo()
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


extern bool Allow_ASOnLine;
extern bool AS_OnLine;				//自动进样系统与主机建立连接-1(START)，未建立连接-0(OVER)
extern bool ASCur_EN;				//当前测试使能。1有效才能工作。请求血样，否则不请求血样(执行自动维护或提示数据库满，需临时暂停)


int		CWorkstationView::addtime = 0;
bool	CWorkstationView::TempReq_EN = FALSE;
int		CWorkstationView::cuptemp = 0;
int		CWorkstationView::oritemp_rea = 0;
int		CWorkstationView::oritemp_cup = 0;
int		CWorkstationView::reagenttemp = 0;
unsigned char	CWorkstationView::ErrFlag = 0;
unsigned char	CWorkstationView::IsBlocking = 0;
unsigned char	CWorkstationView::EN_Repeat = 0;
int				CWorkstationView::TimesofTest = 0;

void CWorkstationView::OnTimer(UINT_PTR nIDEvent)
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
				for (int i = 0; i < 3; i++)	//循环三次，防止数据传输异常
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
				if (reagenttemp < 200)
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
		PostMessage(WM_WORKSHEET_ACKSPI, rdata_state[0], 0);
		break;
	}
	default:
		break;
		
	}
	CDialogEx::OnTimer(nIDEvent);
}

afx_msg LRESULT CWorkstationView::OnAckspi(WPARAM wParam, LPARAM lParam)
{

	switch (wParam)
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
			MessageBox(_T("排液超时,请关机检查"), _T("警告!"), MB_OK | MB_ICONINFORMATION);
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
		m_datatrans.GetNormalTestData(systemcfg.mode, &sampledata2);

		//------------------------------------------------------------------------------------------------
		//日志文件的修改
		//试剂剩余量
		if (systemcfg2.warn_diluent || systemcfg2.warn_baso || systemcfg2.warn_fix || systemcfg2.warn_hgb
			|| systemcfg2.warn_rinse || systemcfg2.warn_waste)
		{
			if (WHOLEDIFF == systemcfg.mode || DILUENTDIFF == systemcfg.mode)
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
				if (systemcfg2.warn_fix)
				{
					if (logfile.regent.eoslyse > 10)
						logfile.regent.eoslyse = logfile.regent.eoslyse - 10;
					else
						logfile.regent.eoslyse = 0;
				}
				if (systemcfg2.warn_baso)
				{
					if (logfile.regent.baslyse > 21)
						logfile.regent.baslyse = logfile.regent.baslyse - 21;
					else
						logfile.regent.baslyse = 0;
				}
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
		}
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
				SetTimer(ERROR_TIMER, 200, 0);
			}
		}
		SetTimer(UPDATE_STATUS, 200, 0);
		//------------------------------------------------------------------------------------------------
		//数据接收成功，进行处理的过程
		//分析数据
		{
			//uchar* 	pIsSuper = (uchar*)GetWindowAdditionalData(hDlg);
			int		recv = 0;

			m_dataprocess.BasoLmneRbcPlt_2Analyse(&sampledata2);//没问题

			m_dataprocess.WbcBasoAnalysis(&sampledata2, pIsSuper);
			if (WHOLEDIFF == systemcfg.mode || DILUENTDIFF == systemcfg.mode)
			{
				recv = m_dataprocess.LmneAnalysis(&sampledata2, pIsSuper);	//必须放在BASO分析后面
				//若接收数据全部为0，则重新接收
				if (recv == -1)
				{
					for (int i = 0; i < 3; i++)
					{
						sdata_cmd[0] = SPI_CMD_REQLMNE;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (0 == PC_RECEIVE_FRAME((unsigned char*)sampledata2.lmnegraph, SPI_TYPE_LMNERES))
						{
							printf("LMNE transfer times=%d---------#\n", i + 1);
							break;
						}
					}
					recv = m_dataprocess.LmneAnalysis(&sampledata2, pIsSuper);
				}
			}
			m_dataprocess.HgbAnalysis(&sampledata2);		//必须放在RBC分析前面
			m_dataprocess.RbcAnalysis(&sampledata2, pIsSuper);
			m_dataprocess.PltAnalysis(&sampledata2);
		}
		//------------------------------------------------------------------------------------------------	
		if (!StartupBlankTestsflag2)	//不是开机空白测试
		{
			//向样本数据表插入记录
			AddSampleRecord(&sampledata2);
			//向病人信息表插入病人编号，注册以和病人数据表记录同步
			AddPatientRecord(&patientdata2);
			//----------------------------------------
			//是否需暂停自动进样系统工作进行维护操作
			DataBaseFull = 0;
			if (sampledata2.row >= 995 && sampledata2.row <= 999)//数据库995,996,997,998,999提示数据库备份，连续提示5次
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
				for (int i = 0; i < errorNumber; i++)//电机错误
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
		//----------
		PC_status = TEST_OVER;		//必须在SendMessage之前，在后会导致第二次开机空白测试不接受数据
		if (IsBlankTest2)
			IsBlankTest2 = FALSE;
		//------------------------------------------------
		if (StartupBlankTestsflag2)//开机测试  恢复到正常状态
		{
			StartupBlankTestsTimes2++;
			if (1 == StartupBlankTestsTimes2)
			{
				if (StartupBlankTestswbc2 < 0.3 && StartupBlankTestsrbc2 < 0.05 && StartupBlankTestsplt2 < 10)//对检测结果进行判断，第一次空白测试合格					
				{
					TRACE("Startup BlankTest first time Qualified----------\n");
					StartupBlankTestsflag2 = FALSE;

					TempReq_EN = TRUE;
				}
				else//第一次空白测试不合格
				{
					TRACE("Startup BlankTest first time not Qualified----------\n");
					TempReq_EN = FALSE;
					SendMessage(WM_MAINBLANKTEST, 0);	//进入空白测试
				}
			}
			else if (2 == StartupBlankTestsTimes2)
			{
				if (StartupBlankTestswbc2 < 0.3 && StartupBlankTestsrbc2 < 0.05 && StartupBlankTestsplt2 < 10)//对检测结果进行判断，第二次空白测试合格			
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
				StartupBlankTestsflag2 = FALSE;
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
		::SendMessage(m_Analysispage, WM_GETRESULT, (WPARAM)&sampledata2, 0);
		ReleaseMutex(SendMutex);
		InformWindowTheTask((sampledata2.number+1));
		//------------------------------------------------	
		break;
		//----------------------------------------
	default:
		break;
	}
	return 0;
}

void CWorkstationView::DealwithBlockErr(uchar CMD_Name, uchar ErrNum)
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


void CWorkstationView::SendCmdToDSP(uchar CMD_Name)
{
	char Mess[50];

	sdata_cmd[0] = CMD_Name;

	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME2, SPI_POLL_TIME3000, 0);
}

void CWorkstationView::InformWindowTheTask(int num)
{
	::SendMessage(m_Tasksheetpage, WM_STARTNEXTTASK, (WPARAM)num, 0);
}


afx_msg LRESULT CWorkstationView::OnGetallTaskInfo(WPARAM wParam, LPARAM lParam)
{
	m_alltask = (vector<task_info>*)wParam;
	::SendMessage(m_Analysispage, WM_GETALLTASKINFO, (WPARAM)m_alltask,0);
	return 0;
}


