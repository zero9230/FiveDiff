// DevelopmentSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "DevelopmentSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"


// CDevelopmentSetView 对话框

IMPLEMENT_DYNAMIC(CDevelopmentSetView, CDialogEx)

CDevelopmentSetView::CDevelopmentSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevelopmentSetView::IDD, pParent)
	, m_structureRadio(0)
	, m_diluentRadio(0)
{

}

CDevelopmentSetView::~CDevelopmentSetView()
{
}

void CDevelopmentSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_STRUCTURE_NOPUNCTURE, m_structureRadio);
	DDX_Radio(pDX, IDC_DEVELOPERSET_DILUENT_20UL, m_diluentRadio);
}


BEGIN_MESSAGE_MAP(CDevelopmentSetView, CDialogEx)
	ON_WM_PAINT()	
	ON_BN_CLICKED(IDC_APPLY, &CDevelopmentSetView::OnBnClickedApply)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDevelopmentSetView 消息处理程序
BOOL CDevelopmentSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_structureRadio = systemcfg3.structure;
	m_diluentRadio = systemcfg3.diluent;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


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


void CDevelopmentSetView::OnBnClickedApply()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	systemcfg3.structure = m_structureRadio;
	systemcfg3.diluent = m_diluentRadio;


	WriteSystemcfg3File();
	MessageBox(L"保存成功");

}




HBRUSH CDevelopmentSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STRUCTURE_NOPUNCTURE:
	case IDC_STRUCTURE_PUNCTURE:
	case IDC_STRUCTURE_AUTOSAMPLE:
	case IDC_DEVELOPERSET_DILUENT_20UL:
	case IDC_DEVELOPERSET_DILUENT_50UL:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
