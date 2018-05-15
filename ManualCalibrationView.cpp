// ManualCalibrationView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "ManualCalibrationView.h"
#include "afxdialogex.h"
#include "FilesOperation.h"

// CManualCalibrationView 对话框

IMPLEMENT_DYNAMIC(CManualCalibrationView, CDialogEx)

CManualCalibrationView::CManualCalibrationView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualCalibrationView::IDD, pParent)
	, m_moderadio(0)
	, m_testmoderadio(0)
{
	TestMode = WHOLEDIFF;
}

CManualCalibrationView::~CManualCalibrationView()
{
}

void CManualCalibrationView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_MODE_RADIO, m_moderadio);
	DDX_Radio(pDX, IDC_TESTMODE_RADIO, m_testmoderadio);
}


BEGIN_MESSAGE_MAP(CManualCalibrationView, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MODE_RADIO, &CManualCalibrationView::OnModeRadio)
	ON_BN_CLICKED(IDC_MODE_RADIO2, &CManualCalibrationView::OnModeRadio2)
	ON_BN_CLICKED(IDC_TESTMODE_RADIO, &CManualCalibrationView::OnTestmodeRadio)
	ON_BN_CLICKED(IDC_TESTMODE_RADIO2, &CManualCalibrationView::OnTestmodeRadio2)
END_MESSAGE_MAP()
// CManualCalibrationView 消息处理程序


void CManualCalibrationView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //设置为绿色背景
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


BOOL CManualCalibrationView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ShowCalibration();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}



void CManualCalibrationView::OnModeRadio()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ShowCalibration();

}


void CManualCalibrationView::OnModeRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ShowCalibration();
}


void CManualCalibrationView::OnTestmodeRadio()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ShowCalibration();
}


void CManualCalibrationView::OnTestmodeRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ShowCalibration();
}


void CManualCalibrationView::ShowCalibration()
{
	CString calibrationtemp[4][5];

	if (m_moderadio == 0)
	{
		if (m_testmoderadio == 0)
		{
			TestMode = WHOLEDIFF;
		}
		else if (m_testmoderadio == 1)
		{
			TestMode = WHOLECBC;
		}
	}
	else if (m_moderadio == 1)
	{
		if (m_testmoderadio == 0)
		{
			TestMode = DILUENTDIFF;
		}
		else if (m_testmoderadio == 1)
		{
			TestMode = DILUENTCBC;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		calibrationtemp[TestMode][i].Format(L"%0.2f", systemcfg.calibration[TestMode][i]);
	}
	GetDlgItem(IDC_MANCALIB_WBCF)->SetWindowText(calibrationtemp[TestMode][0]);
	GetDlgItem(IDC_MANCALIB_RBCF)->SetWindowText(calibrationtemp[TestMode][1]);
	GetDlgItem(IDC_MANCALIB_HGBF)->SetWindowText(calibrationtemp[TestMode][2]);
	GetDlgItem(IDC_MANCALIB_MCVF)->SetWindowText(calibrationtemp[TestMode][3]);
	GetDlgItem(IDC_MANCALIB_PLTF)->SetWindowText(calibrationtemp[TestMode][4]);
}


void CManualCalibrationView::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CString calibrationtemp[4][5];
	GetDlgItem(IDC_MANCALIB_WBCF)->GetWindowText(calibrationtemp[TestMode][0]);
	GetDlgItem(IDC_MANCALIB_RBCF)->GetWindowText(calibrationtemp[TestMode][1]);
	GetDlgItem(IDC_MANCALIB_HGBF)->GetWindowText(calibrationtemp[TestMode][2]);
	GetDlgItem(IDC_MANCALIB_MCVF)->GetWindowText(calibrationtemp[TestMode][3]);
	GetDlgItem(IDC_MANCALIB_PLTF)->GetWindowText(calibrationtemp[TestMode][4]);
	for (int i = 0; i < 5; i++)
	{
		systemcfg.calibration[TestMode][i] = _wtoi(calibrationtemp[TestMode][i]);
	}
	WriteSystemcfgFile();
	CDialogEx::OnOK();
}


void CManualCalibrationView::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}
