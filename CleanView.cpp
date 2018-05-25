// CleanView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "CleanView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CCleanView 对话框

IMPLEMENT_DYNAMIC(CCleanView, CDialogEx)

CCleanView::CCleanView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCleanView::IDD, pParent)
{
	/*GetDlgItem(IDC_CLEAN_RINSEBASO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CLEAN_EXTERNNEEDLE)->EnableWindow(FALSE);*/

}

CCleanView::~CCleanView()
{

}

void CCleanView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCleanView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CLEAN_CYTO, &CCleanView::OnCleanCyto)
	ON_BN_CLICKED(IDC_CLEAN_CHAMBERS, &CCleanView::OnCleanChambers)
	ON_BN_CLICKED(IDC_CLEAN_DILUENTINTINE, &CCleanView::OnCleanDiluentintine)
	ON_BN_CLICKED(IDC_CLEAN_DILUENTEXTINE, &CCleanView::OnCleanDiluentextine)
	ON_BN_CLICKED(IDC_CLEAN_GEM, &CCleanView::OnCleanGem)
	ON_BN_CLICKED(IDC_CLEAN_SHEATFLOWPIPE, &CCleanView::OnCleanSheatflowpipe)
	ON_BN_CLICKED(IDC_CLEAN_RINSEBASO, &CCleanView::OnCleanRinsebaso)
	ON_BN_CLICKED(IDC_CLEAN_RINSEINTINE, &CCleanView::OnCleanRinseintine)
	ON_BN_CLICKED(IDC_CLEAN_RINSEEXTINE, &CCleanView::OnCleanRinseextine)
	ON_BN_CLICKED(IDC_CLEAN_EXTERNNEEDLE, &CCleanView::OnCleanExternneedle)
	ON_MESSAGE(WM_ACKSPI, &CCleanView::OnAckspi)
END_MESSAGE_MAP()


// CCleanView 消息处理程序
unsigned char CCleanView::ExterCleanFlag = 0;
unsigned char CCleanView::ExterCleanStep = 0;

BOOL CCleanView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_CLEAN_RINSEBASO)->EnableWindow(FALSE);
	GetDlgItem(IDC_CLEAN_EXTERNNEEDLE)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CCleanView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为白色背景
}


void CCleanView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case POLLTIME:
		TRACE("MSG_TIMER:POLLTIME is due -------------#\n");
		sdata_cmd[0] = SPI_CMD_REQDSP_STATUS;
		PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		PC_RECEIVE_FRAME(rdata_state, SPI_TYPE_STATE);
		SendMessage(WM_ACKSPI, rdata_state[0], 0);
		return;
	default:
		return;

	}
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CCleanView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CCleanView::CleanChannel(char* Mess, uchar CMD)
{

	TRACE(Mess);
	key_status = FALSE;
	DSP_status = Busy;
	sdata_cmd[0] = CMD;
	if (PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD) == 0)
	{
		GetDlgItem(IDC_CLEAN_CYTO)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLEAN_CHAMBERS)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLEAN_DILUENTINTINE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLEAN_DILUENTEXTINE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLEAN_GEM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLEAN_SHEATFLOWPIPE)->EnableWindow(FALSE);
		//GetDlgItem(IDC_CLEAN_RINSEBASO)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLEAN_RINSEINTINE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLEAN_RINSEEXTINE)->EnableWindow(FALSE);
		//GetDlgItem(IDC_CLEAN_EXTERNNEEDLE)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
		SetTimer(POLLTIME, 3000, 0);

	}

}

void CCleanView::OnCleanCyto()//鞘流池
{
	// TODO:  在此添加控件通知处理程序代码
	((CMainFrame*)AfxGetMainWnd())->StartProgress(30);
	CleanChannel("Clean SHEATHFLOWPOOL---------#\n", SPI_CMD_CLEAN_SHEATHFLOWPOOL);
	
}


