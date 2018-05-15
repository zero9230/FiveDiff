// PrintSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "PrintSetView.h"
#include "FilesOperation.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CPrintSetView 对话框

IMPLEMENT_DYNAMIC(CPrintSetView, CDialogEx)

CPrintSetView::CPrintSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrintSetView::IDD, pParent)
	, m_PrintsizeRadio(0)
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
	VERIFY(textfont1.CreateFont(
		15,                        // nHeight
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

CPrintSetView::~CPrintSetView()
{
}

void CPrintSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SWITCH1, m_AutoprintSwitch);
	DDX_Control(pDX, IDC_SWITCH2, m_PictureSwitch);
	DDX_Radio(pDX, IDC_A4RADIO, m_PrintsizeRadio);
}


BEGIN_MESSAGE_MAP(CPrintSetView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PRINT_APPLICATE, &CPrintSetView::OnPrintApplicate)
END_MESSAGE_MAP()


// CPrintSetView 消息处理程序


void CPrintSetView::OnPaint()
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


BOOL CPrintSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CBCGPSwitchColors colorsHorz;
	colorsHorz.m_brFillOn = CBCGPBrush(CBCGPColor::LightSkyBlue, CBCGPColor::DodgerBlue, CBCGPBrush::BCGP_GRADIENT_HORIZONTAL);
	colorsHorz.m_brFillOff = CBCGPBrush(CBCGPColor::Gainsboro, CBCGPColor::Silver, CBCGPBrush::BCGP_GRADIENT_HORIZONTAL);
	colorsHorz.m_brFillThumb = CBCGPBrush(CBCGPColor::LightGray, CBCGPColor::White, CBCGPBrush::BCGP_GRADIENT_RADIAL_TOP_LEFT);


	m_AutoprintSwitch.GetSwitch()->EnableOnOffLabels();
	m_AutoprintSwitch.GetSwitch()->SetID(IDC_SWITCH1);
	m_AutoprintSwitch.GetSwitch()->SetStyle(CBCGPSwitchImpl::BCGP_SWITCH_ROUNDED_RECTANGLE);
	m_AutoprintSwitch.GetSwitch()->SetColors(colorsHorz);

	m_PictureSwitch.GetSwitch()->EnableOnOffLabels();
	m_PictureSwitch.GetSwitch()->SetID(IDC_SWITCH2);
	m_PictureSwitch.GetSwitch()->SetStyle(CBCGPSwitchImpl::BCGP_SWITCH_ROUNDED_RECTANGLE);
	m_PictureSwitch.GetSwitch()->SetColors(colorsHorz);


	GetDlgItem(IDC_STATIC)->SetFont(&textfont);
	GetDlgItem(IDC_STATIC2)->SetFont(&textfont);
	GetDlgItem(IDC_STATIC3)->SetFont(&textfont1);
	GetDlgItem(IDC_STATIC4)->SetFont(&textfont1);

	GetDlgItem(IDC_A4RADIO)->SetFont(&textfont1);
	GetDlgItem(IDC_A5RADIO)->SetFont(&textfont1);

	if (systemcfg.printercfg.mode == 1)
	{
		m_AutoprintSwitch.GetSwitch()->SetOn(TRUE);
	}
	else m_AutoprintSwitch.GetSwitch()->SetOn(FALSE);
	
	if (systemcfg.printercfg.format == 0)
	{
		m_PictureSwitch.GetSwitch()->SetOn(TRUE);
	}
	else m_PictureSwitch.GetSwitch()->SetOn(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CPrintSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  在此更改 DC 的任何特性

	//switch (pWnd->GetDlgCtrlID())
	//{
	//case IDC_STATIC:
	//case IDC_A4RADIO:
	//case IDC_A5RADIO:
	//	pDC->SetBkMode(TRANSPARENT);
	//	pDC->SetTextColor(RGB(0, 0, 0));
	//	return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	//default:
	//	break;
	//}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CPrintSetView::OnPrintApplicate()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	systemcfg.printercfg.size = m_PrintsizeRadio;
	if (m_AutoprintSwitch.GetSwitch()->IsOn())
	{
		systemcfg.printercfg.mode = 1;
	}
	else
	{
		systemcfg.printercfg.mode = 0;
	}
	
	if (m_PictureSwitch.GetSwitch()->IsOn())
	{
		systemcfg.printercfg.format = 0;
	}
	else systemcfg.printercfg.format = 1;
	WriteSystemcfgFile();
	MessageBox(L"修改成功");
}
