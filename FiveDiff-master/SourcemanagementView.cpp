// SourcemanagementView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "SourcemanagementView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CSourcemanagementView 对话框

IMPLEMENT_DYNAMIC(CSourcemanagementView, CDialogEx)

CSourcemanagementView::CSourcemanagementView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSourcemanagementView::IDD, pParent)
{

}

CSourcemanagementView::~CSourcemanagementView()
{
}

void CSourcemanagementView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSourcemanagementView, CDialogEx)
END_MESSAGE_MAP()


// CSourcemanagementView 消息处理程序
