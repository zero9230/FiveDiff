// QualityFileExit.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QualityFileExit.h"
#include "afxdialogex.h"
#include "QualityTargetValueView.h"

// CQualityFileExit 对话框
extern qc_edit_data_info qcLjEditData;
IMPLEMENT_DYNAMIC(CQualityFileExit, CDialogEx)

int rc;

CQualityFileExit::CQualityFileExit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQualityFileExit::IDD, pParent)
{
	VERIFY(textfont.CreateFont(
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

CQualityFileExit::~CQualityFileExit()
{
}

void CQualityFileExit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQualityFileExit, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CQualityFileExit 消息处理程序

void CQualityFileExit::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


BOOL CQualityFileExit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CWnd *cWnd = GetDlgItem(IDC_STATIC);
	cWnd->SetFont(&textfont);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CQualityFileExit::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	QcLjXXrEditFileExistReset(&qcLjEditData);
	rc = 0;
	CDialogEx::OnOK();
}

void CQualityFileExit::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	rc = -5;
	CDialogEx::OnClose();
}
