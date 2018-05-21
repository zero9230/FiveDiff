// PatientResultView2.cpp : 实现文件
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "PatientResultView2.h"
#include "afxdialogex.h"


// CPatientResultView2 对话框

IMPLEMENT_DYNAMIC(CPatientResultView2, CDialogEx)

CPatientResultView2::CPatientResultView2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPatientResultView2::IDD, pParent)
{
	is_search = false;

}

CPatientResultView2::~CPatientResultView2()
{
}

void CPatientResultView2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PatientResultList);
	//DDX_Control(pDX, IDC_DAILY_RESULT2, m_daily_result);
	DDX_Text(pDX, IDC_EDIT_NAME, m_patientname);
	//DDX_Text(pDX, IDC_EDIT_GENDER, m_patientGender);
	DDX_Control(pDX, IDC_COMBOX_SEX, patient_gender);
}


BEGIN_MESSAGE_MAP(CPatientResultView2, CDialogEx)
	
	ON_WM_ERASEBKGND()
	//ON_BN_CLICKED(IDC_DAILY_RESULT2, &CPatientResultView2::OnDailyResult2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPatientResultView2::OnNMDblclkList1)
	//	ON_BN_CLICKED(IDC_PATIENT_RESULT2, &CPatientResultView::OnBnClickedPatientResult2)
	//ON_BN_CLICKED(IDC_BUTTON3, &CPatientResultView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CPatientResultView2::OnBnClickedButtonSearch)
END_MESSAGE_MAP()



// CPatientResultView2 消息处理程序






BOOL CPatientResultView2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitPatientResultForm();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


BOOL CPatientResultView2::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnEraseBkgnd(pDC);
}
BOOL CPatientResultView2::InitPatientResultForm()
{
	CRect rect;
	int i = 0;
	CString select_name_sample = L"select * from patientdata ";// where name = '" + m_patientname + "'";
	CString strNum = "";
	CString strtemp = "20";
	CString strSex[3] = { "空", "男", "女" };

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	patient_gender.AddString(_T("空"));
	patient_gender.AddString(_T("男"));
	patient_gender.AddString(_T("女"));

	_variant_t var;
	is_search = false;
	CString filename;
	filename.Format(L"appdata.accdb");

	// 获取编程语言列表视图控件的位置和大小   
	m_PatientResultList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_PatientResultList.SetExtendedStyle(m_PatientResultList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_PatientResultList.SetRowHeigt(20);


	// 为CRP列表视图控件添加四列
	m_PatientResultList.InsertColumn(0, _T("选择"), LVCFMT_CENTER, rect.Width() / 10, 0);
	m_PatientResultList.InsertColumn(1, _T("样本号"), LVCFMT_CENTER, rect.Width() / 8, 1);
	m_PatientResultList.InsertColumn(2, _T("时间"), LVCFMT_CENTER, rect.Width() / 8, 2);
	m_PatientResultList.InsertColumn(3, _T("病人编号"), LVCFMT_CENTER, rect.Width() / 8, 3);
	m_PatientResultList.InsertColumn(4, _T("病人姓名"), LVCFMT_CENTER, rect.Width() / 8, 4);
	m_PatientResultList.InsertColumn(5, _T("性别"), LVCFMT_CENTER, rect.Width() / 8, 5);
	m_PatientResultList.InsertColumn(6, _T("测试类型"), LVCFMT_CENTER, rect.Width() / 8, 6);
	m_PatientResultList.InsertColumn(7, _T("阳阴"), LVCFMT_CENTER, rect.Width() / 8, 6);

	// 在CRP列表视图控件中插入列表项，并设置列表子项文本

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)//作用为打开数据库
		return FALSE;
	ExeSql(m_pDB, m_pRs, select_name_sample);     //执行数据库
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
			strNum = strtemp + strNum;								//样本号读取正确，并在前面加上20
			m_PatientResultList.InsertItem(i, _T(""));              //显示信息，第一个参数为行，第二个参数为列，第三个参数为内容
			m_PatientResultList.SetItemText(i, 1, strNum);


			var = m_pRs->GetCollect("sex");
			CString sextemp;
			if (var.vt != VT_NULL)
			{
				sextemp = (LPCSTR)_bstr_t(var);

				sextemp = strSex[_ttoi(sextemp)];
			}
			m_PatientResultList.SetItemText(i, 5, sextemp);



			/*******************************************/



			var = m_pRs->GetCollect("ID");
			CString strID;
			if (var.vt != VT_NULL)
				strID = (LPCSTR)_bstr_t(var);
			m_PatientResultList.SetItemText(i, 3, strID);
			//m_PatientResultList.InsertItem(i, _T(""));              //显示信息，第一个参数为行，第二个参数为列，第三个参数为内容

			var = m_pRs->GetCollect("name");
			CString strName;
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			m_PatientResultList.SetItemText(i, 4, strName);


			/*******************************************/


			/*var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
			strTime = (LPCSTR)_bstr_t(var);
			CString a = ":";
			strTime.Insert(2, a);
			strTime.Insert(5, a);
			m_PatientResultList.SetItemText(i, 2, strTime);*/

			i++;
			m_pRs->MoveNext();
		}
		ThisResult2.totalnums = m_PatientResultList.GetItemCount();
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}


	return TRUE;
}

