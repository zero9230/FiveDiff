// ThresholdSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ThresholdSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
// CThresholdSetView 对话框

IMPLEMENT_DYNAMIC(CThresholdSetView, CDialogEx)

CThresholdSetView::CThresholdSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThresholdSetView::IDD, pParent)
{

}

CThresholdSetView::~CThresholdSetView()
{
}

void CThresholdSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CThresholdSetView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_THRESHOLD_APPLICATE, &CThresholdSetView::OnThresholdApplicate)
END_MESSAGE_MAP()


// CThresholdSetView 消息处理程序


void CThresholdSetView::OnPaint()
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


HBRUSH CThresholdSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CThresholdSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString thresholdtemp[25];
	for (int i = 0; i < 25; i++)
	{
		thresholdtemp[i].Format(L"%d",systemcfg.range.thresholds[i]);
	}

	GetDlgItem(IDC_THRESHOLDS_NOL)->SetWindowText(thresholdtemp[0]);
	GetDlgItem(IDC_THRESHOLDS_NON)->SetWindowText(thresholdtemp[1]);
	GetDlgItem(IDC_THRESHOLDS_LL)->SetWindowText(thresholdtemp[2]);
	GetDlgItem(IDC_THRESHOLDS_LN)->SetWindowText(thresholdtemp[3]);
	GetDlgItem(IDC_THRESHOLDS_NOE)->SetWindowText(thresholdtemp[4]);
	GetDlgItem(IDC_THRESHOLDS_LMN)->SetWindowText(thresholdtemp[5]);
	GetDlgItem(IDC_THRESHOLDS_AL)->SetWindowText(thresholdtemp[6]);
	GetDlgItem(IDC_THRESHOLDS_LMU)->SetWindowText(thresholdtemp[7]);
	GetDlgItem(IDC_THRESHOLDS_LMD)->SetWindowText(thresholdtemp[8]);
	GetDlgItem(IDC_THRESHOLDS_MN)->SetWindowText(thresholdtemp[9]);
	GetDlgItem(IDC_THRESHOLDS_RM)->SetWindowText(thresholdtemp[10]);
	GetDlgItem(IDC_THRESHOLDS_RN)->SetWindowText(thresholdtemp[11]);
	GetDlgItem(IDC_THRESHOLDS_NL)->SetWindowText(thresholdtemp[12]);
	GetDlgItem(IDC_THRESHOLDS_RMN)->SetWindowText(thresholdtemp[13]);
	GetDlgItem(IDC_THRESHOLDS_NE)->SetWindowText(thresholdtemp[14]);
	GetDlgItem(IDC_THRESHOLDS_RLN)->SetWindowText(thresholdtemp[15]);
	GetDlgItem(IDC_THRESHOLDS_FNE)->SetWindowText(thresholdtemp[16]);
	GetDlgItem(IDC_THRESHOLDS_FMN)->SetWindowText(thresholdtemp[17]);
	GetDlgItem(IDC_THRESHOLDS_BA1)->SetWindowText(thresholdtemp[18]);
	GetDlgItem(IDC_THRESHOLDS_BA2)->SetWindowText(thresholdtemp[19]);
	GetDlgItem(IDC_THRESHOLDS_BA3)->SetWindowText(thresholdtemp[20]);
	GetDlgItem(IDC_THRESHOLDS_RB1)->SetWindowText(thresholdtemp[21]);
	GetDlgItem(IDC_THRESHOLDS_RB2)->SetWindowText(thresholdtemp[22]);
	GetDlgItem(IDC_THRESHOLDS_PLT1)->SetWindowText(thresholdtemp[23]);
	GetDlgItem(IDC_THRESHOLDS_PLT2)->SetWindowText(thresholdtemp[24]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



void CThresholdSetView::OnThresholdApplicate()
{
	// TODO:  在此添加控件通知处理程序代码
	CString thresholdtemp[25];
	GetDlgItem(IDC_THRESHOLDS_NOL)->GetWindowText(thresholdtemp[0]);
	GetDlgItem(IDC_THRESHOLDS_NON)->GetWindowText(thresholdtemp[1]);
	GetDlgItem(IDC_THRESHOLDS_LL)->GetWindowText(thresholdtemp[2]);
	GetDlgItem(IDC_THRESHOLDS_LN)->GetWindowText(thresholdtemp[3]);
	GetDlgItem(IDC_THRESHOLDS_NOE)->GetWindowText(thresholdtemp[4]);
	GetDlgItem(IDC_THRESHOLDS_LMN)->GetWindowText(thresholdtemp[5]);
	GetDlgItem(IDC_THRESHOLDS_AL)->GetWindowText(thresholdtemp[6]);
	GetDlgItem(IDC_THRESHOLDS_LMU)->GetWindowText(thresholdtemp[7]);
	GetDlgItem(IDC_THRESHOLDS_LMD)->GetWindowText(thresholdtemp[8]);
	GetDlgItem(IDC_THRESHOLDS_MN)->GetWindowText(thresholdtemp[9]);
	GetDlgItem(IDC_THRESHOLDS_RM)->GetWindowText(thresholdtemp[10]);
	GetDlgItem(IDC_THRESHOLDS_RN)->GetWindowText(thresholdtemp[11]);
	GetDlgItem(IDC_THRESHOLDS_NL)->GetWindowText(thresholdtemp[12]);
	GetDlgItem(IDC_THRESHOLDS_RMN)->GetWindowText(thresholdtemp[13]);
	GetDlgItem(IDC_THRESHOLDS_NE)->GetWindowText(thresholdtemp[14]);
	GetDlgItem(IDC_THRESHOLDS_RLN)->GetWindowText(thresholdtemp[15]);
	GetDlgItem(IDC_THRESHOLDS_FNE)->GetWindowText(thresholdtemp[16]);
	GetDlgItem(IDC_THRESHOLDS_FMN)->GetWindowText(thresholdtemp[17]);
	GetDlgItem(IDC_THRESHOLDS_BA1)->GetWindowText(thresholdtemp[18]);
	GetDlgItem(IDC_THRESHOLDS_BA2)->GetWindowText(thresholdtemp[19]);
	GetDlgItem(IDC_THRESHOLDS_BA3)->GetWindowText(thresholdtemp[20]);
	GetDlgItem(IDC_THRESHOLDS_RB1)->GetWindowText(thresholdtemp[21]);
	GetDlgItem(IDC_THRESHOLDS_RB2)->GetWindowText(thresholdtemp[22]);
	GetDlgItem(IDC_THRESHOLDS_PLT1)->GetWindowText(thresholdtemp[23]);
	GetDlgItem(IDC_THRESHOLDS_PLT2)->GetWindowText(thresholdtemp[24]);

	for (int i = 0; i < 25; i++)
	{
		thresholdtemp[i].Format(L"%d", systemcfg.range.thresholds[i]);
		systemcfg.range.thresholds[i] = _wtoi(thresholdtemp[i]);
	}
	WriteSystemcfgFile();
}
