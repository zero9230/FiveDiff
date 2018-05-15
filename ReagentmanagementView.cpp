// ReagentmanagementView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ReagentmanagementView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CReagentmanagementView 对话框


static uchar 		DayConCleanFlag = 0;	//浓缩清洗标志，1-浓缩清洗(去蛋白液清洗)
static uchar 		DayConCleanStep = 0;	//0:初始状态,1:第一步执行完,2:第二步执行完

IMPLEMENT_DYNAMIC(CReagentmanagementView, CDialogEx)

CReagentmanagementView::CReagentmanagementView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReagentmanagementView::IDD, pParent)
{
	VERIFY(m_Font.CreateFont(
		20,                        // nHeight
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

CReagentmanagementView::~CReagentmanagementView()
{
}

void CReagentmanagementView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReagentmanagementView, CDialogEx)
	
	ON_BN_CLICKED(IDC_MAINTENANCE_WEEKLY_OK1, &CReagentmanagementView::OnBnClickedMaintenanceWeeklyOk1)
	ON_BN_CLICKED(IDC_MAINTENANCE_WEEKLY_OK2, &CReagentmanagementView::OnBnClickedMaintenanceWeeklyOk2)
	ON_BN_CLICKED(IDC_MAINTENANCE_YEARLY, &CReagentmanagementView::OnBnClickedMaintenanceYearly)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CReagentmanagementView::OnAckspi)
END_MESSAGE_MAP()


// CReagentmanagementView 消息处理程序




void CReagentmanagementView::OnBnClickedMaintenanceWeeklyOk1()
{
	if(0 == DayConCleanStep)
		{
	//ARM_GPIOCMD(EN_RED);
	TRACE("DAILY MAINTENANCE---------!#\n");
	key_status = FALSE;		
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_CONCENTRATE_CLEAN1;	
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	else
	       {
			   SetTimer( POLLTIME,SPI_POLL_TIME1000,0);
			   GetDlgItem(IDC_STATIC_WEEKLY)->SetWindowText(L"正在执行第一步！");
			  DayConCleanFlag = 1;
	        }
			//ConcentratedCleaning_1(hDlg,"DAILY MAINTENANCE---------!#\n");
		}
	else
		MessageBox(L"第一步已完成!",L"提示",0);
	// TODO: 在此添加控件通知处理程序代码
}


void CReagentmanagementView::OnBnClickedMaintenanceWeeklyOk2()
{
	if(1 == DayConCleanStep)
		{
	//ARM_GPIOCMD(EN_RED);
	TRACE("DAILY MAINTENANCE---------!#\n");
	key_status = FALSE;		
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_CONCENTRATE_CLEAN2;	
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	else
	       {
			   SetTimer( POLLTIME,SPI_POLL_TIME1000,0);
			   GetDlgItem(IDC_STATIC_WEEKLY)->SetWindowText(L"正在执行第二步！");
			  // DayConCleanStep=0;
			   DayConCleanFlag = 1;
	        }
			//ConcentratedCleaning_1(hDlg,"DAILY MAINTENANCE---------!#\n");
		}
	else
		MessageBox(L"请先执行第一步!",L"提示",0);
	// TODO: 在此添加控件通知处理程序代码
}


void CReagentmanagementView::OnBnClickedMaintenanceYearly()
{

	//ARM_GPIOCMD(EN_RED);
	TRACE("YEARLY MAINTENANCE----------!#\n");
	key_status = FALSE;		
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_MONTHLYMAINTAIN;	
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	else
	       {
			   SetTimer( POLLTIME,SPI_POLL_TIME3000,0);
			   GetDlgItem(IDC_STATIC_WEEKLY)->SetWindowText(L"正在执行年保养！");
			  // DayConCleanStep=0;
			  
	        }
			//ConcentratedCleaning_1(hDlg,"DAILY MAINTENANCE---------!#\n");
		
	// TODO: 在此添加控件通知处理程序代码
}


HBRUSH CReagentmanagementView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//文字背景色
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//控件背景色   
		return b;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CReagentmanagementView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
		CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为白色背景
	dc.Rectangle(30, 20, rect.right/2-10 , rect.bottom - 70);
	dc.Rectangle(rect.right/2+10, 20, rect.right-30 , rect.bottom - 70);
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CReagentmanagementView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case POLLTIME:
		TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
					sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;	
				 	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
					PC_RECEIVE_FRAME(rdata_state,SPI_TYPE_STATE);	
					SendMessage(WM_ACKSPI,rdata_state[0],0);
					break;
				default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CReagentmanagementView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
			{
				//日常维护完成
				case SPI_STATE_INFO_END:
					if(1 == DayConCleanFlag)//若是浓缩清洗
					{
						//ARM_GPIOCMD(EN_GREEN);
						KillTimer( POLLTIME);
						DSP_status = Free;
						DayConCleanStep++;
						if(1 == DayConCleanStep)
						{
							//if(systemcfg.language == CHINESE)
							MessageBox(L"请在每个杯中加3ml 去蛋白液,并执行第二步",L"提示",0);
						//	else if(systemcfg.language == ENGLISH)
							//	SetDlgItemText(hDlg, IDC_MAINTENANCE_WEEKLY_MESS,"Add 3ml protein solution to each cup,and Excute the action of Concentrated Cleaning Step 2");
						}
						else if(2 == DayConCleanStep)
						{
							//if(systemcfg.language == CHINESE)
								MessageBox(L"浓缩清洗完成",L"提示",0);
								//SetDlgItemText(hDlg, IDC_MAINTENANCE_WEEKLY_MESS,"浓缩清洗完成");
							//else if(systemcfg.language == ENGLISH)
							//	SetDlgItemText(hDlg, IDC_MAINTENANCE_WEEKLY_MESS,"Concentrated Cleaning Done");
							DayConCleanStep = 0;
						}
						DayConCleanFlag = 0;
						key_status = TRUE;
					}
					else
					{
						//ARM_GPIOCMD(EN_RED);
						KillTimer( POLLTIME);
						DSP_status = Free ;
						key_status = TRUE;
					}
					break;
				default:
					break;
			}
	return 0;
}
