// CompanySetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "CompanySetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CCompanySetView 对话框

IMPLEMENT_DYNAMIC(CCompanySetView, CDialogEx)

CCompanySetView::CCompanySetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCompanySetView::IDD, pParent)
{

}

CCompanySetView::~CCompanySetView()
{
}

void CCompanySetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCompanySetView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCompanySetView 消息处理程序


void CCompanySetView::OnPaint()
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
