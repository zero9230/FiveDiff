// MicroperfusionView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "MicroperfusionView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CMicroperfusionView 对话框

IMPLEMENT_DYNAMIC(CMicroperfusionView, CDialogEx)

CMicroperfusionView::CMicroperfusionView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMicroperfusionView::IDD, pParent)
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

CMicroperfusionView::~CMicroperfusionView()
{
}

void CMicroperfusionView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMicroperfusionView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDM_MAIN_HYDR_MINIPRIME, &CMicroperfusionView::OnBnClickedMainHydrMiniprime)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CMicroperfusionView::OnAckspi)
END_MESSAGE_MAP()


// CMicroperfusionView 消息处理程序


HBRUSH CMicroperfusionView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	return hbr;
}


void CMicroperfusionView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为白色背景
	dc.Rectangle(40, 20, rect.right - 40, rect.bottom - 30);
}


void CMicroperfusionView::OnBnClickedMainHydrMiniprime()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("IDM_MAIN_HYDR_MINIPRIME---------#\n");
	key_status = FALSE;
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_MINIPRIME;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
		MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	else{
	GetDlgItem(IDC_MICROPERFUSION)->SetWindowText(L"正在执行微灌注！");
		SetTimer(POLLTIME, SPI_POLL_TIME3000, 0);
	}
}


void CMicroperfusionView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case POLLTIME:
		//DEBUG_PRINT1("MSG_TIMER:POLLTIME is due -------------#\n");
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(WM_ACKSPI, rdata_state[0], 0);
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CMicroperfusionView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	//处理SPI消息

	switch (wParam)
	{
	case SPI_STATE_INFO_END:
		TRACE(_T("SPI_STATE_INFO_END"));
		KillTimer(POLLTIME);
		DSP_status = Free;
		statusShowMess = 0;
		//InvalidateRect(hDlg, &STATUS, TRUE);
		key_status = TRUE;
		//Standby_EN = TRUE;
		GetDlgItem(IDC_MICROPERFUSION)->SetWindowText(L"执行微灌注完成！");
		break;
	}
	//如果完成：
	//
	
	return 0;
}
