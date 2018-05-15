// ValvetestView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ValvetestView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CValvetestView 对话框

IMPLEMENT_DYNAMIC(CValvetestView, CDialogEx)

CValvetestView::CValvetestView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CValvetestView::IDD, pParent)
{

}

CValvetestView::~CValvetestView()
{

}

void CValvetestView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CValvetestView, CDialogEx)
	ON_BN_CLICKED(IDC_CHVALVES_V1, &CValvetestView::OnChvalvesV1)
	ON_BN_CLICKED(IDC_CHVALVES_V2, &CValvetestView::OnChvalvesV2)
	ON_BN_CLICKED(IDC_CHVALVES_V3, &CValvetestView::OnChvalvesV3)
	ON_BN_CLICKED(IDC_CHVALVES_V4, &CValvetestView::OnChvalvesV4)
	ON_BN_CLICKED(IDC_CHVALVES_V5, &CValvetestView::OnChvalvesV5)
	ON_BN_CLICKED(IDC_CHVALVES_V6, &CValvetestView::OnChvalvesV6)
	ON_BN_CLICKED(IDC_CHVALVES_V7, &CValvetestView::OnChvalvesV7)
	ON_BN_CLICKED(IDC_CHVALVES_V8, &CValvetestView::OnChvalvesV8)
	ON_BN_CLICKED(IDC_CHVALVES_V9, &CValvetestView::OnChvalvesV9)
	ON_BN_CLICKED(IDC_CHVALVES_V10, &CValvetestView::OnChvalvesV10)
	ON_BN_CLICKED(IDC_CHVALVES_V11, &CValvetestView::OnChvalvesV11)
	ON_BN_CLICKED(IDC_CHVALVES_V12, &CValvetestView::OnChvalvesV12)
	ON_BN_CLICKED(IDC_CHVALVES_V13, &CValvetestView::OnChvalvesV13)
	ON_BN_CLICKED(IDC_CHVALVES_V14, &CValvetestView::OnChvalvesV14)
	ON_BN_CLICKED(IDC_CHVALVES_V15, &CValvetestView::OnChvalvesV15)
	ON_BN_CLICKED(IDC_CHVALVES_V16, &CValvetestView::OnChvalvesV16)
	ON_BN_CLICKED(IDC_CHVALVES_V17, &CValvetestView::OnChvalvesV17)
	ON_BN_CLICKED(IDC_CHVALVES_V18, &CValvetestView::OnChvalvesV18)
	ON_BN_CLICKED(IDC_CHVALVES_V19, &CValvetestView::OnChvalvesV19)
	ON_BN_CLICKED(IDC_CHVALVES_V20, &CValvetestView::OnChvalvesV20)
	ON_BN_CLICKED(IDC_CHVALVES_V21, &CValvetestView::OnChvalvesV21)
	ON_BN_CLICKED(IDC_CHVALVES_V22, &CValvetestView::OnChvalvesV22)
	ON_BN_CLICKED(IDC_CHVALVES_V23, &CValvetestView::OnChvalvesV23)
	ON_BN_CLICKED(IDC_CHVALVES_V24, &CValvetestView::OnChvalvesV24)
	ON_BN_CLICKED(IDC_CHVALVES_V25, &CValvetestView::OnChvalvesV25)
	ON_BN_CLICKED(IDC_CHVALVES_V26, &CValvetestView::OnChvalvesV26)
	ON_BN_CLICKED(IDC_CHVALVES_V27, &CValvetestView::OnChvalvesV27)
	ON_BN_CLICKED(IDC_CHVALVES_V28, &CValvetestView::OnChvalvesV28)
	ON_BN_CLICKED(IDC_CHVALVES_V29, &CValvetestView::OnChvalvesV29)
	ON_BN_CLICKED(IDC_CHVALVES_V30, &CValvetestView::OnChvalvesV30)
	ON_BN_CLICKED(IDC_CHVALVES_V31, &CValvetestView::OnChvalvesV31)
	ON_BN_CLICKED(IDC_CHVALVES_V32, &CValvetestView::OnChvalvesV32)
	ON_BN_CLICKED(IDC_CHVALVES_V33, &CValvetestView::OnChvalvesV33)
	ON_BN_CLICKED(IDC_CHVALVES_V34, &CValvetestView::OnChvalvesV34)
	ON_BN_CLICKED(IDC_CHVALVES_V35, &CValvetestView::OnChvalvesV35)
	ON_BN_CLICKED(IDC_CHVALVES_V36, &CValvetestView::OnChvalvesV36)
	ON_BN_CLICKED(IDC_CHVALVES_V37, &CValvetestView::OnChvalvesV37)
	ON_BN_CLICKED(IDC_CHVALVES_V38, &CValvetestView::OnChvalvesV38)
	ON_BN_CLICKED(IDC_CHVALVES_V39, &CValvetestView::OnChvalvesV39)
	ON_BN_CLICKED(IDC_CHVALVES_V40, &CValvetestView::OnChvalvesV40)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CValvetestView 消息处理程序


void CValvetestView::OnChvalvesV1()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V1---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V1;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}



void CValvetestView::OnChvalvesV2()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V2---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V2;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV3()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V3---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V3;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV4()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V4---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V4;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV5()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V5---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V5;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV6()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V6---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V6;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV7()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V7---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V7;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV8()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V8---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V8;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV9()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V9---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V9;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV10()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V10---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V10;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}



void CValvetestView::OnChvalvesV11()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V11---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V11;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV12()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V12---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V12;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV13()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V13---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V13;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV14()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V4---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V14;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV15()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V15---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V15;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV16()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V16---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V16;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV17()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V17---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V17;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV18()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V18---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V18;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV19()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V19---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V19;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV20()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V20---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V20;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV21()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V21---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V21;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV22()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V22---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V22;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV23()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V23---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V23;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV24()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V24---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V24;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}



void CValvetestView::OnChvalvesV25()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V25---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V25;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV26()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V26---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V26;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV27()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V27---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V27;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV28()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V28---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V28;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV29()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V29---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V29;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV30()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V30---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V30;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV31()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V31---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V31;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV32()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V32---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V32;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV33()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V33--------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_TUBE;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV34()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V34---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V34;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV35()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V35---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V35;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV36()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V36---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V36;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV37()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V37---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V37;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV38()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V38---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V38;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV39()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V39---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V39;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnChvalvesV40()
{
	// TODO:  在此添加控件通知处理程序代码
	TRACE("Test V40---------#\n");
	sdata_cmd[0] = SPI_CMD_TEST_V40;
	PC_SEND_FRAME(sdata_cmd, SPI_TYPE_CMD);
}


void CValvetestView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为绿色背景
}


BOOL CValvetestView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
