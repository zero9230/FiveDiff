// Reagentmanagement2View.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "Reagentmanagement2View.h"
#include "ChangeAllReagentView.h"
#include "ChangeReagentView.h"
#include "FilesOperation.h"
#include "Resource.h"
//#include "Includes_app.h"
// CReagentmanagement2View

#define Diluent_Top_Level   10000
#define Rinse_Top_Level     10000
#define HGB_Top_Level       10000
#define EOS_Top_Level       10000
#define BAS_Top_Level       10000



IMPLEMENT_DYNCREATE(CReagentmanagement2View, CBCGPChartExampleView)

CReagentmanagement2View::CReagentmanagement2View()
: CBCGPChartExampleView(CReagentmanagement2View::IDD)
{
	m_nFirstDayOfWeek = 1;
}

CReagentmanagement2View::~CReagentmanagement2View()
{

}

void CReagentmanagement2View::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_TIMEPICKER1, m_DiluentStartDate);
	DDX_Control(pDX, IDC_START_TIMEPICKER2, m_RinseStartDate);
	DDX_Control(pDX, IDC_START_TIMEPICKER3, m_HGBStartDate);
	DDX_Control(pDX, IDC_START_TIMEPICKER4, m_EOSStartDate);
	DDX_Control(pDX, IDC_START_TIMEPICKER5, m_BASStartDate);
	DDX_Control(pDX, IDC_END_TIMEPICKER1, m_DiluentEndDate);
	DDX_Control(pDX, IDC_END_TIMEPICKER2, m_RinseEndDate);
	DDX_Control(pDX, IDC_END_TIMEPICKER3, m_HGBEndDate);
	DDX_Control(pDX, IDC_END_TIMEPICKER4, m_EOSEndDate);
	DDX_Control(pDX, IDC_END_TIMEPICKER5, m_BASEndDate);
	DDX_Control(pDX, IDC_DILUENT, m_Diluent_Status);
}

BEGIN_MESSAGE_MAP(CReagentmanagement2View, CBCGPChartExampleView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHANGE_ALL_REAGENT, &CReagentmanagement2View::OnChangeAllReagent)
	ON_BN_CLICKED(IDC_CHANGE_REAGENT, &CReagentmanagement2View::OnChangeReagent)
END_MESSAGE_MAP()


// CReagentmanagement2View 诊断

#ifdef _DEBUG
void CReagentmanagement2View::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CReagentmanagement2View::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReagentmanagement2View 消息处理程序


void CReagentmanagement2View::OnPaint()
{


	PaintLevel();
	RECT rc;

	
	
	CWnd *pWnd = 0;
	pWnd = GetDlgItem(IDC_HB5D_BAS);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	




	pWnd = GetDlgItem(IDC_DILUENT);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_RINSE);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_HB5D_HGB);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	pWnd = GetDlgItem(IDC_HB5D_EOS);
	pWnd->GetClientRect(&rc);
	pWnd->ValidateRect(&rc);
	





	//Paint_Diluent();
}


