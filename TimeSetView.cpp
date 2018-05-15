// TimeSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "TimeSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CTimeSetView 对话框

IMPLEMENT_DYNAMIC(CTimeSetView, CDialogEx)

CTimeSetView::CTimeSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeSetView::IDD, pParent)
{

}

CTimeSetView::~CTimeSetView()
{
}

void CTimeSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTimeSetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTimeSetView 消息处理程序


void CTimeSetView::OnPaint()
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
