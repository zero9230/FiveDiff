// DevelopmentSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "DevelopmentSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CDevelopmentSetView 对话框

IMPLEMENT_DYNAMIC(CDevelopmentSetView, CDialogEx)

CDevelopmentSetView::CDevelopmentSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevelopmentSetView::IDD, pParent)
{

}

CDevelopmentSetView::~CDevelopmentSetView()
{
}

void CDevelopmentSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDevelopmentSetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDevelopmentSetView 消息处理程序


void CDevelopmentSetView::OnPaint()
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