void CReagentmanagement2View::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	m_DiluentStartDate.SizeToContent();
	m_RinseStartDate.SizeToContent();
	m_HGBStartDate.SizeToContent();
	m_EOSStartDate.SizeToContent();
	m_BASStartDate.SizeToContent();
	m_DiluentEndDate.SizeToContent();
	m_RinseEndDate.SizeToContent();
	m_HGBEndDate.SizeToContent();
	m_EOSEndDate.SizeToContent();
	m_BASEndDate.SizeToContent();

	m_DiluentStartDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_RinseStartDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_HGBStartDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_EOSStartDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_BASStartDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);

	m_DiluentEndDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_RinseEndDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_HGBEndDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_EOSEndDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE | CBCGPDateTimeCtrl::DTM_TIME24H | CBCGPDateTimeCtrl::DTM_CHECKBOX | CBCGPDateTimeCtrl::DTM_TIME | CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);
	m_BASEndDate.SetState(CBCGPDateTimeCtrl::DTM_DROPCALENDAR | CBCGPDateTimeCtrl::DTM_DATE, CBCGPDateTimeCtrl::DTM_SPIN | CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
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

	m_DiluentStartDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_RinseStartDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_HGBStartDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_EOSStartDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_BASStartDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_DiluentEndDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_RinseEndDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_HGBEndDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_EOSEndDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_BASEndDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);

	m_DiluentStartDate.SetDate(DiluentStartDate);
	m_RinseStartDate.SetDate(RinseStartDate);
	m_HGBStartDate.SetDate(HGBStartDate);
	m_EOSStartDate.SetDate(EOSStartDate);
	m_BASStartDate.SetDate(BASStartDate);
	m_DiluentEndDate.SetDate(DiluentEndDate);
	m_RinseEndDate.SetDate(RinseEndDate);
	m_HGBEndDate.SetDate(HGBEndDate);
	m_EOSEndDate.SetDate(EOSEndDate);
	m_BASEndDate.SetDate(BASEndDate);

	OnPaint();

}
void CReagentmanagement2View::UpdateReagentDate()
{
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
	
	m_DiluentStartDate.SetDate(DiluentStartDate);
	m_RinseStartDate.SetDate(RinseStartDate);
	m_HGBStartDate.SetDate(HGBStartDate);
	m_EOSStartDate.SetDate(EOSStartDate);
	m_BASStartDate.SetDate(BASStartDate);

	m_DiluentEndDate.SetDate(DiluentEndDate);
	m_RinseEndDate.SetDate(RinseEndDate);
	m_HGBEndDate.SetDate(HGBEndDate);
	m_EOSEndDate.SetDate(EOSEndDate);
	m_BASEndDate.SetDate(BASEndDate);
}

void CReagentmanagement2View::Paint_Diluent()
{
	CDC* pdc =m_Diluent_Status.GetDC();
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 绿笔
		CPen* pOldpen = pdc->SelectObject(&pen);
	//CRect rect; 
	//m_layoutBtn3.GetWindowRect(&rect);
	//m_layoutBtn3.ScreenToClient(&rect);
	//rect.OffsetRect(rect.left, rect.top); 
	pdc->MoveTo(2, 20);      //画一条横线，一条竖线
		pdc->LineTo(42, 20);
	pdc->MoveTo(22, 2);
	pdc->LineTo(22, 37);
	//pdc-> LineTo(rect.left, rect.bottom);
	//pdc-> LineTo(rect.left, rect.top);
	pdc->SelectObject(pOldpen);
	ReleaseDC(pdc);
}

void CReagentmanagement2View::Paint_Rinse()
{
	


}

void CReagentmanagement2View::Paint_HB5D_HGB()
{



}

void CReagentmanagement2View::Paint_HB5D_EOS()
{



}

void CReagentmanagement2View::Paint_HB5D_BAS()
{



}



void CReagentmanagement2View::OnChangeAllReagent()
{
	// TODO:  在此添加控件通知处理程序代码
	CChangeAllReagentView changeallreagentdlg;
	if (!changeallreagentdlg.DoModal())
	{
		MessageBox(L"生成更换所有试剂窗口失败");
		return;
	}
	UpdateReagentDate();
	return;
}


void CReagentmanagement2View::OnChangeReagent()
{
	// TODO:  在此添加控件通知处理程序代码
	CChangeReagentView changereagentdlg;
	if (!changereagentdlg.DoModal())
	{
		MessageBox(L"生成更换所有试剂窗口失败");
		return;
	}
	UpdateReagentDate();
	return;
}


BOOL CReagentmanagement2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此添加专用代码和/或调用基类
	//cs.style |= WS_CLIPCHILDREN;
	return CBCGPChartExampleView::PreCreateWindow(cs);

}



