// AddTaskView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "AddTaskView.h"
#include "afxdialogex.h"
#include "FilesOperation.h"


// CAddTaskView 对话框

IMPLEMENT_DYNAMIC(CAddTaskView, CDialogEx)

CAddTaskView::CAddTaskView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddTaskView::IDD, pParent)
	, m_taskmode(0)
{
	
	m_nFirstDayOfWeek = 1;
	GenerateNumAuto = false;
	hThread = NULL;
}

CAddTaskView::~CAddTaskView()
{
}

void CAddTaskView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDTASK_TESTTIME, m_testtime);
	DDX_Control(pDX, IDC_ADDTASK_SEX, m_addtasksex);
	DDX_Radio(pDX, IDC_TASKMODE_RADIO1, m_taskmode);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_CANCEL);
}

BEGIN_MESSAGE_MAP(CAddTaskView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_GETBARCODE, &CAddTaskView::OnGetbarcode)
	ON_BN_CLICKED(IDC_TASKMODE_RADIO1, &CAddTaskView::OnBnClickedTaskmodeRadio1)
	ON_BN_CLICKED(IDC_TASKMODE_RADIO2, &CAddTaskView::OnBnClickedTaskmodeRadio1)
END_MESSAGE_MAP()
// CAddTaskView 消息处理程序


HBRUSH CAddTaskView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


int CAddTaskView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}


BOOL CAddTaskView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	COleDateTime currenttime;
	currenttime = COleDateTime::GetCurrentTime();
	m_testtime.SizeToContent();
	m_testtime.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_testtime.SetDate(currenttime);
	m_testtime.SetFirstDayOfWeek(m_nFirstDayOfWeek);

	m_addtasksex.AddString(L"空");
	m_addtasksex.AddString(L"男");
	m_addtasksex.AddString(L"女");
	m_addtasksex.SetCurSel(0);
	
	InitTaskdata(m_task);
	//SetTimer(CHECK_BARCODEINPUT,100,0);
	DWORD dwThreadId2;
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hThread = CreateThread(NULL, 0, BarcodeCheck, LPVOID(this), 0, &dwThreadId2);
	if (hThread == NULL)
	{
		MessageBox(L"CreateThread   failed.", L"main", MB_OK);
	}
	else
	{
		//OutputDebugString(L"prepare   post   message\r\n");
		Sleep(1000);//等待线程创建好了   
		//CloseHandle(hThread);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



void CAddTaskView::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SetEvent(hEvent);
	CDialogEx::OnClose();
}


void CAddTaskView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}


void CAddTaskView::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (nType == 1) return;//最小化则什么都不做  
	// TODO: Add your message handler code here  
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_ADDTASK_NAME);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_ADDTASK_TESTTIME);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_ADDTASK_AGE);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_ADDTASK_SEX);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_ADDTASK_SAMPLENUM);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_ADDTASK_BARCODE);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_ADDTASK_DEPARTMENT);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_ADDTASK_DOCTOR);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_STATIC);
	ChangeSize(pWnd, cx, cy);
	GetClientRect(&m_rect);// 将变化后的对话框大小设为旧大小   

}


void CAddTaskView::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	SetEvent(hEvent);
	if (GetTaskInfo() == true)
	{
		CDialogEx::OnOK();
	}
	else 
		CDialogEx::OnCancel();	
}


void CAddTaskView::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	SetEvent(hEvent);
	CDialogEx::OnCancel();
}

void CAddTaskView::ChangeSize(CWnd *pWnd, int cx, int cy)
{
	if (pWnd)  //判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建	
	{
		CRect rect;   //获取控件变化前的大小  
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标

		//    cx/m_rect.Width()为对话框在横向的变化比例
		rect.left = rect.left*cx / m_rect.Width();//调整控件大小
		rect.right = rect.right*cx / m_rect.Width();
		rect.top = rect.top*cy / m_rect.Height();
		rect.bottom = rect.bottom*cy / m_rect.Height();
		pWnd->MoveWindow(rect);//设置控件大小
	}
}

