// CorrectParaSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "CorrectParaSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"
#include "FilesOperation.h"
// CCorrectParaSetView 对话框

IMPLEMENT_DYNAMIC(CCorrectParaSetView, CDialogEx)

CCorrectParaSetView::CCorrectParaSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCorrectParaSetView::IDD, pParent)
	, m_modeRadio(0)
	, m_testmodeRadio(0)
	, TestMode(0)
{

}

CCorrectParaSetView::~CCorrectParaSetView()
{
}

void CCorrectParaSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_MODIFYSET_WHOLEBLOOD, m_modeRadio);
	DDX_Radio(pDX, IDC_MODIFYSET_CBC5DIFF, m_testmodeRadio);
}


BEGIN_MESSAGE_MAP(CCorrectParaSetView, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MODIFYSET_WHOLEBLOOD, &CCorrectParaSetView::OnBnClickedModifysetWholeblood)
	ON_BN_CLICKED(IDC_MODIFYSET_DILUENT, &CCorrectParaSetView::OnBnClickedModifysetDiluent)
	ON_BN_CLICKED(IDC_MODIFYSET_CBC5DIFF, &CCorrectParaSetView::OnBnClickedModifysetCbc5diff)
	ON_BN_CLICKED(IDC_MODIFYSET_CBC, &CCorrectParaSetView::OnBnClickedModifysetCbc)
	ON_BN_CLICKED(IDC_SET_SAVE, &CCorrectParaSetView::OnParaSetSave)
END_MESSAGE_MAP()


// CCorrectParaSetView 消息处理程序

BOOL CCorrectParaSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ShowModifyPara();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CCorrectParaSetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
	dc.FillPath();

	CDialogEx::OnPaint();
}

