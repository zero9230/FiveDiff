// ChangeAllReagentView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ChangeAllReagentView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
// CChangeAllReagentView 对话框

IMPLEMENT_DYNAMIC(CChangeAllReagentView, CDialogEx)

CChangeAllReagentView::CChangeAllReagentView(CWnd* pParent /*=NULL*/)
: CDialogEx(CChangeAllReagentView::IDD, pParent)
{
	m_nFirstDayOfWeek = 1;
}

CChangeAllReagentView::~CChangeAllReagentView()
{
}

void CChangeAllReagentView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHANGE_D_STARTDATE, m_Dstartdate);
	DDX_Control(pDX, IDC_CHANGE_R_STARTDATE, m_Rstartdate);
	DDX_Control(pDX, IDC_CHANGE_HGB_STARTDATE, m_HGBstartdate);
	DDX_Control(pDX, IDC_CHANGE_EOS_STARTDATE, m_EOSstartdate);
	DDX_Control(pDX, IDC_CHANGE_BAS_STARTDATE, m_BASstartdate);
	DDX_Control(pDX, IDC_CHANGE_D_ENDDATE, m_Denddate);
	DDX_Control(pDX, IDC_CHANGE_R_ENDDATE, m_Renddate);
	DDX_Control(pDX, IDC_CHANGE_HGB_ENDDATE, m_HGBenddate);
	DDX_Control(pDX, IDC_CHANGE_EOS_ENDDATE, m_EOSenddate);
	DDX_Control(pDX, IDC_CHANGE_BAS_ENDDATE, m_BASenddate);
}


BEGIN_MESSAGE_MAP(CChangeAllReagentView, CDialogEx)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChangeAllReagentView 消息处理程序


void CChangeAllReagentView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}


BOOL CChangeAllReagentView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CChangeAllReagentView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_Dstartdate.SizeToContent();
	m_Rstartdate.SizeToContent();
	m_HGBstartdate.SizeToContent();
	m_EOSstartdate.SizeToContent();
	m_BASstartdate.SizeToContent();

	m_Denddate.SizeToContent();
	m_Renddate.SizeToContent();
	m_HGBenddate.SizeToContent();
	m_EOSenddate.SizeToContent();
	m_BASenddate.SizeToContent();

	m_Dstartdate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_Rstartdate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_HGBstartdate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_EOSstartdate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_BASstartdate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	

	m_Denddate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_Renddate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_HGBenddate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_EOSenddate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_BASenddate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);


	ReadSystemcfgFile();
	DiluentStartDate.SetDate(systemcfg.regentdate.startyear[DILUENT], systemcfg.regentdate.startmonth[DILUENT], systemcfg.regentdate.startday[DILUENT]);
	RinseStartDate.SetDate(systemcfg.regentdate.startyear[Rinse], systemcfg.regentdate.startmonth[Rinse], systemcfg.regentdate.startday[Rinse]);
	HGBStartDate.SetDate(systemcfg.regentdate.startyear[HGBLyse], systemcfg.regentdate.startmonth[HGBLyse], systemcfg.regentdate.startday[HGBLyse]);
	EOSStartDate.SetDate(systemcfg.regentdate.startyear[EOSLyse], systemcfg.regentdate.startmonth[EOSLyse], systemcfg.regentdate.startday[EOSLyse]);
	BASStartDate.SetDate(systemcfg.regentdate.startyear[BASLyse], systemcfg.regentdate.startmonth[BASLyse], systemcfg.regentdate.startday[BASLyse]);

	DiluentEndDate.SetDate(systemcfg.regentdate.endyear[DILUENT], systemcfg.regentdate.endmonth[DILUENT], systemcfg.regentdate.endday[DILUENT]);
	RinseEndDate.SetDate(systemcfg.regentdate.endyear[Rinse], systemcfg.regentdate.endmonth[Rinse], systemcfg.regentdate.endday[Rinse]);
	HGBEndDate.SetDate(systemcfg.regentdate.endyear[HGBLyse], systemcfg.regentdate.endmonth[HGBLyse], systemcfg.regentdate.endday[HGBLyse]);
	EOSEndDate.SetDate(systemcfg.regentdate.endyear[EOSLyse], systemcfg.regentdate.endmonth[EOSLyse], systemcfg.regentdate.endday[EOSLyse]);
	BASEndDate.SetDate(systemcfg.regentdate.endyear[BASLyse], systemcfg.regentdate.endmonth[BASLyse], systemcfg.regentdate.endday[BASLyse]);


	m_Dstartdate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_Rstartdate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_HGBstartdate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_EOSstartdate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_BASstartdate.SetFirstDayOfWeek(m_nFirstDayOfWeek);

	m_Denddate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_Renddate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_HGBenddate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_EOSenddate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_BASenddate.SetFirstDayOfWeek(m_nFirstDayOfWeek);

	m_Dstartdate.SetDate(DiluentStartDate);
	m_Rstartdate.SetDate(RinseStartDate);
	m_HGBstartdate.SetDate(HGBStartDate);
	m_EOSstartdate.SetDate(EOSStartDate);
	m_BASstartdate.SetDate(BASStartDate);
	m_Denddate.SetDate(DiluentEndDate);
	m_Renddate.SetDate(RinseEndDate);
	m_HGBenddate.SetDate(HGBEndDate);
	m_EOSenddate.SetDate(EOSEndDate);
	m_BASenddate.SetDate(BASEndDate);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE

}

