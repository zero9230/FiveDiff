// DoctorInfoView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "DoctorInfoView.h"
//#include "Includes_app.h"
#include <regex>
// CDoctorInfoView

IMPLEMENT_DYNCREATE(CDoctorInfoView, CBCGPChartExampleView)

static int reserve_index;

CDoctorInfoView::CDoctorInfoView()
: CBCGPChartExampleView(CDoctorInfoView::IDD)
{

	reserve_index = 0;

	ThisResult.numofrs.reserve(10);
	ThisResult.numofrs.clear();

	ThisResult.page_num = 10; //一页显示的id个数
	ThisResult.data_count = 0;  //数据库总id数

	int i = 0;
	CString select_name_sample = L"select * from doctordata order by doct_id asc";

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;

	CString filename;
	filename.Format(L"appdata.accdb");
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return ;
	ExeSql(m_pDB, m_pRs, select_name_sample);
	try
	{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空");
			return ;
		}
		while (!m_pRs->adoEOF)
		{
			i++;
			ThisResult.data_count++;
			m_pRs->MoveNext();
		}
		
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}
	CloseDataBase(m_pDB, m_pRs);
	if (ThisResult.data_count != 0)
		ThisResult.page_count = (ThisResult.data_count % ThisResult.page_num == 0 ? ThisResult.data_count / ThisResult.page_num : ThisResult.data_count / ThisResult.page_num + 1);
	else
		ThisResult.page_count = 1;

	if (reserve_index <= ThisResult.page_count)
		ThisResult.page_index = reserve_index;
	else
		ThisResult.page_index = reserve_index = ThisResult.page_count - 1;
	//InitDoctorInfoForm();
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
	ON_BN_CLICKED(IDC_DOCT_PAGE_HOME, &CDoctorInfoView::OnBnClickedDoctPageHome)
	ON_BN_CLICKED(IDC_DOCT_PAGE_FRONT, &CDoctorInfoView::OnBnClickedDoctPageFront)
	ON_BN_CLICKED(IDC_DOCT_PAGE_NEXT, &CDoctorInfoView::OnBnClickedDoctPageNext)
	ON_BN_CLICKED(IDC_DOCT_PAGE_TRAILER, &CDoctorInfoView::OnBnClickedDoctPageTrailer)
	ON_BN_CLICKED(IDC_DOCT_PAGE_JUMP, &CDoctorInfoView::OnBnClickedDoctPageJump)
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
BOOL CDoctorInfoView::InitDoctorInfoForm()//initialization
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

	ThisResult.numofrs.reserve(10);
	ThisResult.numofrs.clear();

	ThisResult.page_num = 10; //一页显示的id个数


	int i = 0;
	CString pagenum;
	pagenum.Format(_T("%d"), ThisResult.page_num);
	CString pageindex;
	pageindex.Format(_T("%d"), ThisResult.page_num*(ThisResult.page_index));
	CString select_name_sample;//排除第一页的情况
	select_name_sample = (ThisResult.page_index > 0) ? (_T("select top ") + pagenum + " * from doctordata where doct_id not in(select top " + pageindex + " doct_id from doctordata order by doct_id ) order by doct_id ") :
		(_T("select top ") + pagenum + " * from doctordata");

	CString strTemp = "";
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;

	CString filename;
	filename.Format(L"appdata.accdb");
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return FALSE;
	ExeSql(m_pDB, m_pRs, select_name_sample);
	m_DoctorInfoList.DeleteAllItems();
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
			var = m_pRs->GetCollect("doct_id");
			if (var.vt != VT_NULL)
				strTemp = (LPCSTR)_bstr_t(var);

			ThisResult.numofrs.push_back(strTemp);//存储id

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
			ThisResult.totalnums++;
			m_pRs->MoveNext();
		}
		
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}

	if (ThisResult.data_count != 0)
		ThisResult.page_count = (ThisResult.data_count % ThisResult.page_num == 0 ? ThisResult.data_count / ThisResult.page_num : ThisResult.data_count / ThisResult.page_num + 1);
	else
		ThisResult.page_count = 1;
	if (reserve_index <= ThisResult.page_count)
		ThisResult.page_index = reserve_index;
	else
		ThisResult.page_index = reserve_index = ThisResult.page_count - 1;

	CloseDataBase(m_pDB, m_pRs);


	CString count;
	count.Format(_T("%d"), ThisResult.page_count);
	count = "/" + count;
	SetDlgItemText(IDC_DOCT_PAGE_COUNT, count);

	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_DOCT_PAGE_SELECT, select);

	return TRUE;
}