void CCorrectParaSetView::ShowModifyPara()
{

	char		buffer[6] = { 0 };
	CString     buffer_a[4][11];
	CString		buffer_b[4][11];
	CString		buffer_c[4][11];
	UpdateData(true);
	if (m_modeRadio == 0)
	{
		if (m_testmodeRadio ==0)
		{
			TestMode = WHOLEDIFF;
		}
		else if (m_testmodeRadio ==1)
		{
			TestMode = WHOLECBC;
		}
	}
	else if (m_modeRadio==1)
	{
		if (m_testmodeRadio == 0)
		{
			TestMode = DILUENTDIFF;
		}
		else if (m_testmodeRadio == 1)
		{
			TestMode = DILUENTCBC;
		}
	}

	ReadSystemcfgFile();
	for (int i = 0; i < 11; i++)
	{
		buffer_a[TestMode][i].Format(L"%.3f", systemcfg.modify[TestMode].a[i]);
		buffer_b[TestMode][i].Format(L"%.2f", systemcfg.modify[TestMode].b[i]);
		buffer_c[TestMode][i].Format(L"%.2f", systemcfg.modify[TestMode].c[i]);
	}

	GetDlgItem(IDC_MODIFYSET_WBCF_A)->SetWindowText(buffer_a[TestMode][0]);
	GetDlgItem(IDC_MODIFYSET_WBCF_B)->SetWindowText(buffer_b[TestMode][0]);
	GetDlgItem(IDC_MODIFYSET_WBCF_C)->SetWindowText(buffer_c[TestMode][0]);

	GetDlgItem(IDC_MODIFYSET_RBCF_A)->SetWindowText(buffer_a[TestMode][1]);
	GetDlgItem(IDC_MODIFYSET_RBCF_B)->SetWindowText(buffer_b[TestMode][1]);
	GetDlgItem(IDC_MODIFYSET_RBCF_C)->SetWindowText(buffer_c[TestMode][1]);

	GetDlgItem(IDC_MODIFYSET_HGBF_A)->SetWindowText(buffer_a[TestMode][2]);
	GetDlgItem(IDC_MODIFYSET_HGBF_B)->SetWindowText(buffer_b[TestMode][2]);
	GetDlgItem(IDC_MODIFYSET_HGBF_C)->SetWindowText(buffer_c[TestMode][2]);

	GetDlgItem(IDC_MODIFYSET_MCVF_A)->SetWindowText(buffer_a[TestMode][3]);
	GetDlgItem(IDC_MODIFYSET_MCVF_B)->SetWindowText(buffer_b[TestMode][3]);
	GetDlgItem(IDC_MODIFYSET_MCVF_C)->SetWindowText(buffer_c[TestMode][3]);

	GetDlgItem(IDC_MODIFYSET_RDWCVF_A)->SetWindowText(buffer_a[TestMode][4]);
	GetDlgItem(IDC_MODIFYSET_RDWCVF_B)->SetWindowText(buffer_b[TestMode][4]);
	GetDlgItem(IDC_MODIFYSET_RDWCVF_C)->SetWindowText(buffer_c[TestMode][4]);

	GetDlgItem(IDC_MODIFYSET_RDWSDF_A)->SetWindowText(buffer_a[TestMode][5]);
	GetDlgItem(IDC_MODIFYSET_RDWSDF_B)->SetWindowText(buffer_b[TestMode][5]);
	GetDlgItem(IDC_MODIFYSET_RDWSDF_C)->SetWindowText(buffer_c[TestMode][5]);

	GetDlgItem(IDC_MODIFYSET_PLTF_A)->SetWindowText(buffer_a[TestMode][6]);
	GetDlgItem(IDC_MODIFYSET_PLTF_B)->SetWindowText(buffer_b[TestMode][6]);
	GetDlgItem(IDC_MODIFYSET_PLTF_C)->SetWindowText(buffer_c[TestMode][6]);

	GetDlgItem(IDC_MODIFYSET_MPVF_A)->SetWindowText(buffer_a[TestMode][7]);
	GetDlgItem(IDC_MODIFYSET_MPVF_B)->SetWindowText(buffer_b[TestMode][7]);
	GetDlgItem(IDC_MODIFYSET_MPVF_C)->SetWindowText(buffer_c[TestMode][7]);

	GetDlgItem(IDC_MODIFYSET_PDWF_A)->SetWindowText(buffer_a[TestMode][8]);
	GetDlgItem(IDC_MODIFYSET_PDWF_B)->SetWindowText(buffer_b[TestMode][8]);
	GetDlgItem(IDC_MODIFYSET_PDWF_C)->SetWindowText(buffer_c[TestMode][8]);

	GetDlgItem(IDC_MODIFYSET_PCTF_A)->SetWindowText(buffer_a[TestMode][9]);
	GetDlgItem(IDC_MODIFYSET_PCTF_B)->SetWindowText(buffer_b[TestMode][9]);
	GetDlgItem(IDC_MODIFYSET_PCTF_C)->SetWindowText(buffer_c[TestMode][9]);

	GetDlgItem(IDC_MODIFYSET_PLCRF_A)->SetWindowText(buffer_a[TestMode][10]);
	GetDlgItem(IDC_MODIFYSET_PLCRF_B)->SetWindowText(buffer_b[TestMode][10]);
	GetDlgItem(IDC_MODIFYSET_PLCRF_C)->SetWindowText(buffer_c[TestMode][10]);
}

void CCorrectParaSetView::OnBnClickedModifysetWholeblood()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ShowModifyPara();
}


void CCorrectParaSetView::OnBnClickedModifysetDiluent()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ShowModifyPara();
}


void CCorrectParaSetView::OnBnClickedModifysetCbc5diff()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ShowModifyPara();
}


void CCorrectParaSetView::OnBnClickedModifysetCbc()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ShowModifyPara();
}

