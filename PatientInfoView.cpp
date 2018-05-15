// PatientInfoView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "PatientInfoView.h"
//#include "Includes_app.h"

// CPatientInfoView

IMPLEMENT_DYNCREATE(CPatientInfoView, CBCGPChartExampleView)

CPatientInfoView::CPatientInfoView()
: CBCGPChartExampleView(CPatientInfoView::IDD)
{

}

CPatientInfoView::~CPatientInfoView()
{
}

void CPatientInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST3, m_patientInfoList);
	DDX_Control(pDX, IDC_PATIENTINFO_LIST, m_patientInfoList);
}

BEGIN_MESSAGE_MAP(CPatientInfoView, CFormView)
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_DBLCLK, IDC_PATIENTINFO_LIST, &CPatientInfoView::OnNMDblclkPatientinfoList)
	ON_BN_CLICKED(IDC_SAVE, &CPatientInfoView::OnClickedSave)
	ON_COMMAND(ID_MANUAL_ADD, &CPatientInfoView::OnManualAdd)
	ON_COMMAND(ID_Delete, &CPatientInfoView::OnDelete)
END_MESSAGE_MAP()


// CPatientInfoView 诊断

#ifdef _DEBUG
void CPatientInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPatientInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPatientInfoView 消息处理程序


BOOL CPatientInfoView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}


void CPatientInfoView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	InitPaitientInfoForm();
}



BOOL CPatientInfoView::InitPaitientInfoForm()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_patientInfoList.GetClientRect(&rect);

	int i = 0;
	CString select_name_sample = L"select * from patientdata ";
	CString strNum = "";
	//CString strtemp = "20";
	CString strSex[3] = { "男", "女", "" };

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	_variant_t var;
	//is_search = false;
	CString filename;
	filename.Format(L"appdata.accdb");


	// 为列表视图控件添加全行选中和栅格风格   
	m_patientInfoList.SetExtendedStyle(m_patientInfoList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_patientInfoList.SetRowHeigt(20);


	// 为CRP列表视图控件添加四列
	m_patientInfoList.InsertColumn(0, _T("患者ID号"), LVCFMT_CENTER, rect.Width() / 7, 0);
	m_patientInfoList.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, rect.Width() / 7, 1);
	
	m_patientInfoList.InsertColumn(2, _T("性别"), LVCFMT_CENTER, rect.Width() / 8, 2);
	m_patientInfoList.InsertColumn(3, _T("条码"), LVCFMT_CENTER, rect.Width() / 7, 3);
	m_patientInfoList.InsertColumn(4, _T("年龄"), LVCFMT_CENTER, rect.Width() / 7, 4);
	m_patientInfoList.InsertColumn(5, _T("病区"), LVCFMT_CENTER, rect.Width() / 7, 5);

	m_patientInfoList.InsertColumn(6, _T("医师"), LVCFMT_CENTER, rect.Width() / 7, 6);
	//m_patientInfoList.InsertColumn(7, _T("患者评语"), LVCFMT_CENTER, rect.Width() / 8, 7);

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
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
				strNum = (LPCSTR)_bstr_t(var);
			ThisResult2.numofrs[i] = strNum;
			//strNum = strtemp + strNum;
			m_patientInfoList.InsertItem(i, _T(""));
			m_patientInfoList.SetItemText(i, 0, strNum);
			
			var = m_pRs->GetCollect("name");
			CString nametemp;
			if (var.vt != VT_NULL)
			{
				nametemp = (LPCSTR)_bstr_t(var);
			}
			m_patientInfoList.SetItemText(i, 1, nametemp);
			
			var = m_pRs->GetCollect("sex");
			CString sextemp;
			if (var.vt != VT_NULL)
			{
				sextemp = (LPCSTR)_bstr_t(var);
				sextemp = strSex[_ttoi(sextemp)];
			}
			m_patientInfoList.SetItemText(i, 2, sextemp);

			var = m_pRs->GetCollect("code");
			CString codetemp;
			if (var.vt != VT_NULL)
			{
				codetemp = (LPCSTR)_bstr_t(var);
			}
			m_patientInfoList.SetItemText(i, 3, codetemp);


			var = m_pRs->GetCollect("age");
			CString agetemp;
			if (var.vt != VT_NULL)
			{
				agetemp = (LPCSTR)_bstr_t(var);
			}
			m_patientInfoList.SetItemText(i, 4, agetemp);

			var = m_pRs->GetCollect("rangetype");
			CString rangetypetemp;
			if (var.vt != VT_NULL)
			{
				rangetypetemp = (LPCSTR)_bstr_t(var);
			}
			m_patientInfoList.SetItemText(i, 5, rangetypetemp);


			var = m_pRs->GetCollect("doctor");
			CString doctortemp;
			if (var.vt != VT_NULL)
			{
				doctortemp = (LPCSTR)_bstr_t(var);
			}
			m_patientInfoList.SetItemText(i, 6, doctortemp);


			i++;
			m_pRs->MoveNext();
		}
		ThisResult2.totalnums = m_patientInfoList.GetItemCount();
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}
	return TRUE;
	/*
	// 在CRP列表视图控件中插入列表项，并设置列表子项文本
	m_patientInfoList.InsertItem(0, _T("123456"));
	m_patientInfoList.SetItemText(0, 1, _T("NANCY"));
	m_patientInfoList.SetItemText(0, 2, _T("HELLEN"));
	m_patientInfoList.SetItemText(0, 3, _T("女"));
	m_patientInfoList.SetItemText(0, 4, _T("1991/01/1"));
	m_patientInfoList.SetItemText(0, 5, _T("1"));
	m_patientInfoList.SetItemText(0, 7, _T("HPC test"));
	*/
	return TRUE;
}