void CChangeAllReagentView::SaveDate()
{
	DiluentStartDate = m_Dstartdate.GetDate();
	RinseStartDate = m_Rstartdate.GetDate();
	HGBStartDate = m_HGBstartdate.GetDate();
	EOSStartDate = m_EOSstartdate.GetDate();
	BASStartDate = m_BASstartdate.GetDate();

	DiluentEndDate = m_Denddate.GetDate();
	RinseEndDate = m_Renddate.GetDate();
	HGBEndDate = m_HGBenddate.GetDate();
	EOSEndDate = m_EOSenddate.GetDate();
	BASEndDate = m_BASenddate.GetDate();
	//start
	systemcfg.regentdate.startyear[DILUENT] = DiluentStartDate.GetYear();
	systemcfg.regentdate.startmonth[DILUENT] = DiluentStartDate.GetMonth();
	systemcfg.regentdate.startday[DILUENT] = DiluentStartDate.GetDay();

	systemcfg.regentdate.startyear[Rinse] = RinseStartDate.GetYear();
	systemcfg.regentdate.startmonth[Rinse] = RinseStartDate.GetMonth();
	systemcfg.regentdate.startday[Rinse] = RinseStartDate.GetDay();

	systemcfg.regentdate.startyear[HGBLyse] = HGBStartDate.GetYear();
	systemcfg.regentdate.startmonth[HGBLyse] = HGBStartDate.GetMonth();
	systemcfg.regentdate.startday[HGBLyse] = HGBStartDate.GetDay();

	systemcfg.regentdate.startyear[EOSLyse] = EOSStartDate.GetYear();
	systemcfg.regentdate.startmonth[EOSLyse] = EOSStartDate.GetMonth();
	systemcfg.regentdate.startday[EOSLyse] = EOSStartDate.GetDay();

	systemcfg.regentdate.startyear[BASLyse] = BASStartDate.GetYear();
	systemcfg.regentdate.startmonth[BASLyse] = BASStartDate.GetMonth();
	systemcfg.regentdate.startday[BASLyse] = BASStartDate.GetDay();

	//end 
	systemcfg.regentdate.endyear[DILUENT] = DiluentEndDate.GetYear();
	systemcfg.regentdate.endmonth[DILUENT] = DiluentEndDate.GetMonth();
	systemcfg.regentdate.endday[DILUENT] = DiluentEndDate.GetDay();

	systemcfg.regentdate.endyear[Rinse] = RinseEndDate.GetYear();
	systemcfg.regentdate.endmonth[Rinse] = RinseEndDate.GetMonth();
	systemcfg.regentdate.endday[Rinse] = RinseEndDate.GetDay();

	systemcfg.regentdate.endyear[HGBLyse] = HGBEndDate.GetYear();
	systemcfg.regentdate.endmonth[HGBLyse] = HGBEndDate.GetMonth();
	systemcfg.regentdate.endday[HGBLyse] = HGBEndDate.GetDay();

	systemcfg.regentdate.endyear[EOSLyse] = EOSEndDate.GetYear();
	systemcfg.regentdate.endmonth[EOSLyse] = EOSEndDate.GetMonth();
	systemcfg.regentdate.endday[EOSLyse] = EOSEndDate.GetDay();

	systemcfg.regentdate.endyear[BASLyse] = BASEndDate.GetYear();
	systemcfg.regentdate.endmonth[BASLyse] = BASEndDate.GetMonth();
	systemcfg.regentdate.endday[BASLyse] = BASEndDate.GetDay();
	
	WriteSystemcfgFile();
}

void CChangeAllReagentView::SaveReagentAmount()
{
	systemcfg.regentfull.diluent = 10000;		//FDparam
	systemcfg.regentfull.rinse = 10000;
	systemcfg.regentfull.hgblyse = 10000;
	systemcfg.regentfull.eoslyse = 10000;
	systemcfg.regentfull.baslyse = 10000;

	WriteSystemcfgFile();
}
void CChangeAllReagentView::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	SaveDate();
	SaveReagentAmount();
	CDialogEx::OnOK();

}


HBRUSH CChangeAllReagentView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
