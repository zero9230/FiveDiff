// BASOLandmarkView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "BASOLandmarkView.h"
#include "afxdialogex.h"
#include "FilesOperation.h"

int baso1,baso2,baso3;
// CBASOLandmarkView 对话框

IMPLEMENT_DYNAMIC(CBASOLandmarkView, CDialogEx)

CBASOLandmarkView::CBASOLandmarkView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBASOLandmarkView::IDD, pParent)
{
	VERIFY(m_Font.CreateFont(
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

CBASOLandmarkView::~CBASOLandmarkView()
{
}

void CBASOLandmarkView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBASOLandmarkView, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CBASOLandmarkView::OnBnClickedOk)
END_MESSAGE_MAP()


// CBASOLandmarkView 消息处理程序


HBRUSH CBASOLandmarkView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

//#3018
//
//#3019
//	return hbr;
//
//#3018
//
//#3019
//	return hbr;
//	// TODO:  在此更改 DC 的任何特性
//
//#3019
//	return hbr;
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_Font);
		pDC->SetBkColor(RGB(255, 255, 255));//文字背景色
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//控件背景色   
		return b;
	}
	//if (nCtlColor == CTLCOLOR_EDIT)
	//{
	//	pDC->SetTextColor(RGB(0, 0, 0));
	//pDC->SelectObject(&m_Font);
	//pDC->SetBkColor(RGB(255, 255, 255));//文字背景色
	//	HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));//控件背景色

	//}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CBASOLandmarkView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	/*@TG
#3073*/
	CString str;
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为白色背景
	dc.Rectangle(40, 20, rect.right - 40, rect.bottom - 30);
	Edit_BASO1=(CEdit *)GetDlgItem(IDC_THD_QC_BASO1);
	Edit_BASO1->SetFont(&m_Font);
	Edit_BASO2=(CEdit *)GetDlgItem(IDC_THD_QC_BASO2);
	Edit_BASO2->SetFont(&m_Font);
	Edit_BASO3=(CEdit *)GetDlgItem(IDC_THD_QC_BASO3);
	Edit_BASO3->SetFont(&m_Font);

	str.Format(L"%d",systemcfg.range.thresholds_qc[0]);
	GetDlgItem(IDC_THD_QC_BASO1)->SetWindowText((LPCTSTR)str);
	str.Format(L"%d",systemcfg.range.thresholds_qc[1]);
	GetDlgItem(IDC_THD_QC_BASO2)->SetWindowText((LPCTSTR)str);
	str.Format(L"%d",systemcfg.range.thresholds_qc[2]);
	GetDlgItem(IDC_THD_QC_BASO3)->SetWindowText((LPCTSTR)str);
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CBASOLandmarkView::OnBnClickedOk()
{
	baso1= GetDlgItemInt(IDC_THD_QC_BASO1);
	baso2= GetDlgItemInt(IDC_THD_QC_BASO2);
	baso3= GetDlgItemInt(IDC_THD_QC_BASO3);
	if(baso1>254||baso2>254||baso3>254)
	{
	if(baso1>254)
		MessageBox(L"BASO1数值超出范围！", L"ERROR", MB_OKCANCEL);
	if(baso2>254)
		MessageBox(L"BASO2数值超出范围！", L"ERROR", MB_OKCANCEL);
	if(baso3>254)
		MessageBox(L"BASO3数值超出范围！", L"ERROR", MB_OKCANCEL);
	}
	else
	{
		systemcfg.range.thresholds_qc[0] = baso1;
		systemcfg.range.thresholds_qc[1] = baso2;
		systemcfg.range.thresholds_qc[2] = baso3;
		WriteSystemcfgFile();
		MessageBox(L"设置成功，请返回！", L"OK", MB_OK);
	}
		
		
	
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}
