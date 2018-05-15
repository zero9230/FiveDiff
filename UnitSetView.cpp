// UnitSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "UnitSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"

// CUnitSetView 对话框

IMPLEMENT_DYNAMIC(CUnitSetView, CDialogEx)

CUnitSetView::CUnitSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUnitSetView::IDD, pParent)
	, m_WBCunitRadio(0)
	, m_RBCunitRadio(0)
	, m_HGBunitRadio(0)
	, m_MCVunitRadio(0)
	, m_MCHunitRadio(0)
	, m_MCHCunitRadio(0)
	, m_PLTunitRadio(0)
	, m_MPVunitRadio(0)
	, m_PDWunitRadio(0)
	, m_OtherunitRadio(0)
{

}

CUnitSetView::~CUnitSetView()
{
}

void CUnitSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_WBCunitRadio);
	DDX_Radio(pDX, IDC_RADIO5, m_RBCunitRadio);
	DDX_Radio(pDX, IDC_RADIO9, m_HGBunitRadio);
	DDX_Radio(pDX, IDC_RADIO12, m_MCVunitRadio);
	DDX_Radio(pDX, IDC_RADIO14, m_MCHunitRadio);
	DDX_Radio(pDX, IDC_RADIO16, m_MCHCunitRadio);
	DDX_Radio(pDX, IDC_RADIO19, m_PLTunitRadio);
	DDX_Radio(pDX, IDC_RADIO23, m_MPVunitRadio);
	DDX_Radio(pDX, IDC_RADIO25, m_PDWunitRadio);
	DDX_Radio(pDX, IDC_RADIO26, m_OtherunitRadio);
}


BEGIN_MESSAGE_MAP(CUnitSetView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_UNIT_APPLICATE, &CUnitSetView::OnUnitApplicate)
END_MESSAGE_MAP()


// CUnitSetView 消息处理程序


void CUnitSetView::OnPaint()
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


BOOL CUnitSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_WBCunitRadio = systemcfg.unitWBC;
	m_RBCunitRadio = systemcfg.unitRBC;
	m_HGBunitRadio = systemcfg.unitHGB;
	m_MCVunitRadio = systemcfg.unitMCVRDWSD;
	m_MCHunitRadio = systemcfg.unitMCH;
	m_MCHCunitRadio = systemcfg.unitMCHC;
	m_PLTunitRadio = systemcfg.unitPLT;
	m_MPVunitRadio = systemcfg.unitMPV;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CUnitSetView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_RADIO1:
	case IDC_RADIO2:
	case IDC_RADIO3:
	case IDC_RADIO4:
	case IDC_RADIO5:
	case IDC_RADIO6:
	case IDC_RADIO7:
	case IDC_RADIO8:
	case IDC_RADIO9:
	case IDC_RADIO10:
	case IDC_RADIO11:
	case IDC_RADIO12:
	case IDC_RADIO13:
	case IDC_RADIO14:
	case IDC_RADIO15:
	case IDC_RADIO16:
	case IDC_RADIO17:
	case IDC_RADIO18:
	case IDC_RADIO19:
	case IDC_RADIO20:
	case IDC_RADIO21:
	case IDC_RADIO22:
	case IDC_RADIO23:
	case IDC_RADIO24:
	case IDC_RADIO25:
	case IDC_RADIO26:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CUnitSetView::OnUnitApplicate()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	systemcfg.unitWBC = m_WBCunitRadio;
	systemcfg.unitRBC = m_RBCunitRadio ;
	systemcfg.unitHGB = m_HGBunitRadio ;
	systemcfg.unitMCVRDWSD = m_MCVunitRadio;
	systemcfg.unitMCH = m_MCHunitRadio;
	systemcfg.unitMCHC = m_MCHCunitRadio;
	systemcfg.unitPLT = m_PLTunitRadio;
	systemcfg.unitMPV = m_MPVunitRadio;
	WriteSystemcfgFile();
	MessageBox(L"保存成功");
}
