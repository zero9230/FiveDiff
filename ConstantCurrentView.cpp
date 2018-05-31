// ConstantCurrentView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ConstantCurrentView.h"
#include "afxdialogex.h"


// CConstantCurrentView 对话框
	static unsigned char rbc_on_off = 0;		//0表示关闭，1表示打开
	static unsigned char baso_on_off = 0;
	static unsigned char lmne_on_off = 0;
	
IMPLEMENT_DYNAMIC(CConstantCurrentView, CDialogEx)

CConstantCurrentView::CConstantCurrentView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConstantCurrentView::IDD, pParent)
{

}

CConstantCurrentView::~CConstantCurrentView()
{
}

void CConstantCurrentView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConstantCurrentView, CDialogEx)
	ON_BN_CLICKED(IDC_CONSTANTCURRENT_RBC, &CConstantCurrentView::OnBnClickedConstantcurrentRbc)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CONSTANTCURRENT_BASO, &CConstantCurrentView::OnBnClickedConstantcurrentBaso)
	ON_BN_CLICKED(IDC_CONSTANTCURRENT_LMNE, &CConstantCurrentView::OnBnClickedConstantcurrentLmne)
	ON_BN_CLICKED(IDCANCEL, &CConstantCurrentView::OnBnClickedCancel)
END_MESSAGE_MAP()


// CConstantCurrentView 消息处理程序


void CConstantCurrentView::OnBnClickedConstantcurrentRbc()
{
	if(0 == rbc_on_off)
					{
						//RBC 恒流源开
						TRACE("Engineer Maintain:RBC Constant-current Source ON--------------!#\n");
						sdata_cmd[0] = SPI_CMD_RBCCURON;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
						else
						{
							rbc_on_off = !rbc_on_off;
						  GetDlgItem(IDC_CONSTANTCURRENT_RBC)->SetWindowText(L"RBC恒流源  关");
						}
					//	if(systemcfg.language == CHINESE)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_RBC,	"RBC  恒流源    关");
					//	}
					//	else if(systemcfg.language == ENGLISH)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_RBC,"RBC   Constant Current    Close");
					//	}	
					}
					else if(1 == rbc_on_off)
					{
						//RBC 恒流源关
						TRACE("Engineer Maintain:RBC Constant-current Source OFF---------------!#\n");
						sdata_cmd[0] = SPI_CMD_RBCCUROFF;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
						else
						{
						rbc_on_off = !rbc_on_off;
						 GetDlgItem(IDC_CONSTANTCURRENT_RBC)->SetWindowText(L"RBC恒流源  开");
						}
						//if(systemcfg.language == CHINESE)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_RBC,	"RBC  恒流源   开");
					//	}
					//	else if(systemcfg.language == ENGLISH)
					//	{
				//			SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_RBC,"RBC   Constant Current    Open");
					//	}	
					}
		
	// TODO: 在此添加控件通知处理程序代码
}


HBRUSH CConstantCurrentView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CConstantCurrentView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
			CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为白色背景
	dc.Rectangle(30, 20, rect.right-30 , rect.bottom - 30);
	//dc.Rectangle(rect.right/2+10, 20, rect.right-30 , rect.bottom - 70);
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CConstantCurrentView::OnBnClickedConstantcurrentBaso()
{
	if(0 == baso_on_off)
					{
						//BASO 恒流源开
						TRACE("Engineer Maintain:BASO Constant-current Source ON--------------!#\n");
						sdata_cmd[0] = SPI_CMD_BASOCURON;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
						else
						{
						baso_on_off = !baso_on_off;
						 GetDlgItem(IDC_CONSTANTCURRENT_BASO)->SetWindowText(L"BASO恒流源  关");
						}
						//if(systemcfg.language == CHINESE)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_BASO,"BASO恒流源   关");
					//	}
					//	else if(systemcfg.language == ENGLISH)
					//	{
					//		SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_BASO,"BASO Constant Current    Close");
					//	}
					}
					else if(1 == baso_on_off)
					{
						//BASO 恒流源关
						TRACE("Engineer Maintain:BASO Constant-current Source OFF--------------!#\n");
						sdata_cmd[0] = SPI_CMD_BASOCUROFF;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
							if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
							else
							{
								baso_on_off = !baso_on_off;
						 GetDlgItem(IDC_CONSTANTCURRENT_BASO)->SetWindowText(L"BASO恒流源  开");
							}
						//if(systemcfg.language == CHINESE)
						//{
							//SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_BASO,"BASO恒流源  开");
						//}
						//else if(systemcfg.language == ENGLISH)
						//{
							//SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_BASO,"BASO Constant Current    Open");
						//}
					}
					
					
	// TODO: 在此添加控件通知处理程序代码
}


void CConstantCurrentView::OnBnClickedConstantcurrentLmne()
{
	if(0 == lmne_on_off)
					{
						//LMNE 恒流源开
						TRACE("Engineer Maintain:LMNE Constant-current Source ON--------------!#\n");
						sdata_cmd[0] = SPI_CMD_LMNECURON;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
						else
						{
							lmne_on_off = !lmne_on_off;
							 GetDlgItem(IDC_CONSTANTCURRENT_LMNE)->SetWindowText(L"LMNE恒流源  关");
						}
						/*if(systemcfg.language == CHINESE)
						{
							SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_LMNE,"LMNE恒流源  关");
						}
						else if(systemcfg.language == ENGLISH)
						{
							SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_LMNE,"LMNE Constant Current    Close");
						}*/
					}
					else if(1 == lmne_on_off)
					{
						//LMNE 恒流源关
						TRACE("Engineer Maintain:LMNE Constant-current Source OFF---------------!#\n");
						sdata_cmd[0] = SPI_CMD_LMNECUROFF;
						PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
						if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == -1)
			                   MessageBox(L"命令发送不成功！", L"ERROR", MB_OKCANCEL);
						else
						{
							lmne_on_off = !lmne_on_off;
							 GetDlgItem(IDC_CONSTANTCURRENT_LMNE)->SetWindowText(L"LMNE恒流源  开");
						}
						/*if(systemcfg.language == CHINESE)
						{
							SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_LMNE,"LMNE恒流源  开");
						}
						else if(systemcfg.language == ENGLISH)
						{
							SetDlgItemText(hDlg,IDC_CONSTANTCURRENT_LMNE,"LMNE Constant Current    Open");
						}*/
					}
					
					
	// TODO: 在此添加控件通知处理程序代码
}


void CConstantCurrentView::OnBnClickedCancel()
{
	
	if(rbc_on_off != 0 || baso_on_off != 0 || lmne_on_off != 0)
		{
			 MessageBox(L"请关闭恒流源！", L"警告", MB_OKCANCEL);
						/*if(systemcfg.language == CHINESE)
							MessageBox(HWND_DESKTOP,"请关闭恒流源!","警告!",MB_OK | MB_ICONINFORMATION);	
						else if(systemcfg.language == ENGLISH)
							CreateWarningBoxNonCHDlg(HWND_DESKTOP, "Please Close The Constant Current!", "Warning!");*/
		}
	// TODO: 在此添加控件通知处理程序代码
	else
	CDialogEx::OnCancel();
}