void CPatientResultView2::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//MessageBox(L"Assert Here!");
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	POSITION pos = m_PatientResultList.GetFirstSelectedItemPosition();

	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_PatientResultList.GetNextSelectedItem(pos);//获得病人信息编号
		TRACE1("Item %d was selected!\n", nItem);
		CString selectnum = m_PatientResultList.GetItemText(nItem, 1);
		if (is_search == true)
			ThisResult2.nownum = ThisRelation.ado_pos[nItem];
		else
			ThisResult2.nownum = nItem;
		if (m_PatientResultList.GetNextSelectedItem(pos) < m_PatientResultList.GetItemCount())
		{
			CMainFrame* pMf = (CMainFrame*)AfxGetMainWnd();
			CRect rect;
			pMf->GetClentRectEx(rect);

			/**********以下过程进行界面切换**************/
			CRuntimeClass* pClass = RUNTIME_CLASS(CResultDetails);
			CView* pView = DYNAMIC_DOWNCAST(CView, pClass->CreateObject());

			//下面两句看不太懂，可能问题在此处
			this->m_pResultDetails2 = (CResultDetails*)pView;
			m_pResultDetails2->pThisResult = &ThisResult2;

			//必然在此处触发断言失败！
			//MessageBox(L"Before failure");
			ASSERT_VALID(pView);
			//MessageBox(L"After  failure");

			CDocument* pCurrentDoc = ((CMainFrame*)::AfxGetMainWnd())->GetActiveDocument();

			CCreateContext newContext;
			newContext.m_pNewViewClass = NULL;
			newContext.m_pNewDocTemplate = NULL;
			newContext.m_pLastView = NULL;
			newContext.m_pCurrentFrame = NULL;
			newContext.m_pCurrentDoc = pCurrentDoc;

			if (!pView->Create(NULL, _T(""), (AFX_WS_DEFAULT_VIEW & ~WS_VISIBLE),
				rect, pMf, AFX_IDW_PANE_FIRST + 10, &newContext))
			{
				delete pView;
				return;
			}
			pView->OnInitialUpdate();
			CView* pActiveView = ((CMainFrame*)::AfxGetMainWnd())->GetActiveView();
			UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);

			::SetWindowLong(pActiveView->m_hWnd, GWL_ID,
				::GetWindowLong(pView->m_hWnd, GWL_ID));

			::SetWindowLong(pView->m_hWnd, GWL_ID, temp);
			pActiveView->ShowWindow(SW_HIDE);
			pView->ShowWindow(SW_SHOW);
			((CMainFrame*)::AfxGetMainWnd())->SetActiveView(pView);
		}
	}

}
void CPatientResultView2::OnBnClickedButtonSearch()
{
	// TODO:  在此添加控件通知处理程序代码
	CString ID, name, age, sex;
	char sex_1;
	CRect rect;
	int i = 0;
	CString select_name_sample = L"select * from patientdata where";
	CString strNum = "";
	CString strtemp = "20";
	CString strSex[3] = { "空", "男", "女" };
	//获取数据
	m_PatientResultList.DeleteAllItems();
	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	GetDlgItem(IDC_EDIT6)->GetWindowText(age);
	GetDlgItem(IDC_EDIT_ID)->GetWindowText(ID);
	ID.Delete(0, 2);
	sex_1 = patient_gender.GetCurSel();
	if (sex_1 < 3 && sex_1 >= 0)
	{
		sex_1 = sex_1 + 48;
		sex = sex_1;
	}
	//判断检索条件
	if (name.GetLength() != 0)
		select_name_sample += " name like '%" + name + "%' and ";
	if (age.GetLength() != 0)
		select_name_sample += " age = '" + age + "' and ";
	if (ID.GetLength() != 0)
		select_name_sample += " number like '%" + ID + "%' and ";
	if (sex.GetLength() != 0)
		select_name_sample += " sex = '" + sex + "'";
	else
		select_name_sample.Delete(select_name_sample.GetLength() - 5, 4);

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
		if (!m_pRs->BOF){
			m_pRs->MoveFirst();
		}
		else
		{
			TRACE("表内数据为空");
			return;
		}

		bool bo = false;
		int pos;
		is_search = false;
		while (!m_pRs->adoEOF)
		{
			if (i == 0)
			{
				m_PatientResultList.DeleteAllItems();
				is_search = true;
			}

			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
				strNum = (LPCSTR)_bstr_t(var);
			ThisResult2.numofrs[i] = strNum;
			strNum = strtemp + strNum;								//样本号读取正确，并在前面加上20
			m_PatientResultList.InsertItem(i, _T(""));              //显示信息，第一个参数为行，第二个参数为列，第三个参数为内容
			m_PatientResultList.SetItemText(i, 1, strNum);


			var = m_pRs->GetCollect("sex");
			CString sextemp;
			if (var.vt != VT_NULL)
			{
				sextemp = (LPCSTR)_bstr_t(var);

				sextemp = strSex[_ttoi(sextemp)];
			}
			m_PatientResultList.SetItemText(i, 5, sextemp);



			/*******************************************/



			var = m_pRs->GetCollect("ID");
			CString strID;
			if (var.vt != VT_NULL)
				strID = (LPCSTR)_bstr_t(var);
			m_PatientResultList.SetItemText(i, 3, strID);            //显示信息，第一个参数为行，第二个参数为列，第三个参数为内容

			var = m_pRs->GetCollect("name");
			CString strName;
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			m_PatientResultList.SetItemText(i, 4, strName);


			i++;
			m_pRs->MoveNext();

		}
		if (m_pRs->adoEOF && is_search == false)
			MessageBox(L"can not find!");
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}
}