// TypeRangeCopy.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "TypeRangeCopy.h"
#include "afxdialogex.h"
#include "RangeSetView.h"
#include "FilesOperation.h"
// CTypeRangeCopy 对话框

IMPLEMENT_DYNAMIC(CTypeRangeCopy, CDialogEx)

CTypeRangeCopy::CTypeRangeCopy(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTypeRangeCopy::IDD, pParent)
{
	pasteName[0] = "通用";
	pasteName[1] = "成男";
	pasteName[2] = "成女";
	pasteName[3] = "儿童";
	pasteName[4] = "婴儿";
	pasteName[5] = "老人";
}

CTypeRangeCopy::~CTypeRangeCopy()
{
}

void CTypeRangeCopy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COPY_COMBO, m_copyCombo);
}


BEGIN_MESSAGE_MAP(CTypeRangeCopy, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTypeRangeCopy 消息处理程序


BOOL CTypeRangeCopy::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_PASTE_EDIT)->SetWindowTextW(pasteName[ListFocusItem]);
	m_copyCombo.AddString(L"通用");
	m_copyCombo.AddString(L"成男");
	m_copyCombo.AddString(L"成女");
	m_copyCombo.AddString(L"儿童");
	m_copyCombo.AddString(L"婴儿");
	m_copyCombo.AddString(L"老人");
	m_copyCombo.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CTypeRangeCopy::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CTypeRangeCopy::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	int nItem;
	nItem = m_copyCombo.GetCurSel();
	for (int i = 0; i < 56; i++)
	{
		systemcfg.range.normal[nItem][i] = systemcfg.range.normal[ListFocusItem][i];
	}
	WriteSystemcfgFile();
	CDialogEx::OnOK();
}

void CTypeRangeCopy::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}
