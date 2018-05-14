// DoctorInfoView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "DoctorInfoView.h"
//#include "Includes_app.h"

// CDoctorInfoView
int ITEM_NUM = 0;
IMPLEMENT_DYNCREATE(CDoctorInfoView, CBCGPChartExampleView)

CDoctorInfoView::CDoctorInfoView()
: CBCGPChartExampleView(CDoctorInfoView::IDD)
{


}

CDoctorInfoView::~CDoctorInfoView()
{

}

void CDoctorInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DOCTOR_LIST, m_DoctorInfoList);
}

BEGIN_MESSAGE_MAP(CDoctorInfoView, CFormView)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MANUAL_ADD, &CDoctorInfoView::OnManualAdd)
	ON_COMMAND(ID_Delete, &CDoctorInfoView::OnDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_DOCTOR_LIST, &CDoctorInfoView::OnDblclkDoctorList)
	ON_BN_CLICKED(IDC_SAVE, &CDoctorInfoView::OnBnClickedSave)
END_MESSAGE_MAP()

// CDoctorInfoView 诊断

#ifdef _DEBUG
void CDoctorInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDoctorInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDoctorInfoView 消息处理程序
BOOL CDoctorInfoView::InitDoctorInfoForm()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_DoctorInfoList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_DoctorInfoList.SetExtendedStyle(m_DoctorInfoList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_DoctorInfoList.SetRowHeigt(20);


	// 为CRP列表视图控件添加四列
	m_DoctorInfoList.InsertColumn(0, _T("序号."), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_DoctorInfoList.InsertColumn(1, _T("NO."), LVCFMT_CENTER, rect.Width() / 5, 1);
	m_DoctorInfoList.InsertColumn(2, _T("医师"), LVCFMT_CENTER, rect.Width() / 5, 2);
	m_DoctorInfoList.InsertColumn(3, _T("备注"), LVCFMT_CENTER, rect.Width() * 2 / 5, 3);

	// 在CRP列表视图控件中插入列表项，并设置列表子项文本
	//	m_DoctorInfoList.InsertItem(0, _T("123456"));
	//	m_DoctorInfoList.SetItemText(0, 1, _T("NANCY"));
	//	m_DoctorInfoList.SetItemText(0, 2, _T("空"));

	int i = 0;
	CString select_name_sample = L"select * from doctordata order by doct_id asc";
	CString strTemp = "";
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;

	CString filename;
	filename.Format(L"appdata.accdb");
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return FALSE;
	ExeSql(m_pDB, m_pRs, select_name_sample);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空");
			return FALSE;
		}
		while (!m_pRs->adoEOF)
		{
			var = m_pRs->GetCollect("doct_row");
			if (var.vt != VT_NULL)
				strTemp = (LPCSTR)_bstr_t(var);
			m_DoctorInfoList.InsertItem(i, strTemp);
			var = m_pRs->GetCollect("doct_No");
			if (var.vt != VT_NULL)
				strTemp = (LPCSTR)_bstr_t(var);
			m_DoctorInfoList.SetItemText(i, 1, strTemp);
			var = m_pRs->GetCollect("doct_name");
			if (var.vt != VT_NULL)
				strTemp = (LPCSTR)_bstr_t(var);
			m_DoctorInfoList.SetItemText(i, 2, strTemp);
			var = m_pRs->GetCollect("doct_memo");
			if (var.vt != VT_NULL)
				strTemp = (LPCSTR)_bstr_t(var);
			m_DoctorInfoList.SetItemText(i, 3, strTemp);
			i++;
			ITEM_NUM++;
			m_pRs->MoveNext();
		}
		CloseDataBase(m_pDB, m_pRs);
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}

	return TRUE;
}

void CDoctorInfoView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	InitDoctorInfoForm();
}


BOOL CDoctorInfoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}

