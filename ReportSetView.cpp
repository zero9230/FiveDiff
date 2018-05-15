// ReportSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ReportSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CReportSetView 对话框

IMPLEMENT_DYNAMIC(CReportSetView, CDialogEx)

CReportSetView::CReportSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReportSetView::IDD, pParent)
{

}

CReportSetView::~CReportSetView()
{
}

void CReportSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReportSetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CReportSetView 消息处理程序


void CReportSetView::OnPaint()
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
