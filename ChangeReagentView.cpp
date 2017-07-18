// ChangeReagentView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ChangeReagentView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CChangeReagentView 对话框

IMPLEMENT_DYNAMIC(CChangeReagentView, CDialogEx)

CChangeReagentView::CChangeReagentView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeReagentView::IDD, pParent)
{
	m_nFirstDayOfWeek = 1;
}

CChangeReagentView::~CChangeReagentView()
{
}

void CChangeReagentView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_startdate);
	DDX_Control(pDX, IDC_BUTTON2, m_enddate);
	DDX_Control(pDX, IDC_REAGENT_COMBO, m_reagentbox);
}


BEGIN_MESSAGE_MAP(CChangeReagentView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_CBN_SELCHANGE(IDC_REAGENT_COMBO, &CChangeReagentView::OnChangeReagentCombo)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChangeReagentView 消息处理程序


void CChangeReagentView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}


BOOL CChangeReagentView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnEraseBkgnd(pDC);
}

BOOL CChangeReagentView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_startdate.SizeToContent();
	m_enddate.SizeToContent();

	m_startdate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_enddate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);

	m_startdate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_enddate.SetFirstDayOfWeek(m_nFirstDayOfWeek);

	m_reagentbox.AddString(L"空");
	m_reagentbox.AddString(L"稀释液");
	m_reagentbox.AddString(L"清洗剂");
	m_reagentbox.AddString(L"HB5D-HGB");
	m_reagentbox.AddString(L"HB5D-EOS");
	m_reagentbox.AddString(L"HB5D-BAS");

	m_reagentbox.SetCurSel(0);

	m_startdate.SetDate(COleDateTime::GetCurrentTime());
	m_enddate.SetDate(COleDateTime::GetCurrentTime());
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CChangeReagentView::SaveDate()
{

	int reagent = m_reagentbox.GetCurSel();
	 startdate=m_startdate.GetDate();
	 enddate = m_enddate.GetDate();
	 if (reagent >= 1)
	 {
		 //start
		 systemcfg.regentdate.startyear[reagent-1] = startdate.GetYear();
		 systemcfg.regentdate.startmonth[reagent-1] = startdate.GetMonth();
		 systemcfg.regentdate.startday[reagent-1] = startdate.GetDay();
		 //end
		 systemcfg.regentdate.endyear[reagent-1] = enddate.GetYear();
		 systemcfg.regentdate.endmonth[reagent-1] = enddate.GetMonth();
		 systemcfg.regentdate.endday[reagent-1] = enddate.GetDay();
	 }
}

void CChangeReagentView::SaveReagentAmount()
{
	int reagent = m_reagentbox.GetCurSel();
	switch (reagent)
	{
	case DILUENT+1: 
		systemcfg.regentfull.diluent = 10000;		//FDparam
		break;
	case Rinse+1:
		systemcfg.regentfull.rinse = 10000;
		break;
	case HGBLyse+1:
		systemcfg.regentfull.hgblyse = 10000;
		break;
	case EOSLyse+1:
		systemcfg.regentfull.eoslyse = 10000;
		break;
	case BASLyse+1:
		systemcfg.regentfull.baslyse = 10000;
		break;
	default:
		break;
	}

}

void CChangeReagentView::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	SaveDate();
	SaveReagentAmount();
	CDialogEx::OnOK();
}

void CChangeReagentView::OnChangeReagentCombo()
{
	// TODO:  在此添加控件通知处理程序代码
	int num = m_reagentbox.GetCurSel();
	if (num >= 1)
	{
		startdate.SetDate(systemcfg.regentdate.startyear[num-1], systemcfg.regentdate.startmonth[num-1], systemcfg.regentdate.startday[num-1]);
		enddate.SetDate(systemcfg.regentdate.endyear[num-1], systemcfg.regentdate.endmonth[num-1], systemcfg.regentdate.endday[num-1]);
		m_startdate.SetDate(startdate);
		m_enddate.SetDate(enddate);
	}
	else {

		m_startdate.SetDate(COleDateTime::GetCurrentTime());
		m_enddate.SetDate(COleDateTime::GetCurrentTime());
	}
}


HBRUSH CChangeReagentView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
