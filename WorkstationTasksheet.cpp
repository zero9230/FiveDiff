// WorkstationTasksheet.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "WorkstationTasksheet.h"
#include "afxdialogex.h"
#include "AddTaskView.h"
#include "FilesOperation.h"
#include <map>

// CWorkstationTasksheet 对话框

IMPLEMENT_DYNAMIC(CWorkstationTasksheet, CDialogEx)

CWorkstationTasksheet::CWorkstationTasksheet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkstationTasksheet::IDD, pParent)
{
	TaskNum = 0;
	autogenerate = false;
}

CWorkstationTasksheet::~CWorkstationTasksheet()
{

}

void CWorkstationTasksheet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WORKSTATION_TASKLIST, m_WorkstationTasklist);
	DDX_Control(pDX, IDC_ADDTASK, m_addtask);
	DDX_Control(pDX, IDC_DELETETASK, m_deletetask);
	DDX_Control(pDX, IDC_STARTEXECUTION, m_startexecute);
	DDX_Control(pDX, IDC_CLEARSHEET, m_clearsheet);
}


BEGIN_MESSAGE_MAP(CWorkstationTasksheet, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ADDTASK, &CWorkstationTasksheet::OnBnClickedAddtask)
	ON_BN_CLICKED(IDC_DELETETASK, &CWorkstationTasksheet::OnBnClickedDeletetask)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_STARTEXECUTION, &CWorkstationTasksheet::OnBnClickedStartexecution)
	ON_MESSAGE(WM_STARTNEXTTASK, &CWorkstationTasksheet::OnStartNextTask)
	ON_BN_CLICKED(IDC_CLEARSHEET, &CWorkstationTasksheet::OnBnClickedClearsheet)
	ON_MESSAGE(WM_RESTART, &CWorkstationTasksheet::OnRestart)
END_MESSAGE_MAP()


// CWorkstationTasksheet 消息处理程序


bool CWorkstationTasksheet::InitTaskList()
{
	// 获取编程语言列表视图控件的位置和大小   
	CRect m_rect;
	GetClientRect(&m_rect);

	int i=0;
	m_rect.top += 20;
	m_rect.bottom -= 35;
	m_rect.left += 0;
	m_rect.right -= 0;
	m_WorkstationTasklist.MoveWindow(m_rect);


	CRect rect;
	m_WorkstationTasklist.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_WorkstationTasklist.SetExtendedStyle(m_WorkstationTasklist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_WorkstationTasklist.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_WorkstationTasklist.SetRowHeigt(20);
	
	m_WorkstationTasklist.DeleteAllItems();//清空列表刷新

	m_WorkstationTasklist.InsertColumn(0, _T("序列号"), LVCFMT_CENTER, rect.Width() / 14, 0);
	m_WorkstationTasklist.InsertColumn(1, _T("样品编号"), LVCFMT_CENTER, rect.Width() / 7, 1);
	m_WorkstationTasklist.InsertColumn(2, _T("病人姓名"), LVCFMT_CENTER, rect.Width() / 7, 2);
	m_WorkstationTasklist.InsertColumn(3, _T("性别"), LVCFMT_CENTER, rect.Width() / 14, 3);
	m_WorkstationTasklist.InsertColumn(4, _T("年龄"), LVCFMT_CENTER, rect.Width() / 14, 4);
	m_WorkstationTasklist.InsertColumn(5, _T("标本条码"), LVCFMT_CENTER, rect.Width() / 7, 5);
	m_WorkstationTasklist.InsertColumn(6, _T("检验日期"), LVCFMT_CENTER, rect.Width() / 14, 6);
	m_WorkstationTasklist.InsertColumn(7, _T("检测模式"), LVCFMT_CENTER, rect.Width() / 7, 7);
	m_WorkstationTasklist.InsertColumn(8, _T("科室"), LVCFMT_CENTER, rect.Width() / 14, 8);
	m_WorkstationTasklist.InsertColumn(9, _T("状态"), LVCFMT_CENTER, rect.Width() / 14, 9);

	
	//此处从数据库获取tasksheet的记录
	CString select_tasksheet = L"select * from tasksheet ";
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	CString varStr;//用于将var转为string的中间变量，方便显示
	CString filename;
	CString index;//序号
	filename.Format(L"appdata.accdb");
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return false;
	ExeSql(m_pDB, m_pRs, select_tasksheet);
	
	try{
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
			
			m_WorkstationTasklist.InsertItem(i, _T(""));
			

			
			index.Format(L"%d", i);
			m_WorkstationTasklist.SetItemText(i, 0, index);

			var = m_pRs->GetCollect("number");			
			if (var.vt != VT_NULL)
				varStr = (LPCSTR)_bstr_t(var);
			m_WorkstationTasklist.SetItemText(i, 1, varStr);

			var = m_pRs->GetCollect("name");
			if (var.vt != VT_NULL)
				varStr = (LPCSTR)_bstr_t(var);
			m_WorkstationTasklist.SetItemText(i, 2, varStr);

			var = m_pRs->GetCollect("sex");
			if (var.vt != VT_NULL)
				varStr = (LPCSTR)_bstr_t(var);
			m_WorkstationTasklist.SetItemText(i, 3, varStr);

			var = m_pRs->GetCollect("age");
			if (var.vt != VT_NULL)
				varStr = (LPCSTR)_bstr_t(var);
			m_WorkstationTasklist.SetItemText(i, 4, varStr);

			var = m_pRs->GetCollect("barcode");
			if (var.vt != VT_NULL)
				varStr = (LPCSTR)_bstr_t(var);
			m_WorkstationTasklist.SetItemText(i, 5, varStr);

			var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
				varStr = (LPCSTR)_bstr_t(var);
			m_WorkstationTasklist.SetItemText(i, 6, varStr);

			var = m_pRs->GetCollect("status");
			if (var.vt != VT_NULL)
				varStr = (LPCSTR)_bstr_t(var);
			m_WorkstationTasklist.SetItemText(i, 9, varStr);


			i++;
			m_pRs->MoveNext();

		}

	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}
	return TRUE;


}


