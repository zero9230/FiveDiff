// UploadSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "UploadSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CUploadSetView 对话框

IMPLEMENT_DYNAMIC(CUploadSetView, CDialogEx)

CUploadSetView::CUploadSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUploadSetView::IDD, pParent)
{

}

CUploadSetView::~CUploadSetView()
{
}

void CUploadSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUploadSetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CUploadSetView 消息处理程序


void CUploadSetView::OnPaint()
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
