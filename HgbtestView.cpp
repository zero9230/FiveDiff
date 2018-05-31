// HgbtestView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "HgbtestView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CHgbtestView 对话框

IMPLEMENT_DYNAMIC(CHgbtestView, CDialogEx)

CHgbtestView::CHgbtestView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHgbtestView::IDD, pParent)
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

CHgbtestView::~CHgbtestView()
{
}

void CHgbtestView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHgbtestView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_HGBTEST_OK, &CHgbtestView::OnBnClickedHgbtestOk)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ACKSPI, &CHgbtestView::OnAckspi)
	ON_BN_CLICKED(IDC_HGBTEST_BACK, &CHgbtestView::OnBnClickedHgbtestBack)
END_MESSAGE_MAP()


// CHgbtestView 消息处理程序


HBRUSH CHgbtestView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//文字背景色
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//控件背景色   
		return b;
	}
//#3018
//
//#3019
//	return hbr;
//
//#3018
//
//#3019
//	return hbr;
//	// TODO:  在此更改 DC 的任何特性
//
//#3019
//	//return hbr;
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CHgbtestView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为白色背景
	dc.Rectangle(40, 20, rect.right - 40, rect.bottom - 30);
	/*@TG
#3073*/
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CHgbtestView::OnBnClickedHgbtestOk()
{
	//           ARM_GPIOCMD(EN_RED);
					TRACE("HGB Test----------#\n");
					key_status = FALSE ;
					DSP_status = Busy;
					sdata_cmd[0] = SPI_CMD_HGB_MAINTAIN;
				 	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
					if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
		                MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
	              else{
	                     GetDlgItem(IDC_MICROPERFUSION)->SetWindowText(L"正在执行HGB测试！");//**##此处有异常
		                 SetTimer(POLLTIME, SPI_POLL_TIME1000,0);
	                   }
					
	
	// TODO: 在此添加控件通知处理程序代码
}


void CHgbtestView::OnTimer(UINT_PTR nIDEvent)
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


afx_msg LRESULT CHgbtestView::OnAckspi(WPARAM wParam, LPARAM lParam)
{


	switch(wParam)
			{
				//HGB检测完成
				case SPI_STATE_INFO_END:
				{
					unsigned char buff[8] = {0}; 
					int HGB_Background_int = 0;
					int HGB_Blank_int = 0;
					float HGB_Background = 0.0;
					float HGB_Blank = 0.0;
					unsigned char HGB_Background_str[7] = "*.***V";
					unsigned char HGB_Blank_str[7] = "*.***V";
					
					//ARM_GPIOCMD(EN_GREEN);
					KillTimer( POLLTIME);
					sdata_cmd[0] = SPI_CMD_REQHGBTEST;					
					PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
					PC_RECEIVE_FRAME(buff, SPI_TYPE_HGBTESTRES);	
					DSP_status = Free;
					
					HGB_Background_int = buff[0]*1000 + buff[1]*100 + buff[2]*10 + buff[3];
					HGB_Blank_int =  buff[4]*1000 + buff[5]*100 + buff[6]*10 + buff[7];
					if(HGB_Background_int >= 0 && HGB_Background_int <= 5000 && HGB_Blank_int >= 0 && HGB_Blank_int <= 5000)	//正常情况
					{
						HGB_Background = (float)HGB_Background_int/1000;
						HGB_Blank = (float)HGB_Blank_int/1000;
						//sprintf(HGB_Background_str,"%.3fV",HGB_Background);
						//sprintf(HGB_Blank_str,"%.3fV",HGB_Blank);
					}
					else
					{
						printf("HGB TEST is not Normal----------#\n");
					}
                        		//SetDlgItemText(IDC_HGBTEST_BACKGD,HGB_Background_str);	
					GetDlgItem(IDC_HGBTEST_BACKGD)->SetWindowText((LPCTSTR)HGB_Background_str);
					//SetDlgItemText(IDC_HGBTEST_BLANK,HGB_Blank_str);
					GetDlgItem(IDC_HGBTEST_BLANK)->SetWindowText((LPCTSTR)HGB_Blank_str);
					key_status = TRUE;
					break;
				}
				default:
					break;
			}
			
	return 0;
}


void CHgbtestView::OnBnClickedHgbtestBack()
{
	
	CDialogEx::OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}