HBRUSH CWorkstationTasksheet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


int CWorkstationTasksheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

//程序初始化入口
BOOL CWorkstationTasksheet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitTaskList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CWorkstationTasksheet::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO:  在此处添加消息处理程序代码
	if (nType == 1) return;//最小化则什么都不做  
	// TODO: Add your message handler code here  
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_WORKSTATION_TASKLIST);
	ChangeSize(pWnd, cx, cy);
	pWnd = GetDlgItem(IDC_BUTTON1);
	ChangeSize(pWnd, cx, cy);
	GetClientRect(&m_rect);// 将变化后的对话框大小设为旧大小   
}


void CWorkstationTasksheet::ChangeSize(CWnd *pWnd, int cx, int cy)
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

void CWorkstationTasksheet::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}


void CWorkstationTasksheet::OnBnClickedAddtask()
{
	// TODO:  在此添加控件通知处理程序代码
	CAddTaskView  m_addtaskview;


	if (m_addtaskview.DoModal()==IDOK)
	{
		m_tasksheettask = m_addtaskview.m_task;
		autogenerate = m_addtaskview.GenerateNumAuto;
		if (autogenerate == true)
		{
			autogeneratetimes++;
		}
		AddSingleTask(&m_tasksheettask);
		m_alltask.push_back(m_tasksheettask);

	}
}


int	CWorkstationTasksheet::autogeneratetimes=0;