void CCorrectParaSetView::OnParaSetSave()
{
	// TODO:  在此添加控件通知处理程序代码
	CString temp_a[4][11];
	CString temp_b[4][11];
	CString temp_c[4][11];
	//A
	GetDlgItem(IDC_MODIFYSET_WBCF_A)->GetWindowText(temp_a[TestMode][0]);
	GetDlgItem(IDC_MODIFYSET_RBCF_A)->GetWindowText(temp_a[TestMode][1]);
	GetDlgItem(IDC_MODIFYSET_HGBF_A)->GetWindowText(temp_a[TestMode][2]);
	GetDlgItem(IDC_MODIFYSET_MCVF_A)->GetWindowText(temp_a[TestMode][3]);
	GetDlgItem(IDC_MODIFYSET_RDWCVF_A)->GetWindowText(temp_a[TestMode][4]);
	GetDlgItem(IDC_MODIFYSET_RDWSDF_A)->GetWindowText(temp_a[TestMode][5]);
	GetDlgItem(IDC_MODIFYSET_PLTF_A)->GetWindowText(temp_a[TestMode][6]);
	GetDlgItem(IDC_MODIFYSET_MPVF_A)->GetWindowText(temp_a[TestMode][7]);
	GetDlgItem(IDC_MODIFYSET_PDWF_A)->GetWindowText(temp_a[TestMode][8]);
	GetDlgItem(IDC_MODIFYSET_PCTF_A)->GetWindowText(temp_a[TestMode][9]);
	GetDlgItem(IDC_MODIFYSET_PLCRF_A)->GetWindowText(temp_a[TestMode][10]);
	//B
	GetDlgItem(IDC_MODIFYSET_WBCF_B)->GetWindowText(temp_b[TestMode][0]);
	GetDlgItem(IDC_MODIFYSET_RBCF_B)->GetWindowText(temp_b[TestMode][1]);
	GetDlgItem(IDC_MODIFYSET_HGBF_B)->GetWindowText(temp_b[TestMode][2]);
	GetDlgItem(IDC_MODIFYSET_MCVF_B)->GetWindowText(temp_b[TestMode][3]);
	GetDlgItem(IDC_MODIFYSET_RDWCVF_B)->GetWindowText(temp_b[TestMode][4]);
	GetDlgItem(IDC_MODIFYSET_RDWSDF_B)->GetWindowText(temp_b[TestMode][5]);
	GetDlgItem(IDC_MODIFYSET_PLTF_B)->GetWindowText(temp_b[TestMode][6]);
	GetDlgItem(IDC_MODIFYSET_MPVF_B)->GetWindowText(temp_b[TestMode][7]);
	GetDlgItem(IDC_MODIFYSET_PDWF_B)->GetWindowText(temp_b[TestMode][8]);
	GetDlgItem(IDC_MODIFYSET_PCTF_B)->GetWindowText(temp_b[TestMode][9]);
	GetDlgItem(IDC_MODIFYSET_PLCRF_B)->GetWindowText(temp_b[TestMode][10]);
	//C
	GetDlgItem(IDC_MODIFYSET_WBCF_C)->GetWindowText(temp_c[TestMode][0]);
	GetDlgItem(IDC_MODIFYSET_RBCF_C)->GetWindowText(temp_c[TestMode][1]);
	GetDlgItem(IDC_MODIFYSET_HGBF_C)->GetWindowText(temp_c[TestMode][2]);
	GetDlgItem(IDC_MODIFYSET_MCVF_C)->GetWindowText(temp_c[TestMode][3]);
	GetDlgItem(IDC_MODIFYSET_RDWCVF_C)->GetWindowText(temp_c[TestMode][4]);
	GetDlgItem(IDC_MODIFYSET_RDWSDF_C)->GetWindowText(temp_c[TestMode][5]);
	GetDlgItem(IDC_MODIFYSET_PLTF_C)->GetWindowText(temp_c[TestMode][6]);
	GetDlgItem(IDC_MODIFYSET_MPVF_C)->GetWindowText(temp_c[TestMode][7]);
	GetDlgItem(IDC_MODIFYSET_PDWF_C)->GetWindowText(temp_c[TestMode][8]);
	GetDlgItem(IDC_MODIFYSET_PCTF_C)->GetWindowText(temp_c[TestMode][9]);
	GetDlgItem(IDC_MODIFYSET_PLCRF_C)->GetWindowText(temp_c[TestMode][10]);

	for (int i = 0; i < 11; i++)
	{
		systemcfg.modify[TestMode].a[i] = _wtof(temp_a[TestMode][i]);
		systemcfg.modify[TestMode].b[i] = _wtof(temp_b[TestMode][i]);
		systemcfg.modify[TestMode].c[i] = _wtof(temp_c[TestMode][i]);
	}
	WriteSystemcfgFile();
	MessageBox(	L"保存成功");
}