BOOL CDoctorInfoView::UpdataDoctorInfoForm()
{
	CRect rect;


	// 获取编程语言列表视图控件的位置和大小   
	m_DoctorInfoList.GetClientRect(&rect);



	ThisResult.numofrs.reserve(10);
	ThisResult.numofrs.clear();

	ThisResult.page_num = 10; //一页显示的id个数


	int i = 0;

	CString pagenum;
	pagenum.Format(_T("%d"), ThisResult.page_num);
	CString pageindex;
	pageindex.Format(_T("%d"), ThisResult.page_num*(ThisResult.page_index));
	CString select_name_sample;//排除第一页的情况
	select_name_sample = (ThisResult.page_index > 0) ? (_T("select top ") + pagenum + " * from doctordata where doct_id not in(select top " + pageindex + " doct_id from doctordata order by doct_id ) order by doct_id ") :
		(_T("select top ") + pagenum + " * from doctordata");

	CString strTemp = "";
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;

	CString filename;
	filename.Format(L"appdata.accdb");
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return FALSE;
	ExeSql(m_pDB, m_pRs, select_name_sample);

	m_DoctorInfoList.DeleteAllItems();

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
			var = m_pRs->GetCollect("doct_id");
			if (var.vt != VT_NULL)
				strTemp = (LPCSTR)_bstr_t(var);

			ThisResult.numofrs.push_back(strTemp);//存储id

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
			ThisResult.totalnums++;
			m_pRs->MoveNext();
		}
		
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}
	CloseDataBase(m_pDB, m_pRs);
	if (ThisResult.data_count != 0)
		ThisResult.page_count = (ThisResult.data_count % ThisResult.page_num == 0 ? ThisResult.data_count / ThisResult.page_num : ThisResult.data_count / ThisResult.page_num + 1);
	else
		ThisResult.page_count = 1;
	if (reserve_index <= ThisResult.page_count)
		ThisResult.page_index = reserve_index;
	else
		ThisResult.page_index = reserve_index = ThisResult.page_count - 1;


	return TRUE;
}

void CDoctorInfoView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();
	InitDoctorInfoForm();
	// TODO:  在此添加专用代码和/或调用基类

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
			doctor_row.Format(_T("%d"), ThisResult.data_count + 1);
			CString insertdoctor = _T("INSERT INTO [doctordata] ([doct_No],[doct_name],[doct_memo],[doct_row]) VALUES('") + doctor_num + "' ,'" + doctor_name + "' ,'" + doctor_memo + "' ,'" + doctor_row + "');";
			ExeSql(m_pDB, m_pRs, insertdoctor);
			MessageBox(L"Doctor information has been appended successfully！");

			/*m_DoctorInfoList.InsertItem(ITEM_NUM, doctor_row);
			m_DoctorInfoList.SetItemText(ITEM_NUM, 1, doctor_num);
			m_DoctorInfoList.SetItemText(ITEM_NUM, 2, doctor_name);
			m_DoctorInfoList.SetItemText(ITEM_NUM, 3, doctor_memo);*/
			
			ThisResult.data_count++;   //doctor_list's total
			//更新数据页面信息
			if (ThisResult.data_count != 0)
				ThisResult.page_count = (ThisResult.data_count % ThisResult.page_num == 0 ? ThisResult.data_count / ThisResult.page_num : ThisResult.data_count / ThisResult.page_num + 1);

			if (reserve_index <= ThisResult.page_count)
				ThisResult.page_index = reserve_index;
			else
				ThisResult.page_index = reserve_index = ThisResult.page_count - 1;

	

		}
		CString empty = "";
		GetDlgItem(IDC_No)->SetWindowText(empty);
		GetDlgItem(IDC_Name)->SetWindowText(empty);
		GetDlgItem(IDC_Memo)->SetWindowText(empty);
		
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}
	CloseDataBase(m_pDB, m_pRs);
	UpdataDoctorInfoForm();

	CString count;
	count.Format(_T("%d"), ThisResult.page_count);
	count = "/" + count;
	SetDlgItemText(IDC_DOCT_PAGE_COUNT, count);

	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_DOCT_PAGE_SELECT, select);
}