void CPatientInfoView::OnNMDblclkPatientinfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//TODO:  在此添加控件通知处理程序代码
	POSITION pos = m_patientInfoList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_patientInfoList.GetNextSelectedItem(pos);  // getting patients' number
		TRACE1("Item %d was selected!\n", nItem);
		CString patient_id = m_patientInfoList.GetItemText(nItem, 0);
		CString patient_name = m_patientInfoList.GetItemText(nItem, 1);
		CString patient_sex = m_patientInfoList.GetItemText(nItem, 2);
		CString patient_code = m_patientInfoList.GetItemText(nItem, 3);
		CString patient_age = m_patientInfoList.GetItemText(nItem, 4);
		CString patient_rangetype = m_patientInfoList.GetItemText(nItem, 5);
		CString patient_doctor = m_patientInfoList.GetItemText(nItem, 6);

		GetDlgItem(IDC_patient_id)->SetWindowText(patient_id);
		GetDlgItem(IDC_PATIENT_NAME)->SetWindowText(patient_name);
		GetDlgItem(IDC_PATIENT_SEX)->SetWindowText(patient_sex);
		GetDlgItem(IDC_PATIENT_CODE)->SetWindowText(patient_code);
		GetDlgItem(IDC_PATIENT_AGE)->SetWindowText(patient_age);
		GetDlgItem(IDC_PATIENT_RANGETYPE)->SetWindowText(patient_rangetype);
		GetDlgItem(IDC_PATIENT_DOCTOR)->SetWindowText(patient_doctor);

	}

	*pResult = 0;
}


