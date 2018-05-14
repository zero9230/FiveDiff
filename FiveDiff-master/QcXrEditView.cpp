// QcXrEditView.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "QcXrEditView.h"
#include "afxdialogex.h"
#include "QualityFileExit.h"


// CQcXrEditView 对话框

IMPLEMENT_DYNAMIC(CQcXrEditView, CDialogEx)

qc_edit_data_info qcXrEditData;
extern int rc;

CQcXrEditView::CQcXrEditView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQcXrEditView::IDD, pParent)
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

CQcXrEditView::~CQcXrEditView()
{
}

void CQcXrEditView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQcXrEditView, CDialogEx)
	ON_BN_CLICKED(IDC_QC_XR_EDIT_ENTER, &CQcXrEditView::OnBnClickedQcXrEditEnter)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CQcXrEditView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString item_temp;
	switch (Controltype)
	{
	case 0:
		item_temp.Format(L"L-J靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	case 1:
		item_temp.Format(L"X靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	case 2:
		item_temp.Format(L"X-R靶值编辑（文件 %02u）", Controlfile + 1);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_QC_XR_EDIT_STATIC0, item_temp);
	GetDlgItem(IDC_QC_XR_EDIT_STATIC0)->SetFont(&textfont);
	getQcXrFile(true);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


// CQcXrEditView 消息处理程序
void CQcXrEditView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}

HBRUSH CQcXrEditView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC0:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	default:
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

bool CQcXrEditView::getQcXrFile(bool loadData){
	CString filename;
	CString	qctypetemp;
	CString qcFileNumtemp;
	filename.Format(_T("appdata.accdb"));
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;
	CString strTemp;
	int tempRow;

	qctypetemp.Format(L"%d", Controltype);
	qcFileNumtemp.Format(L"%d", Controlfile);
	CString inital_target = _T("select * from qceditdata where qctype ='") + qctypetemp + "'and filenum ='" + qcFileNumtemp + "';";

	if (-1 == OpenDataBase(filename, m_pDB, m_pRs)){
		//MessageBox(L"Open Failure!");
		return false;
	}
	ExeSql(m_pDB, m_pRs, inital_target);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();

		}
		else
		{
			TRACE("\n表内数据为空!\n");
			//return FALSE;//由于此处需要将表格中的数据置为空，所以不可直接返回
		}
		tempRow = int(m_pRs->GetRecordCount());

		if (tempRow == 0)
		{
			QcXrFileExist = 0;
			tempXrNumber.Format(L"");
			tempXrDeadline.Format(L"");
		}
		else//将对应质控方式对应文件的数据读出来
		{
			if (loadData == true){
				QcXrFileExist = 1;
				var = m_pRs->GetCollect("number");
				if (var.vt != VT_NULL)
				{
					strTemp = m_pRs->GetCollect("number");
					tempXrNumber = (LPCSTR)_bstr_t(var);
					GetDlgItem(IDC_QC_XR_EDIT_NUMBER)->SetWindowText(tempXrNumber);
					//填入批号
				}

				var = m_pRs->GetCollect("deadline");
				if (var.vt != VT_NULL)
				{
					strTemp = m_pRs->GetCollect("deadline");
					tempXrDeadline = (LPCSTR)_bstr_t(var);
					GetDlgItem(IDC_QC_XR_EDIT_DEADLINE)->SetWindowText(tempXrDeadline);
					//填入批号
				}
			}
			else{
				QcXrFileExist = 1;
			}
		}
		//if (temprow == 0)//有效行数为0，则填入空值
		//{
		//	QcLjFileExist = 0;
		//	number = "";
		//	deadline = "";
		//	GetDlgItem(IDC_QC_XR_EDIT_NUMBER)->SetWindowText(number);
		//	GetDlgItem(IDC_QC_XR_EDIT_DEADLINE)->SetWindowText(deadline);
		//	for (int i = 0; i < 26; i++)
		//	{
		//		Qctarget[i] = "";
		//		TargetLimit[i] = "";
		//		m_ListList.SetItemText(i, 2, Qctarget[i]);
		//		m_ListList.SetItemText(i, 1, TargetLimit[i]);
		//		m_ListList.SetItemText(i, 3, TargetLimit[i]);
		//	}
		//}
		//else
		//{
		//	QcLjFileExist = 1;
		//	var = m_pRs->GetCollect("number");
		//	if (var.vt != VT_NULL)
		//	{
		//		strTemp = m_pRs->GetCollect("number");
		//		number = (LPCSTR)_bstr_t(var);
		//		GetDlgItem(IDC_QC_X_LIST_NUMBER)->SetWindowText(number);
		//		//填入批号
		//	}
		//	var = m_pRs->GetCollect("deadline");
		//	if (var.vt != VT_NULL)
		//	{
		//		int qctype = m_pRs->GetCollect("deadline");
		//		deadline.Format(L"%d", qctype);
		//		GetDlgItem(IDC_QC_X_LIST_DEADLINE)->SetWindowText(deadline);
		//		//填入截止日期
		//	}
		CloseDataBase(m_pDB, m_pRs);
		return true;
	}
	catch (_com_error &e)
	{
		TRACE("GetQCFile异常");
	}
	return false;
}

void CQcXrEditView::setQcXrEditData()
{
	qcXrEditData.qctype = Controltype + 48;
	qcXrEditData.filenum = Controlfile + 48;

	USES_CONVERSION;
	
	strcpy(qcXrEditData.Number, W2A(tempXrNumber.Trim()));
	strcpy(qcXrEditData.Deadline, W2A(tempXrDeadline.Trim()));
	//没有靶值和偏差限，有意义的只是上面几个数据
}

afx_msg void CQcXrEditView::OnBnClickedQcXrEditEnter()
{
	// TODO:  在此添加控件通知处理程序代码
	//CString tempXrNumber, tempXrDeadline;
	getQcXrFile(false);
	GetDlgItem(IDC_QC_XR_EDIT_NUMBER)->GetWindowText(tempXrNumber);
	GetDlgItem(IDC_QC_XR_EDIT_DEADLINE)->GetWindowText(tempXrDeadline);

	if (tempXrNumber.Trim()=="" || tempXrDeadline.Trim()=="")
	{
		
		MessageBox( L"信息不能为空!");
		
		return ;
	}
	
	setQcXrEditData();
	if (QcXrFileExist == 1)
	{//CreateQcXEditFileExistDlg(hDlg, &qcXrEditData, &rc);      //几种类型的提示框都一样，暂用XEdit中的
		CQualityFileExit m_QualityFileExitDlg;
		m_QualityFileExitDlg.setLjXXrEditData(qcXrEditData);
		m_QualityFileExitDlg.DoModal();
	}
		
	else//文件未使用
	{//rc = QcLjXXrEditFileAdd(&qcXrEditData);
		rc = QcLjXXrEditFileAdd(&qcXrEditData);

	}
		

	if (rc == 0)
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"保存成功", L"提示", MB_OK | MB_ICONINFORMATION);
		
	}
	else if (rc != -5)
	{
		if (systemcfg.language == CHINESE)
			MessageBox(L"保存失败", L"提示", MB_OK | MB_ICONINFORMATION);
	}

}







