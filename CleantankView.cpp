// CleantankView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "CleantankView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CCleantankView 对话框

IMPLEMENT_DYNAMIC(CCleantankView, CDialogEx)

CCleantankView::CCleantankView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCleantankView::IDD, pParent)
{

}

CCleantankView::~CCleantankView()
{
}

void CCleantankView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCleantankView, CDialogEx)
END_MESSAGE_MAP()


// CCleantankView 消息处理程序
