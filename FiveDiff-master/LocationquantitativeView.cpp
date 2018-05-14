// LocationquantitativeView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "LocationquantitativeView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CLocationquantitativeView 对话框

IMPLEMENT_DYNAMIC(CLocationquantitativeView, CDialogEx)

CLocationquantitativeView::CLocationquantitativeView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLocationquantitativeView::IDD, pParent)
{

}

CLocationquantitativeView::~CLocationquantitativeView()
{
}

void CLocationquantitativeView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLocationquantitativeView, CDialogEx)
	ON_BN_CLICKED(IDC_DEBUG_XYRATION, &CLocationquantitativeView::OnBnClickedDebugXyration)
	ON_BN_CLICKED(IDC_DEBUG_SAMPLERATION, &CLocationquantitativeView::OnBnClickedDebugSampleration)
	ON_BN_CLICKED(IDC_DEBUG_HGBLYSERATION, &CLocationquantitativeView::OnBnClickedDebugHgblyseration)
	ON_BN_CLICKED(IDC_DEBUG_RINSERATION, &CLocationquantitativeView::OnBnClickedDebugRinseration)
	ON_BN_CLICKED(IDC_DEBUG_FIXRATION, &CLocationquantitativeView::OnBnClickedDebugFixration)
	ON_BN_CLICKED(IDC_DEBUG_DILUENTRATION, &CLocationquantitativeView::OnBnClickedDebugDiluentration)
	ON_BN_CLICKED(IDC_DEBUG_WBCLYSERATION, &CLocationquantitativeView::OnBnClickedDebugWbclyseration)
	ON_BN_CLICKED(IDC_DEBUG_ESCAPE, &CLocationquantitativeView::OnBnClickedDebugEscape)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CLocationquantitativeView::OnAckspi)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLocationquantitativeView 消息处理程序


void CLocationquantitativeView::OnBnClickedDebugXyration()
{
		//ARM_GPIOCMD(EN_RED);
				  TRACE("XY  RATION---------#\n");
					key_status = FALSE;
					DSP_status = Busy;
					sdata_cmd[0] = SPI_CMD_XYRATION;	
					PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_XYRATION)->SetWindowText(L"正在执行XY定位！");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: 在此添加控件通知处理程序代码
}


void CLocationquantitativeView::SetWindowEnable(void)
{
	GetDlgItem(IDC_DEBUG_XYRATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_SAMPLERATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_HGBLYSERATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_RINSERATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_FIXRATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_DILUENTRATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_WBCLYSERATION)->EnableWindow(TRUE);
	GetDlgItem(IDC_DEBUG_ESCAPE)->EnableWindow(TRUE);
	
}


void CLocationquantitativeView::SetWindowDisable(void)
{
	GetDlgItem(IDC_DEBUG_XYRATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_SAMPLERATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_HGBLYSERATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_RINSERATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_FIXRATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_DILUENTRATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_WBCLYSERATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_DEBUG_ESCAPE)->EnableWindow(FALSE);
}


void CLocationquantitativeView::OnBnClickedDebugSampleration()
{
	        TRACE("SAMPLE  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_SAMPLERATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_SAMPLERATION)->SetWindowText(L"正在执行采样定量！");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: 在此添加控件通知处理程序代码
}


void CLocationquantitativeView::OnBnClickedDebugHgblyseration()
{
	   TRACE("HGB  LYSERATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] =  SPI_CMD_HGBLYSERATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_HGBLYSERATION)->SetWindowText(L"正在执行HGB定量！");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	
	// TODO: 在此添加控件通知处理程序代码
}


void CLocationquantitativeView::OnBnClickedDebugRinseration()
{
	 TRACE("RINSE  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_RINSERATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_RINSERATION)->SetWindowText(L"正在执行RINSE定量！");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	
	// TODO: 在此添加控件通知处理程序代码
}


void CLocationquantitativeView::OnBnClickedDebugFixration()
{
	        TRACE("FIX  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_FIXRATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_FIXRATION)->SetWindowText(L"正在执行嗜酸定量！");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: 在此添加控件通知处理程序代码
}


void CLocationquantitativeView::OnBnClickedDebugDiluentration()
{
	
	        TRACE("DILUETN  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_DILUETNRATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_DILUENTRATION)->SetWindowText(L"正在执行HB-5D定量！");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: 在此添加控件通知处理程序代码
}


void CLocationquantitativeView::OnBnClickedDebugWbclyseration()
{
	        TRACE("DILUETN  RATION---------#\n");
		    key_status = FALSE;
			DSP_status = Busy;
			sdata_cmd[0] = SPI_CMD_WBCLYSERATION;	
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	   else{
		    GetDlgItem(IDC_DEBUG_WBCLYSERATION)->SetWindowText(L"正在执行BAS定量！");
			SetWindowDisable();
			SetTimer( POLLTIME, SPI_POLL_TIME1000,0);
	   }
	// TODO: 在此添加控件通知处理程序代码
}


void CLocationquantitativeView::OnBnClickedDebugEscape()
{
	
	CDialogEx::OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}


void CLocationquantitativeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
			{
				case POLLTIME:
					{
					TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
					sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;	
				 	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
					PC_RECEIVE_FRAME(rdata_state,SPI_TYPE_STATE);	
					SendMessage(WM_ACKSPI,rdata_state[0],0);
					}
					break;
				default:
					break;
			}
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CLocationquantitativeView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
			{
				//定位与定量完成
				case SPI_STATE_INFO_END:
					//ARM_GPIOCMD(EN_GREEN);
					KillTimer( POLLTIME); 
					DSP_status = Free ;
					key_status = TRUE;
					SetWindowEnable();
					break;
				default:
					break;
			}
	
	
	return 0;
}


void CLocationquantitativeView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	/*@TG
#3073*/
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为白色背景
	dc.Rectangle(30, 10, rect.right - 30, rect.bottom - 30);
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()
}