bool CAddTaskView::GetTaskInfo()
{
	USES_CONVERSION;
	UpdateData(TRUE);
	CString name,barcode,doctor,age,department,testtime,number,status;
	int sex;
	int len = 0;

	if (m_taskmode == 1)
	{
		m_task.taskmode = 1;
		return true;
	}
	GetDlgItem(IDC_ADDTASK_NAME)->GetWindowText(name);
	memset(m_task.name, 0, sizeof(m_task.name));
	sprintf(m_task.name, "%s", W2A(name));
	
	GetDlgItem(IDC_ADDTASK_AGE)->GetWindowText(age);
	memset(m_task.age, 0, sizeof(m_task.age));
	sprintf(m_task.age, "%s", W2A(age));

	len = strlen(m_task.age);
	for (int i = 0; i < len; i++)
	{
		if (m_task.age[i] < '0' || m_task.age[i] > '9')
		{
			if (systemcfg.language == CHINESE)
				MessageBox(L"输入年龄中含有非法字符!", L"警告!", MB_OK | MB_ICONINFORMATION);	
			return false;
		}
	}

	GetDlgItem(IDC_ADDTASK_BARCODE)->GetWindowText(barcode);
	memset(m_task.barcode, 0, sizeof(m_task.barcode));
	sprintf(m_task.barcode, "%s", W2A(barcode));

	GetDlgItem(IDC_ADDTASK_DOCTOR)->GetWindowText(doctor);
	memset(m_task.doctor, 0, sizeof(m_task.doctor));
	sprintf(m_task.doctor, "%s", W2A(doctor));

	GetDlgItem(IDC_ADDTASK_DEPARTMENT)->GetWindowText(department);
	memset(m_task.department, 0, sizeof(m_task.department));
	sprintf(m_task.department, "%s", W2A(department));

	sex = m_addtasksex.GetCurSel();
	m_task.sex = sex;

	COleDateTime strtime;
	strtime=m_testtime.GetDate();
	testtime.Format(TEXT("%04d%02d%02d"), strtime.GetYear(), strtime.GetMonth(), strtime.GetDay());
	memset(m_task.time, 0, sizeof(m_task.time));
	sprintf(m_task.time, "%s", W2A(testtime));

	GetDlgItem(IDC_ADDTASK_SAMPLENUM)->GetWindowText(number);
	if (number == "")
	{
		GetRowNo(m_task.row, m_task.number);//获取本次测试的记录号及编号
		GenerateNumAuto = true;
	}
	else
	{
		m_task.number = _ttoi(number);
		GenerateNumAuto = false;
	}

	ReadSystemcfgFile();//测试模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC
	m_task.mode = systemcfg.mode;

	TRACE(L"%d\n",m_task.number);
	status = "未进行";
	memset(m_task.status, 0, sizeof(m_task.status));
	sprintf(m_task.status, "%s", W2A(status));
	return true;
}

void CAddTaskView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{

	default:
			break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

DWORD WINAPI CAddTaskView::BarcodeCheck(LPVOID lpParam)
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
	
	SetEvent(TestmainEvent);
	CAddTaskView   *m_Dlg = (CAddTaskView*)lpParam;

	CRS232  m_rs232;
	uchar 	recvdata[100] = { 0 };
	CString barcode;
	USES_CONVERSION;
	for (int i = 0; i < 100; i++)
		recvdata[i] = 0;
	while (1)
	{
		m_rs232.ComRd(6, recvdata, 100,9600);
		barcode = A2W((char*)recvdata);
		if (barcode != "")
		{
			TRACE(barcode + "\n");
			m_Dlg->m_barcode = barcode;
			::PostMessage(m_Dlg->m_hWnd, WM_GETBARCODE, 0, 0);
		}
		Sleep(100);
		if (WAIT_OBJECT_0 == WaitForSingleObject(hEvent, INFINITE))// 收到激发态的消息  
		{
			AfxMessageBox(L"ADD task 退出线程");
			return 0;//正常退出  
		}
	}
	AfxMessageBox(L"退出线程2");
	return  0;
}

afx_msg LRESULT CAddTaskView::OnGetbarcode(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_ADDTASK_BARCODE)->SetWindowText(m_barcode);
	return 0;
}


void CAddTaskView::OnBnClickedTaskmodeRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	switch (m_taskmode)
	{

	case 0:
		FreetheControl();
		
		break;
	case 1:
		LocktheControl();
		break;
	default:
		FreetheControl();
		break;
	}
}

void CAddTaskView::LocktheControl()
{
	GetDlgItem(IDC_ADDTASK_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADDTASK_TESTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADDTASK_AGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADDTASK_SEX)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADDTASK_SAMPLENUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADDTASK_BARCODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADDTASK_DEPARTMENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADDTASK_DOCTOR)->EnableWindow(FALSE);

}

void CAddTaskView::FreetheControl()
{
	GetDlgItem(IDC_ADDTASK_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_ADDTASK_TESTTIME)->EnableWindow(TRUE);
	GetDlgItem(IDC_ADDTASK_AGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_ADDTASK_SEX)->EnableWindow(TRUE);
	GetDlgItem(IDC_ADDTASK_SAMPLENUM)->EnableWindow(TRUE);
	GetDlgItem(IDC_ADDTASK_BARCODE)->EnableWindow(TRUE);
	GetDlgItem(IDC_ADDTASK_DEPARTMENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_ADDTASK_DOCTOR)->EnableWindow(TRUE);

}

void CAddTaskView::InitTaskdata(task_info &taskdata)
{
	CString status;
	USES_CONVERSION;
	taskdata.number = 0000000000;
	strcpy(taskdata.name, "");
	taskdata.sex = 1;
	taskdata.row = 0;
	strcpy(taskdata.age, "");
	strcpy(taskdata.time, "");
	status = "未进行";
	memset(m_task.status, 0, sizeof(m_task.status));
	sprintf(m_task.status, "%s", W2A(status));
	strcpy(taskdata.barcode, "");
	strcpy(taskdata.department, "");
	strcpy(taskdata.doctor, "");
	taskdata.taskmode = 0;
}

