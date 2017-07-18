// BackupView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "BackupView.h"
#include "afxdialogex.h"

// CBackupView 对话框

IMPLEMENT_DYNAMIC(CBackupView, CDialogEx)

CBackupView::CBackupView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBackupView::IDD, pParent)
{

}

CBackupView::~CBackupView()
{
}

void CBackupView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BACKUP_TAB, m_backuptab);
	DDX_Control(pDX, IDC_BACKUP_INSTALL, m_backupinstall);
	DDX_Control(pDX, IDC_SHUTDOWN, m_shutup);
	DDX_Control(pDX, IDC_RESOURCE_MANAGER, m_resourceManage);
	DDX_Control(pDX, IDC_MANUAL_BACKUP, m_manualbackup);
	DDX_Control(pDX, IDC_SAVESET, m_saveset);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
}


BEGIN_MESSAGE_MAP(CBackupView, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBackupView 消息处理程序


BOOL CBackupView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	updatetabview();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CBackupView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CBackupView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//updatetabview();
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();
}

void CBackupView::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CDialogEx::OnOK();
}

void CBackupView::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码

}

void CBackupView::updatetabview()
{
	CRect rectTab;
	GetDlgItem(IDC_BACKUP_TAB)->GetWindowRect(&rectTab);
	ScreenToClient(&rectTab);

	m_backuptab.Create(CBCGPTabWnd::STYLE_3D, rectTab, this, 1, CBCGPTabWnd::LOCATION_TOP);

	// m_Tasksheetpage=new CWorkstationTasksheet();
	//m_Analysispage=new CWorkstationAnalysis();
	//m_Resultpage=new CWorkstationResult();

	CSetPage.Create(IDD_BACKUP_SET, &m_backuptab);
	CRestorePage.Create(IDD_BACKUP_RESTORE, &m_backuptab);

	m_backuptab.AddTab(&CSetPage, L"软件备份设置", 0);
	m_backuptab.AddTab(&CRestorePage, L"软件恢复", 1);

	CRect rc;
	m_backuptab.GetClientRect(rc);
	m_backuptab.SetResizeMode(CBCGPTabWnd::RESIZE_VERT);
	rc.top += 27;
	rc.bottom -= 5;
	rc.left += 5;
	rc.right -= 10;
	CSetPage.MoveWindow(&rc);
	CRestorePage.MoveWindow(&rc);
}