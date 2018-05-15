// WorkstationAnalysis.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "WorkstationAnalysis.h"
#include "afxdialogex.h"


// CWorkstationAnalysis 对话框

IMPLEMENT_DYNAMIC(CWorkstationAnalysis, CDialogEx)

CWorkstationAnalysis::CWorkstationAnalysis(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkstationAnalysis::IDD, pParent)
{

}

CWorkstationAnalysis::~CWorkstationAnalysis()
{

}

void CWorkstationAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANALYSIS_LIST, m_analysisList);

}


BEGIN_MESSAGE_MAP(CWorkstationAnalysis, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_GETALLTASKINFO, &CWorkstationAnalysis::OnGetallTaskInfo)
	ON_MESSAGE(WM_GETRESULT, &CWorkstationAnalysis::OnGetresult)
END_MESSAGE_MAP()


// CWorkstationAnalysis 消息处理程序


HBRUSH CWorkstationAnalysis::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CWorkstationAnalysis::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码

	CWnd *pWnd;

}

void CWorkstationAnalysis::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}

BOOL CWorkstationAnalysis::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	InitAnaliysisList();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CWorkstationAnalysis::ChangeSize(CWnd *pWnd, int cx, int cy)
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

afx_msg LRESULT CWorkstationAnalysis::OnGetallTaskInfo(WPARAM wParam, LPARAM lParam)
{
	m_alltask = (vector<task_info>*)wParam;
	return 0;
}


afx_msg LRESULT CWorkstationAnalysis::OnGetresult(WPARAM wParam, LPARAM lParam)
{
	sampledata = (sample_info*)wParam;
	int num = GetthetaskSerialNum(sampledata);
	FillResultInfo(sampledata, &((*m_alltask)[num]));
	UpdateAnaliysisList(num+1);
	return 0;
}

int CWorkstationAnalysis::GetthetaskSerialNum(sample_info* sampledata)
{
	int  sum;
	int  Serialnum = 0;
	bool numexit = false;
	CString numberofresult;
	numberofresult.Format(L"%d",sampledata->number);
	sum = m_alltask->size();
	for (auto it = m_alltask->begin(); it != m_alltask->end(); it++, Serialnum++)
	{
		CString number_temp;
		number_temp.Format(L"%d", it->number);
		if (numberofresult == number_temp)
		{
			numexit = true;
			break;
		}
	}
	return Serialnum;
}

