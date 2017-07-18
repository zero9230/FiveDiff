// BackupRestoreView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "BackupRestoreView.h"
#include "afxdialogex.h"


// CBackupRestoreView 对话框

IMPLEMENT_DYNAMIC(CBackupRestoreView, CDialogEx)

CBackupRestoreView::CBackupRestoreView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBackupRestoreView::IDD, pParent)
{

}

CBackupRestoreView::~CBackupRestoreView()
{
}

void CBackupRestoreView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBackupRestoreView, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBackupRestoreView 消息处理程序


BOOL CBackupRestoreView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CBackupRestoreView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CBackupRestoreView::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}


void CBackupRestoreView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}



void CBackupRestoreView::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CBackupRestoreView::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


void CBackupRestoreView::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}
