// MaintainView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "MaintainView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CMaintainView 对话框

IMPLEMENT_DYNAMIC(CMaintainView, CDialogEx)

CMaintainView::CMaintainView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMaintainView::IDD, pParent)
{

}

CMaintainView::~CMaintainView()
{
}

void CMaintainView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMaintainView, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMaintainView 消息处理程序


int CMaintainView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


BOOL CMaintainView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CMaintainView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}