void CPatientInfoView::OnClickedSave()
{
	// TODO:  在此添加控件通知处理程序代码
	CString patient_id, patient_name, patient_sex, patient_code, patient_age, patient_rangetype, patient_doctor;
	GetDlgItem(IDC_patient_id)->GetWindowText(patient_id);
	GetDlgItem(IDC_PATIENT_NAME)->GetWindowText(patient_name);
	GetDlgItem(IDC_PATIENT_SEX)->GetWindowText(patient_sex);
	GetDlgItem(IDC_PATIENT_CODE)->GetWindowText(patient_code);
	GetDlgItem(IDC_PATIENT_AGE)->GetWindowText(patient_age);
	GetDlgItem(IDC_PATIENT_RANGETYPE)->GetWindowText(patient_rangetype);
	GetDlgItem(IDC_PATIENT_DOCTOR)->GetWindowText(patient_doctor);
	//CString doctor_num, doctor_name, doctor_memo;
	//GetDlgItem(IDC_No)->GetWindowText(doctor_num);
	//GetDlgItem(IDC_Name)->GetWindowText(doctor_name);
	//GetDlgItem(IDC_Memo)->GetWindowText(doctor_memo);
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	CString filename;
	_variant_t var;
	CString strTemp;//该变量用于获取控件中的属性，用于进行一些逻辑判断
	filename.Format(L"appdata.accdb");
	CString checkSql = "select number from patientdata where number ='" + patient_id+"'";
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	
	ExeSql(m_pDB, m_pRs, checkSql);
	//CString select_sample = L"select * from patientdata";

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
		var = m_pRs->GetCollect((_variant_t)(long)0);//"number");//获得检测sql语句中查询的值，编号存在则执行流程
		if (var.vt != VT_NULL)
			strTemp = (LPCSTR)_bstr_t(var);
		if (strTemp != patient_id)
		{
			CString temp;
			temp = "The No." + patient_id + " is not in access!";
			MessageBox(temp);
			CloseDataBase(m_pDB, m_pRs);
			return;
		}
		m_pRs->MoveNext();
	}

	POSITION pos = m_patientInfoList.GetFirstSelectedItemPosition(); // getting current position of list
	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_patientInfoList.GetNextSelectedItem(pos);
		//nItem += 1;
		//CString id;
		//id.Format(_T("%d"), nItem);
		//更新数据库中的数据
		CString updateSql = _T(" update [patientdata] set [number]='") + patient_id + _T("',[name]='") + patient_name + _T("',[sex]='") + patient_sex + _T("',[code]='") + patient_code + _T("',[age]='") + patient_age + _T("',[rangetype]='") + patient_rangetype + _T("' , [doctor]='") + patient_doctor + _T("' where [number] ='") + patient_id+"'";
		ExeSql(m_pDB, m_pRs, updateSql);
		MessageBox(L"Save successfully!");

		//更新控件中的数据显示
		m_patientInfoList.SetItemText(nItem, 0, patient_id);
		m_patientInfoList.SetItemText(nItem, 1, patient_name);
		m_patientInfoList.SetItemText(nItem, 2, patient_sex);
		m_patientInfoList.SetItemText(nItem, 3, patient_code);
		m_patientInfoList.SetItemText(nItem, 4, patient_age);
		m_patientInfoList.SetItemText(nItem, 5, patient_rangetype);
		m_patientInfoList.SetItemText(nItem, 6, patient_doctor);
		
	}
	CloseDataBase(m_pDB, m_pRs);

}