void CWorkstationTasksheet::AddSingleTask(task_info* taskdata)
{
	CString name, barcode, doctor, age, department, testtime, number, status,NO;
	CString sex,testmode;
	USES_CONVERSION;

	NO.Format(L"%d",TaskNum+1);
	name = A2W(taskdata->name);
	doctor = A2W(taskdata->doctor);
	age = A2W(taskdata->age);
	barcode = A2W(taskdata->barcode);
	department = A2W(taskdata->department);
	testtime = A2W(taskdata->time);
	taskdata->row += TaskNum;
	if (autogenerate == true)
	{
		taskdata->number = taskdata->number + autogeneratetimes - 1;
	}
	number.Format(L"%d", taskdata->number);
	status = A2W(taskdata->status);
	if (taskdata->sex == 0)
		sex = "空";
	else if (taskdata->sex == 1)
		sex = "男";
	else
		sex = "女";
	ReadSystemcfgFile();
	if (systemcfg.mode == 0)//测试模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC
		testmode = "全血+CBC5DIFF";
	else if (systemcfg.mode == 1)
		testmode = "全血+CBC";
	else if (systemcfg.mode == 2)
		testmode = "预稀释+CBC5DIFF";
	else testmode = "预稀释+CBC";


	if (taskdata->taskmode == 1)
	{
		NO.Format(L"%d", TaskNum + 1);
		name = "";
		testmode = "清洗";
	}

	m_WorkstationTasklist.InsertItem(TaskNum, L"任务");
	m_WorkstationTasklist.SetItemText(TaskNum, 0, NO);
	m_WorkstationTasklist.SetItemText(TaskNum, 1, number);
	m_WorkstationTasklist.SetItemText(TaskNum, 2, name);
	m_WorkstationTasklist.SetItemText(TaskNum, 3, sex);
	m_WorkstationTasklist.SetItemText(TaskNum, 4, age);
	m_WorkstationTasklist.SetItemText(TaskNum, 5, barcode);
	m_WorkstationTasklist.SetItemText(TaskNum, 6, testtime);
	m_WorkstationTasklist.SetItemText(TaskNum, 7, testmode);
	m_WorkstationTasklist.SetItemText(TaskNum, 8, department);
	m_WorkstationTasklist.SetItemText(TaskNum, 9, status);
	TaskNum++;
	//MessageBox(status);
	CString year = testtime.Left(4);
	CString month = testtime.Mid(4, 2);
	CString day = testtime.Right(2);
	CString date = year + "/" + month + "/" + day;
	//MessageBox(year);
	//MessageBox(month);
	//MessageBox(day);

	//此处为将工作单中的数据添加到数据库中
	// 此处需要注意，mode和status如何设计尚未查明，以及department属性未在数据库中设计
	//需要维护样品编号的连续性

	CString insert_tasksheet = L"insert into [tasksheet](row,[number],name,sex,age,barcode,[time],mode,status) values('"+NO+"','"+number+"','"+name+"','"+sex+"','"+age+"','"+barcode+"','"+date+"','1','1');";
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;
	CString filename;
	filename.Format(L"appdata.accdb");
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	ExeSql(m_pDB, m_pRs, insert_tasksheet);
	MessageBox(L"add task successfully !");

	CloseDataBase(m_pDB, m_pRs);
}



void CWorkstationTasksheet::OnBnClickedDeletetask()
{
	// TODO:  在此添加控件通知处理程序代码
	POSITION pos = m_WorkstationTasklist.GetFirstSelectedItemPosition();
	if (pos == NULL&&m_WorkstationTasklist.GetNextSelectedItem(pos) < m_WorkstationTasklist.GetItemCount())
	{
		MessageBox(L"没有任务被选中!", L"提示!", MB_OK | MB_ICONINFORMATION);
		return;
	}
	else
	{
		int nItem = m_WorkstationTasklist.GetNextSelectedItem(pos);
		CString nItemTemp;
		nItemTemp.Format(_T("%d"), m_WorkstationTasklist.GetItemCount());
		MessageBox(nItemTemp);

		
		TRACE1("Item %d was selected!\n", nItem);
		
		//此处代码执行删除目标记录，并且维护编号number
		if (nItem < m_WorkstationTasklist.GetItemCount())
		{





			//int sum = m_alltask.size();
			auto it = m_alltask.begin() + nItem;
			it=m_alltask.erase(it);
			TaskNum--;
			autogeneratetimes--;
			for (it; it != m_alltask.end(); it++)
			{
				it->number = it->number - 1;
				TRACE(L"%d\n",it->number);
			}
			UpdateTaskList(m_alltask);
		}
	}
}