void CCleanView::OnCleanChambers()//鞘流排堵
{
	// TODO:  在此添加控件通知处理程序代码
	CleanChannel("BACKFLUSH_LMNE---------#\n", SPI_CMD_BACKFLUSH_LMNE);
}


void CCleanView::OnCleanDiluentintine()//针内壁(稀释液)
{
	// TODO:  在此添加控件通知处理程序代码
	CleanChannel("Clean DILUENTINTINE---------#\n", SPI_CMD_CLEAN_DILUENTINTINE);
}



void CCleanView::OnCleanDiluentextine()//针外壁（稀释液）
{
	// TODO:  在此添加控件通知处理程序代码
	CleanChannel("Clean DILUENTEXTINE---------#\n", SPI_CMD_CLEAN_DILUENTEXTINE);
}


void CCleanView::OnCleanGem()//清洗内鞘
{
	// TODO:  在此添加控件通知处理程序代码
	CleanChannel("Clean GEM---------#\n", SPI_CMD_CLEAN_GEM);
}


void CCleanView::OnCleanSheatflowpipe()//鞘流管
{
	// TODO:  在此添加控件通知处理程序代码
	CleanChannel("Clean SHEATFLOWPIPE---------#\n", SPI_CMD_CLEAN_SHEATFLOWPIPE);
}


void CCleanView::OnCleanRinsebaso()//BASO池（清洗剂）
{
	// TODO:  在此添加控件通知处理程序代码
	CleanChannel("Clean RINSEBASO---------#\n", SPI_CMD_CLEAN_RINSEBASO);
}


void CCleanView::OnCleanRinseintine()//针内壁（清洗剂）
{
	// TODO:  在此添加控件通知处理程序代码
	CleanChannel("Clean RINSEINTINE---------#\n", SPI_CMD_CLEAN_RINSEINTINE);
}


void CCleanView::OnCleanRinseextine()//针外壁（清洗剂）
{
	// TODO:  在此添加控件通知处理程序代码
	CleanChannel("Clean DILUENTEXTINE---------#\n", SPI_CMD_CLEAN_DILUENTEXTINE);
}



void CCleanView::OnCleanExternneedle()//外部针
{
	// TODO:  在此添加控件通知处理程序代码
	ExterCleanFlag = 1;
	CleanChannel("Clean EXTERNNEEDLE Step1---------#\n", SPI_CMD_CLEAN_DILUENTINTINE);
}


afx_msg LRESULT CCleanView::OnAckspi(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		//清洗完成
	case SPI_STATE_INFO_END:

		//75ha:20150625
		if (1 == ExterCleanFlag && ExterCleanStep < 4)//若是外部针清洗
		{
			uchar SendCmd[] = {
				0,
				SPI_CMD_CLEAN_RINSEINTINE,
				SPI_CMD_CLEAN_DILUENTEXTINE,
				SPI_CMD_CLEAN_RINSEEXTINE
			};
			++ExterCleanStep;

			TRACE("Clean EXTERNNEEDLE Step %d---------#\n", ExterCleanStep + 1);
			sdata_cmd[0] = SendCmd[ExterCleanStep];
			PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
		}
		else
		{
			if (4 == ExterCleanStep)
				ExterCleanStep = ExterCleanFlag = 0;
			KillTimer(POLLTIME);
			DSP_status = Free;
			key_status = TRUE;
		}

		break;
	default:
		break;
	}
	GetDlgItem(IDC_CLEAN_CYTO)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLEAN_CHAMBERS)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLEAN_DILUENTINTINE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLEAN_DILUENTEXTINE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLEAN_GEM)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLEAN_SHEATFLOWPIPE)->EnableWindow(TRUE);
	//GetDlgItem(IDC_CLEAN_RINSEBASO)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLEAN_RINSEINTINE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLEAN_RINSEEXTINE)->EnableWindow(TRUE);
	//GetDlgItem(IDC_CLEAN_EXTERNNEEDLE)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDCANCEL)->EnableWindow(TRUE);

	return 0;
}