void CReagentmanagement2View::PaintLevel()
{
	CPaintDC dc(this); 
	
	CRect rect_diluent, rect_rinse, rect_hb5d_hgb, rect_hb5d_eos, rect_hb5d_bas;

	GetDlgItem(IDC_DILUENT)->GetWindowRect(rect_diluent);
	GetDlgItem(IDC_RINSE)->GetWindowRect(rect_rinse);
	GetDlgItem(IDC_HB5D_HGB)->GetWindowRect(rect_hb5d_hgb);
	GetDlgItem(IDC_HB5D_EOS)->GetWindowRect(rect_hb5d_eos);
	GetDlgItem(IDC_HB5D_BAS)->GetWindowRect(rect_hb5d_bas);

	ScreenToClient(&rect_diluent);
	ScreenToClient(&rect_rinse);
	ScreenToClient(&rect_hb5d_hgb);
	ScreenToClient(&rect_hb5d_eos);
	ScreenToClient(&rect_hb5d_bas);

	RECT rect;
	RECT rc;

	CDC memDC;// , memDC1, memDC2, memDC3, memDC4;
	memDC.CreateCompatibleDC(&dc);
	CImage image;
	image.Load(_T("res/bas.png"));

	HBITMAP hbitmap = image.Detach();// attach是把一个C++对象与一个WINDOWS对象关联，直到用detach则把关联去掉。  
	//image.Load(_T"");
	//HBITMAP
	CBitmap cBitmap;
	BITMAP bitmap;
	cBitmap.Attach(hbitmap);
	
	int print = systemcfg.regentfull.baslyse;
	print = (print*100 / BAS_Top_Level);
	CString str1;
	str1.Format(L"%d",print);
	CString str2 = str1 + "%";
	memDC.SelectObject(hbitmap);
	cBitmap.GetBitmap(&bitmap);
	print = (print + 5) / 10;
	dc.StretchBlt(rect_hb5d_bas.left + 25, rect_hb5d_bas.top - 10, 100, 200, &memDC, (10-print)*100, 0, 100, 200, SRCCOPY);
	dc.TextOut(rect_hb5d_bas.left + 60, rect_hb5d_bas.top + 90, str2);
	
	print = systemcfg.regentfull.eoslyse;
	print = (print * 100 / EOS_Top_Level);
	//print = (print * 32 / EOS_Top_Level);
	str1.Format(L"%d", print);
    str2 = str1 + "%";
	print = (print + 5) / 10;
	cBitmap.Detach();
	image.Load(_T("res/eos.png"));
	hbitmap = image.Detach();
	cBitmap.Attach(hbitmap);
	memDC.SelectObject(hbitmap);
	cBitmap.GetBitmap(&bitmap);
	dc.StretchBlt(rect_hb5d_eos.left + 25, rect_hb5d_eos.top - 10, 100, 200, &memDC, (10-print)*100, 0, 100, 200, SRCCOPY);
	dc.TextOut(rect_hb5d_eos.left + 60, rect_hb5d_eos.top + 90, str2);
	cBitmap.Detach();

	print = systemcfg.regentfull.hgblyse;
	print = (print * 100 / HGB_Top_Level);
	str1.Format(L"%d", print);
	str2 = str1 + "%";
	print = (print + 5) / 10;
	image.Load(_T("res/hgb.png"));
	hbitmap = image.Detach();
	cBitmap.Attach(hbitmap);
	memDC.SelectObject(hbitmap);
	cBitmap.GetBitmap(&bitmap);
	dc.StretchBlt(rect_hb5d_hgb.left + 25, rect_hb5d_hgb.top - 10, 100, 200, &memDC, 100*(10-print), 0, 100, 200, SRCCOPY);
	dc.TextOut(rect_hb5d_hgb.left + 60, rect_hb5d_hgb.top + 90, str2);
	cBitmap.Detach();

	print = systemcfg.regentfull.rinse;
	print = (print * 100 / Rinse_Top_Level);
	str1.Format(L"%d", print);
	str2 = str1 + "%";
	print = (print + 5) / 10;
	image.Load(_T("res/rinse.png"));
	hbitmap = image.Detach();
	cBitmap.Attach(hbitmap);
	memDC.SelectObject(hbitmap);
	cBitmap.GetBitmap(&bitmap);
	dc.StretchBlt(rect_rinse.left + 25, rect_rinse.top - 10, 100, 200, &memDC, 100*(10-print), 0, 100, 200, SRCCOPY);
	dc.TextOut(rect_rinse.left + 60, rect_rinse.top + 90, str2);
	cBitmap.Detach();

	print = systemcfg.regentfull.diluent;
	print = (print * 100 / Diluent_Top_Level);
	str1.Format(L"%d", print);
	str2 = str1 + "%";
	print = (print + 5) / 10;
	image.Load(_T("res/diluent.png"));
	hbitmap = image.Detach();
	cBitmap.Attach(hbitmap);
	memDC.SelectObject(hbitmap);
	cBitmap.GetBitmap(&bitmap);
	dc.StretchBlt(rect_diluent.left + 25, rect_diluent.top - 10, 100, 200, &memDC, 100*(10-print), 0, 100, 200, SRCCOPY);
	dc.TextOut(rect_diluent.left + 60, rect_diluent.top + 90, str2);

}