//将数据库和内存中的数据同步显示到UI控件中
void CWorkstationTasksheet::UpdateTaskList(vector<task_info> taskdata)
{

	CString name, barcode, doctor, age, department, testtime, number, status, NO;
	CString sex, testmode;
	USES_CONVERSION;
	m_WorkstationTasklist.DeleteAllItems();
	int sum = taskdata.size();
	for (int i = 0; i < sum; i++)
	{
		NO.Format(L"%d", i + 1);
		name = A2W(taskdata[i].name);
		doctor = A2W(taskdata[i].doctor);
		age = A2W(taskdata[i].age);
		barcode = A2W(taskdata[i].barcode);
		department = A2W(taskdata[i].department);
		testtime = A2W(taskdata[i].time);

		number.Format(L"%d", taskdata[i].number);
		status = A2W(taskdata[i].status);
		if (taskdata[i].sex == 0)
			sex = "空";
		else if (taskdata[i].sex == 1)
			sex = "男";
		else
			sex = "女";
		switch (taskdata[i].mode)//测试模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC
		{
		case 0:
			testmode = "全血+CBC5DIFF";
			break;
		case 1:
			testmode = "全血+CBC";
			break;
		case 2:
			break;
			testmode = "预稀释+CBC5DIFF";
		case 3:
			testmode = "预稀释+CBC";
			break;
		default:
			break;
		}
		m_WorkstationTasklist.InsertItem(i, L"任务");
		m_WorkstationTasklist.SetItemText(i, 0, NO);
		m_WorkstationTasklist.SetItemText(i, 1, number);
		m_WorkstationTasklist.SetItemText(i, 2, name);
		m_WorkstationTasklist.SetItemText(i, 3, sex);
		m_WorkstationTasklist.SetItemText(i, 4, age);
		m_WorkstationTasklist.SetItemText(i, 5, barcode);
		m_WorkstationTasklist.SetItemText(i, 6, testtime);
		m_WorkstationTasklist.SetItemText(i, 7, testmode);
		m_WorkstationTasklist.SetItemText(i, 8, department);
		m_WorkstationTasklist.SetItemText(i, 9, status);
	}
}

void CWorkstationTasksheet::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}

void CWorkstationTasksheet::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CWorkstationTasksheet::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}

//number：任务下标；process：状态标号
void CWorkstationTasksheet::UpdateTaskStatus(int number,int process)
{
	// TODO:  在此添加专用代码和/或调用基类
	switch (process)
	{
	case 0:
		m_WorkstationTasklist.SetItemText(number,9,L"未进行");
		memset(m_alltask[number].status, 0, sizeof(m_alltask[number].status));
		sprintf(m_alltask[number].status, "未进行");
		break;
	case 1:
		m_WorkstationTasklist.SetItemText(number, 9, L"测试进行中");
		memset(m_alltask[number].status, 0, sizeof(m_alltask[number].status));
		sprintf(m_alltask[number].status, "测试进行中");
		break;
	case 2:
		m_WorkstationTasklist.SetItemText(number, 9, L"测试结束");
		memset(m_alltask[number].status, 0, sizeof(m_alltask[number].status));
		sprintf(m_alltask[number].status, "测试结束");
		break;
	case 3:
		m_WorkstationTasklist.SetItemText(number, 9, L"测试失败");
		memset(m_alltask[number].status, 0, sizeof(m_alltask[number].status));
		sprintf(m_alltask[number].status, "测试失败");
		break;
	default:
		break;
	}
}

