// FaultstatisticsView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "FaultstatisticsView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CFaultstatisticsView 对话框

IMPLEMENT_DYNAMIC(CFaultstatisticsView, CDialogEx)

CFaultstatisticsView::CFaultstatisticsView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFaultstatisticsView::IDD, pParent)
{

}

CFaultstatisticsView::~CFaultstatisticsView()
{
}

void CFaultstatisticsView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFaultstatisticsView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ALERT_XMEMPTY, &CFaultstatisticsView::OnBnClickedAlertXmempty)
	ON_BN_CLICKED(IDC_ALERT_YMEMPTY, &CFaultstatisticsView::OnBnClickedAlertYmempty)
	ON_BN_CLICKED(IDC_ALERT_SMEMPTY, &CFaultstatisticsView::OnBnClickedAlertSmempty)
	ON_BN_CLICKED(IDC_ALERT_DIMEMPTY, &CFaultstatisticsView::OnBnClickedAlertDimempty)
	ON_BN_CLICKED(IDC_ALERT_DRMEMPTY, &CFaultstatisticsView::OnBnClickedAlertDrmempty)
	ON_BN_CLICKED(IDC_ALERT_CTMEMPTY, &CFaultstatisticsView::OnBnClickedAlertCtmempty)
	ON_BN_CLICKED(IDC_ALERT_CYMEMPTY, &CFaultstatisticsView::OnBnClickedAlertCymempty)
	ON_BN_CLICKED(IDC_ALERT_WBCEMPTY, &CFaultstatisticsView::OnBnClickedAlertWbcempty)
	ON_BN_CLICKED(IDC_ALERT_RBCEMPTY, &CFaultstatisticsView::OnBnClickedAlertRbcempty)
	ON_BN_CLICKED(IDC_ALERT_WLEMPTY, &CFaultstatisticsView::OnBnClickedAlertWlempty)
	ON_BN_CLICKED(IDC_ALERT_DILTMEMPTY, &CFaultstatisticsView::OnBnClickedAlertDiltmempty)
	ON_BN_CLICKED(IDC_ALERT_WLFEMPTY, &CFaultstatisticsView::OnBnClickedAlertWlfempty)
	ON_BN_CLICKED(IDC_ALERT_TNEMPTY, &CFaultstatisticsView::OnBnClickedAlertTnempty)
	ON_BN_CLICKED(IDC_ALERT_ALLMEMPTY, &CFaultstatisticsView::OnBnClickedAlertAllmempty)
END_MESSAGE_MAP()


// CFaultstatisticsView 消息处理程序


void CFaultstatisticsView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	/*@TG
#3073*/
	int i=0;
	CString str;
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为白色背景
	dc.Rectangle(20, 20, rect.right/2-5 , rect.bottom - 50);
	dc.Rectangle(rect.right/2+5, 20, rect.right - 20, rect.bottom - 50);
	for (i=1;i<13;i++)
	{
		str.Format(L"%d",logfile.alertnum[i]);
		GetDlgItem(IDC_ALERT_XM+i-1)->SetWindowText((LPCTSTR)str);	
	}
	str.Format(L"%d",logfile.totaltimesoftest);
		GetDlgItem(IDC_ALERT_TN)->SetWindowText((LPCTSTR)str);	
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()
}


HBRUSH CFaultstatisticsView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

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
//	return hbr;
	
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		//pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//文字背景色
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//控件背景色   
		return b;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CFaultstatisticsView::OnBnClickedAlertXmempty()
{
	logfile.alertnum[1] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertYmempty()
{
	logfile.alertnum[2] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertSmempty()
{
	logfile.alertnum[3] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertDimempty()
{
	logfile.alertnum[4] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertDrmempty()
{
	logfile.alertnum[5] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertCtmempty()
{
	logfile.alertnum[6] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertCymempty()
{
	logfile.alertnum[7] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertWbcempty()
{
	logfile.alertnum[8] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertRbcempty()
{
	logfile.alertnum[9] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertWlempty()
{
	logfile.alertnum[10] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertDiltmempty()
{
	logfile.alertnum[11] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertWlfempty()
{
	logfile.alertnum[12] = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertTnempty()
{
	logfile.totaltimesoftest = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}


void CFaultstatisticsView::OnBnClickedAlertAllmempty()
{
	int i = 0;
	for(i=1;i<13;i++)
		logfile.alertnum[i] = 0;
	logfile.totaltimesoftest = 0;
	SendMessage(WM_PAINT);
	// TODO: 在此添加控件通知处理程序代码
}
