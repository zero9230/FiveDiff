// PatientResultView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "PatientResultView.h"
#include "Includes_app.h"

// CPatientResultView
bool is_search = false;
IMPLEMENT_DYNCREATE(CPatientResultView, CBCGPChartExampleView)
CPatientResultView::CPatientResultView()
: CBCGPChartExampleView(CPatientResultView::IDD)
, m_patientname(_T(""))
{

}

CPatientResultView::~CPatientResultView()
{
}

void CPatientResultView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_PatientResultList);
	DDX_Control(pDX, IDC_DAILY_RESULT2, m_daily_result);
	DDX_Text(pDX, IDC_EDIT_NAME, m_patientname);

	DDX_Control(pDX, IDC_COMBO1, patient_sex);
}


BEGIN_MESSAGE_MAP(CPatientResultView, CFormView)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_DAILY_RESULT2, &CPatientResultView::OnDailyResult2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPatientResultView::OnNMDblclkList1)
//	ON_BN_CLICKED(IDC_PATIENT_RESULT2, &CPatientResultView::OnBnClickedPatientResult2)
//ON_BN_CLICKED(IDC_BUTTON3, &CPatientResultView::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CPatientResultView::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CPatientResultView 诊断

#ifdef _DEBUG
void CPatientResultView::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CPatientResultView::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPatientResultView 消息处理程序



BOOL CPatientResultView::InitPatientResultForm()
{
	CRect rect;
	int i = 0;
	CString select_name_sample = L"select * from patientdata ";// where name = '" + m_patientname + "'";
	CString strNum = "";
	CString strtemp = "20";
	CString strSex[3] = { "空", "男", "女" };

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;
	patient_sex.AddString(_T("空"));
	patient_sex.AddString(_T("男"));
	patient_sex.AddString(_T("女"));
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
	//m_PatientResultList.InsertItem(0, _T(""));
	//m_PatientResultList.SetItemText(0, 1, _T("12345")); 
	//m_PatientResultList.SetItemText(0, 2, _T("2016/04/11 16:44:00"));
	//m_PatientResultList.SetItemText(0, 3, _T("1111"));
	//m_PatientResultList.SetItemText(0, 4, _T("张三"));
	//m_PatientResultList.SetItemText(0, 5, _T("男"));
	//m_PatientResultList.SetItemText(0, 6, _T("CBC+RET"));
	//m_PatientResultList.SetItemText(0, 7, _T("阳"));

	//m_PatientResultList.InsertItem(1, _T(""));
	//m_PatientResultList.SetItemText(1, 1, _T("12345"));
	//m_PatientResultList.SetItemText(1, 2, _T("2016/04/11 16:44:00"));
	//m_PatientResultList.SetItemText(1, 3, _T("1111"));
	//m_PatientResultList.SetItemText(1, 4, _T("张三"));
	//m_PatientResultList.SetItemText(1, 5, _T("男"));
	//m_PatientResultList.SetItemText(1, 6, _T("CBC+RET"));
	//m_PatientResultList.SetItemText(1, 7, _T("阳"));

	//m_PatientResultList.InsertItem(2, _T(""));
	//m_PatientResultList.SetItemText(2, 1, _T("12345"));
	//m_PatientResultList.SetItemText(2, 2, _T("2016/04/11 16:44:00"));
	//m_PatientResultList.SetItemText(2, 3, _T("1111"));
	//m_PatientResultList.SetItemText(2, 4, _T("张三"));
	//m_PatientResultList.SetItemText(2, 5, _T("男"));
	//m_PatientResultList.SetItemText(2, 6, _T("CBC+RET"));
	//m_PatientResultList.SetItemText(2, 7, _T("阳"));



	return TRUE;
}


BOOL CPatientResultView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}


void CPatientResultView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	InitPatientResultForm();
	GetDlgItem(IDC_PATIENT_RESULT2)->EnableWindow(false);
}



void CPatientResultView::OnDailyResult2()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pMf = (CMainFrame*)AfxGetMainWnd();
	CRect rect;
	CRect rect1;
	pMf->GetClentRectEx(rect);

	CRuntimeClass* pClass = RUNTIME_CLASS(CResultListView);
	CView* pView = DYNAMIC_DOWNCAST(CView, pClass->CreateObject());

	ASSERT_VALID(pView);
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
	pActiveView->ShowWindow(SW_HIDE);
	pView->ShowWindow(SW_SHOW);
	((CMainFrame*)::AfxGetMainWnd())->SetActiveView(pView);
}



//此处可能有问题
void CPatientResultView::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
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
	}
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


//void CPatientResultView::OnBnClickedPatientResult2()
//{
//	// TODO:  在此添加控件通知处理程序代码
//}


//void CPatientResultView::OnBnClickedButton3()
//{
//	// TODO:  在此添加控件通知处理程序代码
//}


void CPatientResultView::OnBnClickedButtonSearch()
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
	ID.Delete(0,2);
	sex_1 = patient_sex.GetCurSel();
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
		select_name_sample.Delete(select_name_sample.GetLength()-5, 4);

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