void CWorkstationAnalysis::InitAnaliysisList()
{
	CRect rect;
	m_analysisList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_analysisList.SetExtendedStyle(m_analysisList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_analysisList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_analysisList.SetRowHeigt(20);

	m_analysisList.DeleteAllItems();//清空列表刷新

	m_analysisList.InsertColumn(0, _T("序列号"), LVCFMT_CENTER, rect.Width() / 7, 0);
	m_analysisList.InsertColumn(1, _T("样品编号"), LVCFMT_CENTER, rect.Width() *2/ 7, 1);
	m_analysisList.InsertColumn(2, _T("病人姓名"), LVCFMT_CENTER, rect.Width() *2/ 7, 2);
	m_analysisList.InsertColumn(3, _T("检测模式"), LVCFMT_CENTER, rect.Width() *2/ 7, 3);
	
}

void CWorkstationAnalysis::UpdateAnaliysisList(int num)
{
	m_analysisList.DeleteAllItems();
	USES_CONVERSION;
	if (m_alltask->size() >= 2)
	{
		if (num <= (m_alltask->size() - 2))
		{
			CString num1, samplenum1, patientname1, testmode1;
			CString num2, samplenum2, patientname2, testmode2;

			num1.Format(L"%d", num);
			samplenum1.Format(L"%d", (*m_alltask)[num].number);
			patientname1 = A2W((*m_alltask)[num].name);
			switch ((*m_alltask)[num].mode)//测试模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC
			{
			case 0:
				testmode1 = "全血+CBC5DIFF";
				break;
			case 1:
				testmode1 = "全血+CBC";
				break;
			case 2:
				break;
				testmode1 = "预稀释+CBC5DIFF";
			case 3:
				testmode1 = "预稀释+CBC";
				break;
			default:
				break;
			}
			m_analysisList.InsertItem(0, L"序号");
			m_analysisList.SetItemText(0, 0, num1);
			m_analysisList.SetItemText(0, 1, samplenum1);
			m_analysisList.SetItemText(0, 2, patientname1);
			m_analysisList.SetItemText(0, 3, testmode1);

			num2.Format(L"%d", num + 1);
			samplenum2.Format(L"%d", (*m_alltask)[num + 1].number);
			patientname2 = A2W((*m_alltask)[num + 1].name);
			switch ((*m_alltask)[num + 1].mode)//测试模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC
			{
			case 0:
				testmode1 = "全血+CBC5DIFF";
				break;
			case 1:
				testmode1 = "全血+CBC";
				break;
			case 2:
				break;
				testmode1 = "预稀释+CBC5DIFF";
			case 3:
				testmode1 = "预稀释+CBC";
				break;
			default:
				break;
			}
			m_analysisList.InsertItem(1, L"序号");
			m_analysisList.SetItemText(1, 0, num2);
			m_analysisList.SetItemText(1, 1, samplenum2);
			m_analysisList.SetItemText(1, 2, patientname2);
			m_analysisList.SetItemText(1, 3, testmode2);
		}
	}
	
	if (num == (m_alltask->size() - 1))
	{
		CString num1, samplenum1, patientname1, testmode1;
		CString num2;

		num1.Format(L"%d", num);
		num2.Format(L"%d",num+1);
		samplenum1.Format(L"%d", (*m_alltask)[num].number);
		patientname1 = A2W((*m_alltask)[num].name);

		switch ((*m_alltask)[num].mode)//测试模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC
		{
		case 0:
			testmode1 = "全血+CBC5DIFF";
			break;
		case 1:
			testmode1 = "全血+CBC";
			break;
		case 2:
			break;
			testmode1 = "预稀释+CBC5DIFF";
		case 3:
			testmode1 = "预稀释+CBC";
			break;
		default:
			break;
		}
		m_analysisList.InsertItem(0, L"序号");
		m_analysisList.SetItemText(0, 0, num1);
		m_analysisList.SetItemText(0, 1, samplenum1);
		m_analysisList.SetItemText(0, 2, patientname1);
		m_analysisList.SetItemText(0, 3, testmode1);

		m_analysisList.InsertItem(1, L"序号");
		m_analysisList.SetItemText(1, 0, num2);
	}
	if (num > (m_alltask->size() - 1))
	{
		CString num1, num2;
		num1.Format(L"%d", num);
		num2.Format(L"%d", num + 1);

		m_analysisList.InsertItem(0, L"序号");
		m_analysisList.SetItemText(0, 0, num1);

		m_analysisList.InsertItem(1, L"序号");
		m_analysisList.SetItemText(1, 0, num2);
	}
}

void CWorkstationAnalysis::FillResultInfo(sample_info* sampledata, task_info* taskdata)
{

	USES_CONVERSION;
	CString serialnum, samplenum, paitientname, sex, age, testmode, testtime, barcode, department;
	int serialnum_temp = GetthetaskSerialNum(sampledata);
	serialnum.Format(L"%d",serialnum_temp);
	samplenum.Format(L"%d",sampledata->number);
	//paitientname.Format(L"%s", taskdata->name);
	paitientname = A2W(taskdata->name);
	switch (taskdata->sex)
	{
	case 0:
		sex = "空";
		break;
	case 1:
		sex = "男";
		break;
	case 2:
		sex = "女";
		break;
	default:
		sex = "男";
		break;
	}
	//age.Format(L"%d",taskdata->age);
	age = A2W(taskdata->age);
	switch (sampledata->mode)//测试模式 0:全血+CBC5DIFF,1:全血+CBC,2:预稀释+CBC5DIFF,3:预稀释+CBC
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


	if (taskdata->taskmode == 1)
	{
		testmode = "清洗";
	}
	testtime.Format(L"%d", sampledata->time);
	barcode = A2W(taskdata->barcode);
	department = A2W(taskdata->department);

	GetDlgItem(IDC_SERIALNUM_EDIT)->SetWindowText(serialnum);
	GetDlgItem(IDC_SAMPLENUM_EDIT)->SetWindowText(samplenum);
	GetDlgItem(IDC_PAITIENTINFO_EDIT)->SetWindowText(paitientname);
	GetDlgItem(IDC_SEX_EDIT)->SetWindowText(sex);
	GetDlgItem(IDC_AGE_EDIT)->SetWindowText(age);
	GetDlgItem(IDC_TESTMODE_EDIT)->SetWindowText(testmode);
	GetDlgItem(IDC_TESTTIME_EDIT)->SetWindowText(testtime);
	GetDlgItem(IDC_BARCODE_EDIT)->SetWindowText(barcode);
	GetDlgItem(IDC_DEPARTMENT_EDIT)->SetWindowText(department);

	GetDlgItem(IDC_ANALYSIS_WBC)->SetWindowText(A2W(sampledata->wbcdata.wbc));
	GetDlgItem(IDC_ANALYSIS_LYMP)->SetWindowText(A2W(sampledata->wbcdata.lymp));
	GetDlgItem(IDC_ANALYSIS_NEUP)->SetWindowText(A2W(sampledata->wbcdata.neup));
	GetDlgItem(IDC_ANALYSIS_MONOP)->SetWindowText(A2W(sampledata->wbcdata.monop));
	GetDlgItem(IDC_ANALYSIS_EOSP)->SetWindowText(A2W(sampledata->wbcdata.eosp));
	GetDlgItem(IDC_ANALYSIS_BASOP)->SetWindowText(A2W(sampledata->wbcdata.basp));
	GetDlgItem(IDC_ANALYSIS_ALYP)->SetWindowText(A2W(sampledata->wbcdata.alyp));
	GetDlgItem(IDC_ANALYSIS_LICP)->SetWindowText(A2W(sampledata->wbcdata.licp));
	GetDlgItem(IDC_ANALYSIS_LYMA)->SetWindowText(A2W(sampledata->wbcdata.lym));
	GetDlgItem(IDC_ANALYSIS_NEUA)->SetWindowText(A2W(sampledata->wbcdata.neu));
	GetDlgItem(IDC_ANALYSIS_MONOA)->SetWindowText(A2W(sampledata->wbcdata.mono));
	GetDlgItem(IDC_ANALYSIS_EOSA)->SetWindowText(A2W(sampledata->wbcdata.eos));
	GetDlgItem(IDC_ANALYSIS_BASOA)->SetWindowText(A2W(sampledata->wbcdata.bas));
	GetDlgItem(IDC_ANALYSIS_ALYA)->SetWindowText(A2W(sampledata->wbcdata.aly));
	GetDlgItem(IDC_ANALYSIS_LICA)->SetWindowText(A2W(sampledata->wbcdata.lic));


	GetDlgItem(IDC_ANALYSIS_RBC)->SetWindowText(A2W(sampledata->rbcdata.rbc));
	GetDlgItem(IDC_ANALYSIS_HGB)->SetWindowText(A2W(sampledata->rbcdata.hgb));
	GetDlgItem(IDC_ANALYSIS_HCT)->SetWindowText(A2W(sampledata->rbcdata.hct));
	GetDlgItem(IDC_ANALYSIS_MCV)->SetWindowText(A2W(sampledata->rbcdata.mcv));
	GetDlgItem(IDC_ANALYSIS_MCH)->SetWindowText(A2W(sampledata->rbcdata.mch));
	GetDlgItem(IDC_ANALYSIS_MCHC)->SetWindowText(A2W(sampledata->rbcdata.mchc));
	GetDlgItem(IDC_ANALYSIS_RDW_CV)->SetWindowText(A2W(sampledata->rbcdata.rdwcv));
	GetDlgItem(IDC_ANALYSIS_RDW_SD)->SetWindowText(A2W(sampledata->rbcdata.rdwsd));

	GetDlgItem(IDC_ANALYSIS_PLT)->SetWindowText(A2W(sampledata->pltdata.plt));
	GetDlgItem(IDC_ANALYSIS_MPV)->SetWindowText(A2W(sampledata->pltdata.mpv));
	GetDlgItem(IDC_ANALYSIS_PDW)->SetWindowText(A2W(sampledata->pltdata.pdw));
	GetDlgItem(IDC_ANALYSIS_PCT)->SetWindowText(A2W(sampledata->pltdata.pct));
	GetDlgItem(IDC_ANALYSIS_PLCR)->SetWindowText(A2W(sampledata->pltdata.plcr));
}