void CDoctorInfoView::OnDelete()//delete one selected info
{
	POSITION pos = m_DoctorInfoList.GetFirstSelectedItemPosition(); // getting current position of list
	if (pos == NULL)
		TRACE("No items were selected!\n");
	else//Tips:when we delete one info, there must be a item selected. So the data_count must be zero.
	{
		int nItem = m_DoctorInfoList.GetNextSelectedItem(pos);  

		TRACE1("Item %d was selected!\n", nItem);
		CString doctor_num = m_DoctorInfoList.GetItemText(nItem, 1);
		CString doctor_name = m_DoctorInfoList.GetItemText(nItem, 2);
		CString doctor_memo = m_DoctorInfoList.GetItemText(nItem, 3);
		CString doctor_id = ThisResult.numofrs[nItem];
		//CString id;
		//id.Format(_T("%d"), nItem);
		_ConnectionPtr m_pDB;
		_RecordsetPtr m_pRs;
		CString filename;
		filename.Format(L"appdata.accdb");
		if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
			return;

		//请先清除相关病人
		CString pati_select = _T("select * from patientdata where doctor = ") + doctor_id;
		ExeSql(m_pDB, m_pRs, pati_select);
		try
		{
			if (!m_pRs->BOF)	{
				MessageBox(L"请先清除相关病人");
				return;
			}
		}
		catch (_com_error &e)
		{
			TRACE("Delete异常");
		}

		CString DEL_Item = _T("delete from doctordata where doct_id = ") + doctor_id;
		ExeSql(m_pDB, m_pRs, DEL_Item);
		CloseDataBase(m_pDB, m_pRs);

		//the data has been delete,now we should change the display info
		//the easy way is to use updateinfo.
		ThisResult.data_count -= 1;

		if (ThisResult.data_count != 0)
			ThisResult.page_count = (ThisResult.data_count % ThisResult.page_num == 0 ? ThisResult.data_count / ThisResult.page_num : ThisResult.data_count / ThisResult.page_num + 1);
		else
			ThisResult.page_count = 1;
		if (reserve_index <= ThisResult.page_count)
			ThisResult.page_index = reserve_index;
		else
			ThisResult.page_index = reserve_index = ThisResult.page_count - 1;
		
		UpdataDoctorInfoForm();

		CString count;
		count.Format(_T("%d"), ThisResult.page_count);
		count = "/" + count;
		SetDlgItemText(IDC_DOCT_PAGE_COUNT, count);

		CString select;
		select.Format(_T("%d"), ThisResult.page_index + 1);
		SetDlgItemText(IDC_DOCT_PAGE_SELECT, select);
		//没懂？ 为什么原先程序是全部删除再重新插入？

		/*
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
		*/
		
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


void CDoctorInfoView::OnBnClickedSave()//update one info
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
	CT2CA tempPassword(doctor_num);
	std::string strPassword(tempPassword);
	std::regex regPattern("[0-9]*"); // <span style = "white-space:pre">	< / span>// at least 6 charaters of digit or letter
	BOOL bValid = std::regex_match(strPassword, regPattern);
	if (!bValid)
	{
		MessageBox(L"Please enter into the number!");
		return ;
	}
	POSITION pos = m_DoctorInfoList.GetFirstSelectedItemPosition(); // getting current position of list
	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_DoctorInfoList.GetNextSelectedItem(pos);
		CString doct_id;
		doct_id = ThisResult.numofrs[nItem];
		filename.Format(L"appdata.accdb");

		if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
			return;
		CString update_item = _T("update doctordata set [doct_No]='") + doctor_num + _T("',[doct_name]='") + doctor_name + _T("',[doct_memo]='") + doctor_memo
			+ _T("'where [doct_id] = ") + doct_id + _T(" ");
		ExeSql(m_pDB, m_pRs, update_item);
		CloseDataBase(m_pDB, m_pRs);


		

		UpdataDoctorInfoForm();

		MessageBox(L"Save successfully!");
	}
}


void CDoctorInfoView::OnBnClickedDoctPageHome()
{
	// TODO:  在此添加控件通知处理程序代码
	reserve_index = 0;
	ThisResult.page_index = reserve_index;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	UpdataDoctorInfoForm();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_DOCT_PAGE_SELECT, select);
}


void CDoctorInfoView::OnBnClickedDoctPageFront()
{
	// TODO:  在此添加控件通知处理程序代码
	if (reserve_index > 0)
		reserve_index--;
	ThisResult.page_index = reserve_index;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	UpdataDoctorInfoForm();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_DOCT_PAGE_SELECT, select);
}


void CDoctorInfoView::OnBnClickedDoctPageNext()
{
	// TODO:  在此添加控件通知处理程序代码
	if (reserve_index < ThisResult.page_count - 1)
		reserve_index++;
	ThisResult.page_index = reserve_index;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	UpdataDoctorInfoForm();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_DOCT_PAGE_SELECT, select);
}


void CDoctorInfoView::OnBnClickedDoctPageTrailer()
{
	// TODO:  在此添加控件通知处理程序代码
	reserve_index = ThisResult.page_count - 1;
	ThisResult.page_index = reserve_index;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	UpdataDoctorInfoForm();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_DOCT_PAGE_SELECT, select);
}


void CDoctorInfoView::OnBnClickedDoctPageJump()
{
	// TODO:  在此添加控件通知处理程序代码
	int page = GetDlgItemInt(IDC_DOCT_PAGE_SELECT);
	if (page > 0 && page <= ThisResult.page_count)
		reserve_index = page - 1;
	ThisResult.page_index = reserve_index;
	ThisResult.numofrs.reserve(20);
	ThisResult.numofrs.clear();
	UpdataDoctorInfoForm();
	CString select;
	select.Format(_T("%d"), ThisResult.page_index + 1);
	SetDlgItemText(IDC_DOCT_PAGE_SELECT, select);
}
