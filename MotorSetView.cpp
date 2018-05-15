// MotorSetView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "MotorSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
// CMotorSetView 对话框

IMPLEMENT_DYNAMIC(CMotorSetView, CDialogEx)

CMotorSetView::CMotorSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotorSetView::IDD, pParent)
{

}

CMotorSetView::~CMotorSetView()
{
}

void CMotorSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMotorSetView, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_XM1, &CMotorSetView::OnBnClickedXm1)
	ON_BN_CLICKED(IDC_XM2, &CMotorSetView::OnBnClickedXm2)
	ON_BN_CLICKED(IDC_XM3, &CMotorSetView::OnBnClickedXm3)
	ON_BN_CLICKED(IDC_XM4, &CMotorSetView::OnBnClickedXm4)
	ON_BN_CLICKED(IDC_XM5, &CMotorSetView::OnBnClickedXm5)
	ON_BN_CLICKED(IDC_XM6, &CMotorSetView::OnBnClickedXm6)
	ON_BN_CLICKED(IDC_DIM, &CMotorSetView::OnBnClickedDim)
	ON_BN_CLICKED(IDC_YM1, &CMotorSetView::OnBnClickedYm1)
	ON_BN_CLICKED(IDC_YM2, &CMotorSetView::OnBnClickedYm2)
	ON_BN_CLICKED(IDC_YM3, &CMotorSetView::OnBnClickedYm3)
	ON_BN_CLICKED(IDC_YM4, &CMotorSetView::OnBnClickedYm4)
	ON_BN_CLICKED(IDC_YM5, &CMotorSetView::OnBnClickedYm5)
	ON_BN_CLICKED(IDC_YM6, &CMotorSetView::OnBnClickedYm6)
	ON_BN_CLICKED(IDC_YM7, &CMotorSetView::OnBnClickedYm7)
	ON_BN_CLICKED(IDC_YM8, &CMotorSetView::OnBnClickedYm8)
	ON_BN_CLICKED(IDC_YM9, &CMotorSetView::OnBnClickedYm9)
	ON_BN_CLICKED(IDC_YM10, &CMotorSetView::OnBnClickedYm10)
	ON_WM_TIMER()
	ON_MESSAGE(MSG_ACKSPI, &CMotorSetView::OnAckspi)
	ON_BN_CLICKED(IDC_RESET_XYMOTOR, &CMotorSetView::OnResetXYmotor)
	ON_BN_CLICKED(IDC_SAVE, &CMotorSetView::OnSave)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMotorSetView 消息处理程序

BOOL CMotorSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString temp[17];
	ReadSystemcfgFile();
	for (int i = 0; i < 17; i++)
	{
		temp[i].Format(L"%d", systemcfg.mstp[i]);
	}
	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_XM_START_RINSE)->SetWindowText(temp[XM_START_RINSE]);
	GetDlgItem(IDC_XM_START_HGB)->SetWindowText(temp[XM_START_HGB]);
	GetDlgItem(IDC_XM_START_LMNE)->SetWindowText(temp[XM_START_LMNE]);
	GetDlgItem(IDC_XM_START_RBC)->SetWindowText(temp[XM_START_RBC]);
	GetDlgItem(IDC_XM_START_WBCBASO)->SetWindowText(temp[XM_START_WBCBASO]);
	GetDlgItem(IDC_XM_CUP_RADIUS)->SetWindowText(temp[XM_CUP_RADIUS]);
	//DIM
	GetDlgItem(IDC_DIM_DILUENT)->SetWindowText(temp[DIM_DILUENT]);
	// YM 
	GetDlgItem(IDC_YM_REF)->SetWindowText(temp[YM_REF]);
	GetDlgItem(IDC_YM_RINSE_HIGH)->SetWindowText(temp[YM_HIGH_RINSE]);
	GetDlgItem(IDC_YM_RINSE_LOW)->SetWindowText(temp[YM_LOW_RINSE]);
	GetDlgItem(IDC_YM_HGB_MID)->SetWindowText(temp[YM_MID_HGB]);
	GetDlgItem(IDC_YM_HGB_LOW)->SetWindowText(temp[YM_LOW_HGB]);
	GetDlgItem(IDC_YM_HGB_HIGH)->SetWindowText(temp[YM_HIGH_HGB]);
	GetDlgItem(IDC_YM_LMNE)->SetWindowText(temp[YM_WBCLMNE]); 
	GetDlgItem(IDC_YM_RBC)->SetWindowText(temp[YM_RBCPLT]);
	GetDlgItem(IDC_YM_BASO)->SetWindowText(temp[YM_WBCBASO]);
	GetDlgItem(IDC_YM_SAMPLE)->SetWindowText(temp[YM_STARTSAMPLE]);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CMotorSetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();

	CDialogEx::OnPaint();
}


void CMotorSetView::OnBnClickedXm1()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	//XM
	systemcfg.mstp[XM_START_RINSE] = GetDlgItemInt(IDC_XM_START_RINSE);	

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_XMSET_START_RINSE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000,0);
}