void CDoctorInfoView::OnManualAdd()
{
	CString select_name_sample = L"select * from doctordata";
	CString strTemp = "";
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;

	CString filename;
	filename.Format(L"appdata.accdb");
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	ExeSql(m_pDB, m_pRs, select_name_sample);
	try
	{
		CString doctor_num, doctor_name, doctor_memo;
		GetDlgItem(IDC_No)->GetWindowText(doctor_num);
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空");
			return;
		}
		while (!m_pRs->adoEOF)
		{
			var = m_pRs->GetCollect("doct_No");
			if (var.vt != VT_NULL)
				strTemp = (LPCSTR)_bstr_t(var);
			if (strTemp == doctor_num)
			{
				CString temp;
				temp = "The No." + doctor_num + " has been in access!";
				MessageBox(temp);
				return;
			}
			m_pRs->MoveNext();
		}

		GetDlgItem(IDC_Name)->GetWindowText(doctor_name);
		GetDlgItem(IDC_Memo)->GetWindowText(doctor_memo);
		if (doctor_num != "" && doctor_name != "")
		{
			CString doctor_row;
			doctor_row.Format(_T("%d"), ITEM_NUM + 1);
			CString insertdoctor = _T("INSERT INTO [doctordata] ([doct_No],[doct_name],[doct_memo],[doct_row]) VALUES('") + doctor_num + "' ,'" + doctor_name + "' ,'" + doctor_memo + "' ,'" + doctor_row + "');";
			ExeSql(m_pDB, m_pRs, insertdoctor);
			MessageBox(L"Doctor information has been appended successfully！");

			m_DoctorInfoList.InsertItem(ITEM_NUM, doctor_row);
			m_DoctorInfoList.SetItemText(ITEM_NUM, 1, doctor_num);
			m_DoctorInfoList.SetItemText(ITEM_NUM, 2, doctor_name);
			m_DoctorInfoList.SetItemText(ITEM_NUM, 3, doctor_memo);
			ITEM_NUM++;   //doctor_list's total
		}
		CString empty = "";
		GetDlgItem(IDC_No)->SetWindowText(empty);
		GetDlgItem(IDC_Name)->SetWindowText(empty);
		GetDlgItem(IDC_Memo)->SetWindowText(empty);
		CloseDataBase(m_pDB, m_pRs);
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}
}


void CDoctorInfoView::OnDelete()
{
	POSITION pos = m_DoctorInfoList.GetFirstSelectedItemPosition(); // getting current position of list
	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_DoctorInfoList.GetNextSelectedItem(pos);     // getting patients' number
		TRACE1("Item %d was selected!\n", nItem);
		CString doctor_num = m_DoctorInfoList.GetItemText(nItem, 1);
		CString doctor_name = m_DoctorInfoList.GetItemText(nItem, 2);
		CString doctor_memo = m_DoctorInfoList.GetItemText(nItem, 3);

		_ConnectionPtr m_pDB;
		_RecordsetPtr m_pRs;
		CString filename;
		filename.Format(L"appdata.accdb");
		if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
			return;
		CString DEL_Item = _T("delete from doctordata");
		ExeSql(m_pDB, m_pRs, DEL_Item);

		for (int i = nItem; i < ITEM_NUM - 1; i++)
		{
			//	CString doctor_row = m_DoctorInfoList.GetItemText(i+1, 0);
			CString doctor_num = m_DoctorInfoList.GetItemText(i + 1, 1);
			CString doctor_name = m_DoctorInfoList.GetItemText(i + 1, 2);
			CString doctor_memo = m_DoctorInfoList.GetItemText(i + 1, 3);
			//	m_DoctorInfoList.SetItemText(i, 0, doctor_row);
			m_DoctorInfoList.SetItemText(i, 1, doctor_num);
			m_DoctorInfoList.SetItemText(i, 2, doctor_name);
			m_DoctorInfoList.SetItemText(i, 3, doctor_memo);
		}
		m_DoctorInfoList.DeleteItem(ITEM_NUM - 1);
		//m_DoctorInfoList.SetItemText(ITEM_NUM, 0, doctor_row);
		ITEM_NUM -= 1;
		CString doctor_row;
		for (int i = 0; i < ITEM_NUM; i++)
		{
			doctor_row = m_DoctorInfoList.GetItemText(i, 0);
			doctor_num = m_DoctorInfoList.GetItemText(i, 1);
			doctor_name = m_DoctorInfoList.GetItemText(i, 2);
			doctor_memo = m_DoctorInfoList.GetItemText(i, 3);
			CString insertdoctor = _T("INSERT INTO [doctordata] ([doct_No],[doct_name],[doct_memo],[doct_row]) VALUES('") + doctor_num + "' ,'" + doctor_name + "' ,'" + doctor_memo + "' ,'" + doctor_row + "');";
			ExeSql(m_pDB, m_pRs, insertdoctor);

		}
		CloseDataBase(m_pDB, m_pRs);
	}
}