int	CWorkstationTasksheet::startnum=0;
void CWorkstationTasksheet::OnBnClickedStartexecution()
{
	// TODO:  在此添加控件通知处理程序代码
	int tasknum;
	tasknum=m_WorkstationTasklist.GetItemCount();
	if (tasknum == 0)
	{
		MessageBox(L"无任务!", L"提示!", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (CheckDifferent())//判重
	{
		if (MessageBox(L"有重复样品，请确认是否继续!", L"提示!", MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
		{
			
			return;
		}
	}
	
	MessageBox(L"before1");
	startnum = m_alltask[0].number;//此处有问题
	
	LockTheButton();
	
	SendMessage(WM_STARTNEXTTASK,(WPARAM)startnum,0);
	//
}
//判断是否有重复样品，以条码号为判断标准，有重复返回true，无重复返回false
bool CWorkstationTasksheet::CheckDifferent()
{
	int sum = m_WorkstationTasklist.GetItemCount();
	//vector<CString> barcode;
	map<CString,bool> barcode;
	for (int i = 0; i < sum; i++)
	{
		if (barcode.find(m_WorkstationTasklist.GetItemText(i, 5)) == barcode.end() )//当前的map中没有找到重复元素
		{
			barcode[m_WorkstationTasklist.GetItemText(i, 5)]=true;//将该元素（已去重）加入集合中
		}
		else
		{
			if(m_WorkstationTasklist.GetItemText(i, 5) != "")//重复的元素不是空字符串，则是确实的重复条码，确定为重复
				return true;
			else continue;
		}
	}
	return false;
}

void CWorkstationTasksheet::LockTheButton()
{
	GetDlgItem(IDC_ADDTASK)->EnableWindow(false);
	GetDlgItem(IDC_DELETETASK)->EnableWindow(false);
	GetDlgItem(IDC_STARTEXECUTION)->EnableWindow(false);
	GetDlgItem(IDC_CLEARSHEET)->EnableWindow(false);
}

void CWorkstationTasksheet::FreeTheButton()
{
	GetDlgItem(IDC_ADDTASK)->EnableWindow(true);
	GetDlgItem(IDC_DELETETASK)->EnableWindow(true);
	GetDlgItem(IDC_STARTEXECUTION)->EnableWindow(true);
	GetDlgItem(IDC_CLEARSHEET)->EnableWindow(true);
}

afx_msg LRESULT CWorkstationTasksheet::OnStartNextTask(WPARAM wParam, LPARAM lParam)
{
	int sum;
	int tasknum = (int)wParam;
	int Serialnum=0;
	bool numexit = false;
	TRACE(L"------%d-------\n",tasknum);
	sum = m_WorkstationTasklist.GetItemCount();
	for (int i = 0; i < sum; i++)
	{
		CString number;
		CString number_str;
		number_str.Format(L"%d",tasknum);
		number=m_WorkstationTasklist.GetItemText(i,1);
		if (number_str == number)
		{
			Serialnum = i;
			numexit = true;
			break;
		}
	}
	if (numexit == false)
	{
		Serialnum = sum;
	}

	if (Serialnum > 0)
	{
		UpdateTaskStatus(Serialnum - 1, 2);
	}
	TRACE("---------%d-------------\n",numexit);
	if (numexit == false)
	{
		MessageBox(L"无待完成任务，请添加!", L"提示!", MB_OKCANCEL | MB_ICONINFORMATION);
		GetDlgItem(IDC_CLEARSHEET)->EnableWindow(true);
		return 0;
	}
	if (m_alltask[Serialnum].taskmode == 0)
	{
		MessageBox(L"请准备好样品!", L"提示", MB_OK | MB_ICONINFORMATION);
	}

	UpdateTaskStatus(Serialnum, 1);
	CWnd* pWnd = GetParent()->GetParent();
	if (m_alltask[Serialnum].taskmode == 0)
	{
		::SendMessage(pWnd->m_hWnd, WM_WORKSHEET_TEST, (WPARAM)&m_alltask[Serialnum], 0);
	}
	else if (m_alltask[Serialnum].taskmode == 1)
	{
		::SendMessage(pWnd->m_hWnd, WM_WORKSHEET_CLEAN, (WPARAM)&m_alltask[Serialnum], 0);
	}
	::SendMessage(pWnd->m_hWnd, WM_GETALLTASKINFO, (WPARAM)&m_alltask, 0);
	return 0;
}


void CWorkstationTasksheet::OnBnClickedClearsheet()
{
	// TODO:  在此添加控件通知处理程序代码
	m_WorkstationTasklist.DeleteAllItems();
	m_alltask.erase(m_alltask.begin(), m_alltask.end());
	FreeTheButton();
	TaskNum = 0;
}


afx_msg LRESULT CWorkstationTasksheet::OnRestart(WPARAM wParam, LPARAM lParam)
{
	FreeTheButton();
	return 0;
}
