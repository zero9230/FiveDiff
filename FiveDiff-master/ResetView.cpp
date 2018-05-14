// ResetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ResetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
// CResetView 对话框

IMPLEMENT_DYNAMIC(CResetView, CDialogEx)

CResetView::CResetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResetView::IDD, pParent)
{
	VERIFY(textfont.CreateFont(
		20,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		GB2312_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		L"宋体"));                 // lpszFacename
}

CResetView::~CResetView()
{
}

void CResetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESET_STATIC, m_statictext);
}


BEGIN_MESSAGE_MAP(CResetView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_DEFAULT_SET, &CResetView::OnSetDefault)
END_MESSAGE_MAP()


// CResetView 消息处理程序


void CResetView::OnPaint()
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


BOOL CResetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CWnd *cWnd = GetDlgItem(IDC_RESET_STATIC);
	cWnd->SetFont(&textfont);
	//cWnd->SetWindowTextW(L"设置需要的内容");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

HBRUSH CResetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_RESET_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CResetView::OnSetDefault()
{
	// TODO:  在此添加控件通知处理程序代码
	uchar 		lan_temp;		//保存恢复系统默认参数前的语言选项
	lan_temp = systemcfg.language;
	::CopyFile(L".//Config//DefaultSet//systemcfg.dat",L".//Config//systemcfg.dat",false);//false表示如文件存在则覆盖
	ReadSystemcfgFile();
	systemcfg.language = lan_temp;
	
	if (systemcfg.language == CHINESE)
	{
		m_statictext.ShowWindow(SW_HIDE);
		m_statictext.SetWindowText(L"成功恢复系统默认配置!");
		m_statictext.ShowWindow(SW_SHOW);
	}
	else if (systemcfg.language == ENGLISH)
	{
		m_statictext.ShowWindow(SW_HIDE);
		m_statictext.SetWindowText(L"Recover Default Settings Success !");
		m_statictext.ShowWindow(SW_SHOW);
	}
}