void CDoctorInfoView::OnDblclkDoctorList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	POSITION pos = m_DoctorInfoList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_DoctorInfoList.GetNextSelectedItem(pos);  // getting patients' number
		TRACE1("Item %d was selected!\n", nItem);
		CString doctor_num = m_DoctorInfoList.GetItemText(nItem, 1);
		CString doctor_name = m_DoctorInfoList.GetItemText(nItem, 2);
		CString doctor_memo = m_DoctorInfoList.GetItemText(nItem, 3);
		GetDlgItem(IDC_No)->SetWindowText(doctor_num);
		GetDlgItem(IDC_Name)->SetWindowText(doctor_name);
		GetDlgItem(IDC_Memo)->SetWindowText(doctor_memo);
	}
	*pResult = 0;
}


void CDoctorInfoView::OnBnClickedSave()
{
	CString doctor_num, doctor_name, doctor_memo;
	GetDlgItem(IDC_No)->GetWindowText(doctor_num);
	GetDlgItem(IDC_Name)->GetWindowText(doctor_name);
	GetDlgItem(IDC_Memo)->GetWindowText(doctor_memo);
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	CString filename;
	_variant_t var;
	CString strTemp;
	filename.Format(L"appdata.accdb");
	CString select_name_sample = L"select * from doctordata";
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	ExeSql(m_pDB, m_pRs, select_name_sample);
	if (!m_pRs->BOF){
		m_pRs->MoveFirst();
	}
	else
	{
		TRACE("表内数据为空");
		return;
	}
	while (!m_pRs->adoEOF)
	{
		var = m_pRs->GetCollect("doct_No");
		if (var.vt != VT_NULL)
			strTemp = (LPCSTR)_bstr_t(var);
		if (strTemp == doctor_num)
		{
			CString temp;
			temp = "The No." + doctor_num + " has been in access!";
			MessageBox(temp);
			return;
		}
		m_pRs->MoveNext();
	}

	POSITION pos = m_DoctorInfoList.GetFirstSelectedItemPosition(); // getting current position of list
	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_DoctorInfoList.GetNextSelectedItem(pos);
		nItem += 1;
		CString id;
		id.Format(_T("%d"), nItem);

		CString update_item = _T("update doctordata set [doct_No]='") + doctor_num + _T("',[doct_name]='") + doctor_name + _T("',[doct_memo]='") + doctor_memo
			+ _T("'where [doct_row] ='") + id + _T("'");
		ExeSql(m_pDB, m_pRs, update_item);
		CloseDataBase(m_pDB, m_pRs);
		m_DoctorInfoList.SetItemText(nItem - 1, 1, doctor_num);
		m_DoctorInfoList.SetItemText(nItem - 1, 2, doctor_name);
		m_DoctorInfoList.SetItemText(nItem - 1, 3, doctor_memo);
		MessageBox(L"Save successfully!");
	}
}