void CMotorSetView::OnBnClickedXm2()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;
	//XM
	systemcfg.mstp[XM_START_HGB] = GetDlgItemInt(IDC_XM_START_HGB);
	((CMainFrame*)AfxGetMainWnd())->SendSysPara();

	sdata_cmd[0] = SPI_CMD_XMSET_START_HGB;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedXm3()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;
	//XM

	systemcfg.mstp[XM_START_LMNE] = GetDlgItemInt(IDC_XM_START_LMNE);


	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_XMSET_START_LMNE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedXm4()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;
	//XM
	systemcfg.mstp[XM_START_RBC] = GetDlgItemInt(IDC_XM_START_RBC);
	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_XMSET_START_RBC;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedXm5()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[XM_START_WBCBASO] = GetDlgItemInt(IDC_XM_START_WBCBASO);
	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_XMSET_START_WBCBASO;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedXm6()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[XM_CUP_RADIUS] = GetDlgItemInt(IDC_XM_CUP_RADIUS);

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_XMSET_CUP_RADIUS;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedDim()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CMotorSetView::OnBnClickedYm1()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[YM_REF] = GetDlgItemInt(IDC_YM_REF);
	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_REF;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedYm2()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;
	
	systemcfg.mstp[YM_HIGH_RINSE] = GetDlgItemInt(IDC_YM_RINSE_HIGH);
	

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_HIGH_RINSE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedYm3()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[YM_LOW_RINSE] = GetDlgItemInt(IDC_YM_RINSE_LOW);

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_LOW_RINSE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedYm4()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[YM_MID_HGB] = GetDlgItemInt(IDC_YM_HGB_MID);

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_MID_HGB;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedYm5()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[YM_LOW_HGB] = GetDlgItemInt(IDC_YM_HGB_LOW);


	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_LOW_HGB;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedYm6()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[YM_HIGH_HGB] = GetDlgItemInt(IDC_YM_HGB_HIGH);

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_HIGH_HGB;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedYm7()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[YM_WBCLMNE] = GetDlgItemInt(IDC_YM_LMNE);

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_WBCLMNE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedYm8()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[YM_RBCPLT] = GetDlgItemInt(IDC_YM_RBC);


	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_RBCPLT;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedYm9()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[YM_WBCBASO] = GetDlgItemInt(IDC_YM_BASO);

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_WBCBASO;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}


void CMotorSetView::OnBnClickedYm10()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;

	systemcfg.mstp[YM_STARTSAMPLE] = GetDlgItemInt(IDC_YM_SAMPLE);

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	sdata_cmd[0] = SPI_CMD_YMSET_STARTSAMPLE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000, 0);
}

void CMotorSetView::OnResetXYmotor()
{
	// TODO:  在此添加控件通知处理程序代码
	key_status = FALSE;
	DSP_status = Busy;
	sdata_cmd[0] = SPI_CMD_XYMSET_RESET;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
	SetTimer(POLLTIME, 1000,0);
}


void CMotorSetView::OnSave()
{
	// TODO:  在此添加控件通知处理程序代码
	//XM
	systemcfg.mstp[XM_START_RINSE] = GetDlgItemInt(IDC_XM_START_RINSE);
	systemcfg.mstp[XM_START_HGB] = GetDlgItemInt(IDC_XM_START_HGB);
	systemcfg.mstp[XM_START_LMNE] = GetDlgItemInt(IDC_XM_START_LMNE);
	systemcfg.mstp[XM_START_RBC] = GetDlgItemInt(IDC_XM_START_RBC);
	systemcfg.mstp[XM_START_WBCBASO] = GetDlgItemInt(IDC_XM_START_WBCBASO);
	systemcfg.mstp[XM_CUP_RADIUS] = GetDlgItemInt(IDC_XM_CUP_RADIUS);
	//DIM
	systemcfg.mstp[DIM_DILUENT] = GetDlgItemInt(IDC_DIM_DILUENT);
	// YM 
	systemcfg.mstp[YM_REF] = GetDlgItemInt(IDC_YM_REF);
	systemcfg.mstp[YM_HIGH_RINSE] = GetDlgItemInt(IDC_YM_RINSE_HIGH);
	systemcfg.mstp[YM_LOW_RINSE] = GetDlgItemInt(IDC_YM_RINSE_LOW);
	systemcfg.mstp[YM_MID_HGB] = GetDlgItemInt(IDC_YM_HGB_MID);
	systemcfg.mstp[YM_LOW_HGB] = GetDlgItemInt(IDC_YM_HGB_LOW);
	systemcfg.mstp[YM_HIGH_HGB] = GetDlgItemInt(IDC_YM_HGB_HIGH);
	systemcfg.mstp[YM_WBCLMNE] = GetDlgItemInt(IDC_YM_LMNE);
	systemcfg.mstp[YM_RBCPLT] = GetDlgItemInt(IDC_YM_RBC);
	systemcfg.mstp[YM_WBCBASO] = GetDlgItemInt(IDC_YM_BASO);
	systemcfg.mstp[YM_STARTSAMPLE] = GetDlgItemInt(IDC_YM_SAMPLE);

	((CMainFrame*)AfxGetMainWnd())->SendSysPara();
	WriteSystemcfgFile();
}


void CMotorSetView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
		TRACE(L"MSG_TIMER:POLLTIME is due -------------#\n");
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(MSG_ACKSPI, rdata_state[0], 0);
	case POLL_TIMER:
	{
		break;
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CMotorSetView::OnAckspi(WPARAM wParam, LPARAM lParam)
{

	switch (wParam)
	{
		//电机动作完成
	case SPI_STATE_INFO_END:
		KillTimer(POLLTIME);
		DSP_status = Free;
		key_status = TRUE;
		break;
	default:
		break;
	}
	return 0;
}


HBRUSH CMotorSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