void CPatientInfoView::OnManualAdd()
{
	 //TODO:  在此添加命令处理程序代码
	CString prow,pnumber,pname,psex,pcode,page,prangetype,pdoctor;
	CString strTemp = "";
	GetDlgItem(IDC_patient_id)->GetWindowText(pnumber);
	//MessageBox(L"1");
	CString select_name_sample = L"select * from patientdata";// where number = " + pnumber;
	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;
	CString filename;
	filename.Format(L"appdata.accdb");
	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	ExeSql(m_pDB, m_pRs, select_name_sample);
	//MessageBox(L"2");
	try{
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else{
			TRACE("表内数据为空");
			return;

		}
		while (!m_pRs->adoEOF)
		{
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
				strTemp = (LPCSTR)_bstr_t(var);
			if (strTemp == pnumber)
			{
				CString temp;
				temp = "The No." + pnumber + " has been in access!";
				MessageBox(temp);
				return;
			}
			m_pRs->MoveNext();
		}
		GetDlgItem(IDC_PATIENT_NAME)->GetWindowText(pname);
		GetDlgItem(IDC_PATIENT_SEX)->GetWindowText(psex);
		GetDlgItem(IDC_PATIENT_CODE)->GetWindowText(pcode);
		GetDlgItem(IDC_PATIENT_AGE)->GetWindowText(page);
		GetDlgItem(IDC_PATIENT_RANGETYPE)->GetWindowText(prangetype);
		GetDlgItem(IDC_PATIENT_DOCTOR)->GetWindowText(pdoctor);

		int count;
		CString scount;
		CString sqlSelectCount = "select max(row)  from patientdata";
		ExeSql(m_pDB, m_pRs, sqlSelectCount);
		//MessageBox(L"count0");
		var = m_pRs->GetCollect((_variant_t)(long)0);
		//MessageBox(L"var");
		if (var.vt != VT_NULL){
			//MessageBox(L"asd");
			count = atoi((LPCSTR)_bstr_t(var));
			TRACE("=============Count=%d\n", count);
		}
		
		int pcount =count+1;

		char str[20];
		itoa(pcount, str, 10);
		prow = str;

		if (pname != ""&&pnumber!=""){
			CString sqlInsertPatient = _T("INSERT INTO [patientdata]([row],[number],[name],[sex],[rangetype],[age],[code],[doctor]) values(" + prow + ",'" + pnumber + "','" + pname + "','" + psex + "','" + prangetype + "','" + page + "','" + pcode + "','" + pdoctor + "')");

			ExeSql(m_pDB, m_pRs, sqlInsertPatient);
			MessageBox(L"Doctor information has been appended successfully！");

			int i = m_patientInfoList.GetItemCount();
			m_patientInfoList.InsertItem(i, pnumber);			
			m_patientInfoList.SetItemText(i, 1, pname);
			m_patientInfoList.SetItemText(i, 2, psex);
			m_patientInfoList.SetItemText(i, 3, pcode);
			m_patientInfoList.SetItemText(i, 4, page);
			m_patientInfoList.SetItemText(i, 5, prangetype);
			m_patientInfoList.SetItemText(i, 6, pdoctor);


		}
		CString empty = "";
		GetDlgItem(IDC_patient_id)->SetWindowText(empty);
		GetDlgItem(IDC_PATIENT_NAME)->SetWindowText(empty);
		GetDlgItem(IDC_PATIENT_SEX)->SetWindowText(empty);
		GetDlgItem(IDC_PATIENT_CODE)->SetWindowText(empty);
		GetDlgItem(IDC_PATIENT_AGE)->SetWindowText(empty);
		GetDlgItem(IDC_PATIENT_RANGETYPE)->SetWindowText(empty);
		GetDlgItem(IDC_PATIENT_DOCTOR)->SetWindowText(empty);

		CloseDataBase(m_pDB, m_pRs);

	}
	catch (_com_error &e){
		TRACE("InsertPatientInfoList异常");
	}

}


void CPatientInfoView::OnDelete()
{
	// TODO:  在此添加命令处理程序代码
	POSITION pos = m_patientInfoList.GetFirstSelectedItemPosition(); // getting current position of list
	if (pos == NULL)
		TRACE("No items were selected!\n");
	else{
		int nItem = m_patientInfoList.GetNextSelectedItem(pos);     // getting patients' number
		TRACE1("Item %d was selected!\n", nItem);
		CString pnumber = m_patientInfoList.GetItemText(nItem, 0);
		//MessageBox(pnumber);
		_ConnectionPtr m_pDB;
		_RecordsetPtr m_pRs;
		CString filename;
		filename.Format(L"appdata.accdb");
		if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
			return;
		CString DEL_Item = _T("delete from patientdata where number='"+pnumber+"'");
		ExeSql(m_pDB, m_pRs, DEL_Item);
		MessageBox(L"Record of ID"+pnumber+" has been deleted!");

		m_patientInfoList.DeleteItem(nItem);

		CloseDataBase(m_pDB, m_pRs);
		
	}

}
