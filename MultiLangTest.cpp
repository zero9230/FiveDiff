// MultiLangTest.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "MultiLangTest.h"
#include "afxdialogex.h"


// CMultiLangTest 对话框

IMPLEMENT_DYNAMIC(CMultiLangTest, CDialogEx)

CMultiLangTest::CMultiLangTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMultiLangTest::IDD, pParent)
{

}

CMultiLangTest::~CMultiLangTest()
{
}

void CMultiLangTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMultiLangTest, CDialogEx)
END_MESSAGE_MAP()


// CMultiLangTest 消息处理程序
