// AboutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "AboutDlg.h"
#include "afxdialogex.h"


// CAboutDlg 对话框

IMPLEMENT_DYNAMIC(CAboutDlg, CDialogEx)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAboutDlg::IDD, pParent)
{
	
}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAboutDlg 消息处理程序


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC || nCtlColor== CTLCOLOR_BTN)
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


void CAboutDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnEraseBkgnd(pDC);
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_COPYRIGHT)->SetWindowText(L"Copyright© 2018-2028 Sinnowa Co Ltd. All rights reserved");
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
