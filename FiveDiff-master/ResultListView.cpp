// ResultListView.cpp : 实现文件
//

#include "stdafx.h"
//#include "MainFrm.h"
//#include "BCGPChartExample.h"
//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
#include "ResultListView.h"
//#include "Includes_app.h"


// CResultListView

IMPLEMENT_DYNCREATE(CResultListView, CBCGPChartExampleView)

CResultListView::CResultListView()
: CBCGPChartExampleView(CResultListView::IDD)
{
	m_nFirstDayOfWeek = 1;
}

CResultListView::~CResultListView()
{
	//delete DetailView;
	//free(ThisResult.numofrs);
}

//ResultToDisplay CResultListView::ThisResult = { NULL, "000000000000" };

void CResultListView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPChartExampleView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ResultList);
	DDX_Control(pDX, IDC_RESULT_TIMEPICKER, m_ResultDate);
	DDX_Control(pDX, IDC_PAITIENT_RESULT, m_paitient_result);
}

BEGIN_MESSAGE_MAP(CResultListView, CBCGPChartExampleView)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RESULT_TIMEPICKER, &CResultListView::OnCloseupResultTimepicker)
	ON_WM_PAINT()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CResultListView::OnNMDblclkList)
	ON_BN_CLICKED(IDC_PAITIENT_RESULT, &CResultListView::OnPaitientResult)
END_MESSAGE_MAP()


// CResultListView 诊断

#ifdef _DEBUG
void CResultListView::AssertValid() const
{
	CBCGPChartExampleView::AssertValid();
}

#ifndef _WIN32_WCE
void CResultListView::Dump(CDumpContext& dc) const
{
	CBCGPChartExampleView::Dump(dc);
}
#endif
#endif //_DEBUG


// CResultListView 消息处理程序

void CResultListView::OnInitialUpdate()
{
	CBCGPChartExampleView::OnInitialUpdate();


	// TODO:  在此添加专用代码和/或调用基类
	m_ResultDate.SizeToContent();

	m_ResultDate.SetState(
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE,
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR |
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME |
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);

	m_ResultDate.SetFirstDayOfWeek(m_nFirstDayOfWeek);
	m_Date = COleDateTime::GetCurrentTime();
	m_ResultDate.SetDate(m_Date);
	InitResultForm();
	UpdateResultList(m_Date);

	int row;
	//将所有查询结果的编号进行保存，用于详细信息翻页用
	row = m_ResultList.GetItemCount();
	//if ((ThisResult.numofrs = (int *)malloc(row*sizeof(int))) == NULL)
	//{
	//	printf("Memory allocation for ResultsList failed--------!\n");
	//	exit(1);
	//}
	GetDlgItem(IDC_DAILY_RESULT)->EnableWindow(FALSE);
}




BOOL CResultListView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CBCGPChartExampleView::OnEraseBkgnd(pDC);
}


BOOL CResultListView::InitResultForm()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_ResultList.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_ResultList.SetExtendedStyle(m_ResultList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_worksheetList.SetItemColor(0, RGB(100, 125, 100), RGB(15, 235, 150));//设置特定Item 字体 背景颜色
	m_ResultList.SetRowHeigt(20);


	//// 为CRP列表视图控件添加四列

	m_ResultList.InsertColumn(0, _T("选择"), LVCFMT_CENTER, rect.Width() / 10, 0);
	m_ResultList.InsertColumn(1, _T("样本号"), LVCFMT_CENTER, rect.Width() / 8, 1);
	m_ResultList.InsertColumn(2, _T("时间"), LVCFMT_CENTER, rect.Width() / 8, 2);
	m_ResultList.InsertColumn(3, _T("病人编号"), LVCFMT_CENTER, rect.Width() / 8, 3);
	m_ResultList.InsertColumn(4, _T("病人姓名"), LVCFMT_CENTER, rect.Width() / 8, 4);
	m_ResultList.InsertColumn(5, _T("性别"), LVCFMT_CENTER, rect.Width() / 8, 5);
	m_ResultList.InsertColumn(6, _T("测试类型"), LVCFMT_CENTER, rect.Width() / 8, 6);
	m_ResultList.InsertColumn(7, _T("阳阴"), LVCFMT_CENTER, rect.Width() / 8, 6);


	// 在CRP列表视图控件中插入列表项，并设置列表子项文本
	m_ResultList.InsertItem(0, _T(""));
	m_ResultList.SetItemText(0, 1, _T("12345"));
	m_ResultList.SetItemText(0, 2, _T("2016/04/11 16:44:00"));
	m_ResultList.SetItemText(0, 3, _T("1111"));
	m_ResultList.SetItemText(0, 4, _T("张三"));
	m_ResultList.SetItemText(0, 5, _T("男"));
	m_ResultList.SetItemText(0, 6, _T("CBC+RET"));
	m_ResultList.SetItemText(0, 7, _T("阳"));

	m_ResultList.InsertItem(1, _T(""));
	m_ResultList.SetItemText(1, 1, _T("12345"));
	m_ResultList.SetItemText(1, 2, _T("2016/04/11 16:44:00"));
	m_ResultList.SetItemText(1, 3, _T("1111"));
	m_ResultList.SetItemText(1, 4, _T("张三"));
	m_ResultList.SetItemText(1, 5, _T("男"));
	m_ResultList.SetItemText(1, 6, _T("CBC+RET"));
	m_ResultList.SetItemText(1, 7, _T("阳"));

	m_ResultList.InsertItem(2, _T(""));
	m_ResultList.SetItemText(2, 1, _T("12345"));
	m_ResultList.SetItemText(2, 2, _T("2016/04/11 16:44:00"));
	m_ResultList.SetItemText(2, 3, _T("1111"));
	m_ResultList.SetItemText(2, 4, _T("张三"));
	m_ResultList.SetItemText(2, 5, _T("男"));
	m_ResultList.SetItemText(2, 6, _T("CBC+RET"));
	m_ResultList.SetItemText(2, 7, _T("阳"));

	return TRUE;
}


void CResultListView::UpdateResultList(COleDateTime Date)
{

	int	i = 0;
	static unsigned int date;
	static unsigned int today_start_num;
	static unsigned int today_end_num;
	CString today_start_num_1;
	CString today_end_num_1;

	_ConnectionPtr m_pDB;
	_RecordsetPtr m_pRs;

	_variant_t var;
	CString strNum = "";
	CString strTime = "";
	CString strName = "";
	CString strtemp;
	strtemp = "20";
	CString strSex[3] = { "男", "女", "" };
	m_ResultList.DeleteAllItems();//清空列表刷新
	int day = Date.GetDay();
	int month = Date.GetMonth();
	int year = Date.GetYear();

	date = year * 10000 + month * 100 + day;
	//由于位数原因，编号在存入数据库的日期的高两位截取掉
	today_start_num = (date % 1000000) * 10000;
	today_end_num = today_start_num + 9999;
	//代表一整天

	today_start_num_1.Format(_T("%d"), today_start_num);
	today_end_num_1.Format(_T("%d"), today_end_num);

	CString select_number_sample = _T("select * from sampledata where number >='") + today_start_num_1 + _T("' and number <='") + today_end_num_1 + _T("'");
	CString select_number_patient = _T("select * from patientdata where number >='") + today_start_num_1 + _T("' and number <='") + today_end_num_1 + _T("'");

	CString filename;
	filename.Format(_T("appdata.accdb"));

	if (OpenDataBase(filename, m_pDB, m_pRs) == -1)
		return;
	ExeSql(m_pDB, m_pRs, select_number_sample);//把特定编号的数据选取出来
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
		while (!m_pRs->adoEOF)
		{
			var = m_pRs->GetCollect("number");
			if (var.vt != VT_NULL)
				strNum = (LPCSTR)_bstr_t(var);
			ThisResult.numofrs[i] = strNum;
			strNum = strtemp + strNum;
			m_ResultList.InsertItem(i, _T(""));
			m_ResultList.SetItemText(i, 1, strNum);


			/*****************************/
			var = m_pRs->GetCollect("ID");
			CString strID;
			if (var.vt != VT_NULL)
				strID = (LPCSTR)_bstr_t(var);
			m_ResultList.SetItemText(i, 3, strID);

			var = m_pRs->GetCollect("mode");
			CString strMode;
			if (var.vt != VT_NULL)
				strMode = (LPCSTR)_bstr_t(var);
			m_ResultList.SetItemText(i, 6, strMode);

			/*****************************/

			var = m_pRs->GetCollect("time");
			if (var.vt != VT_NULL)
				strTime = (LPCSTR)_bstr_t(var);
			CString a = ":";
			strTime.Insert(2, a);
			strTime.Insert(5, a);
			m_ResultList.SetItemText(i, 2, strTime);
			i++;
			m_pRs->MoveNext();
		}
		ThisResult.totalnums = m_ResultList.GetItemCount();
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}

	i = 0;
	ExeSql(m_pDB, m_pRs, select_number_patient);
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
		while (!m_pRs->adoEOF)
		{


			var = m_pRs->GetCollect("name");
			if (var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			m_ResultList.SetItemText(i, 4, strName);

			var = m_pRs->GetCollect("sex");
			CString sextemp;
			if (var.vt != VT_NULL)
			{
				sextemp = (LPCSTR)_bstr_t(var);
				sextemp = strSex[_ttoi(sextemp)];
			}
			m_ResultList.SetItemText(i, 5, sextemp);

			i++;
			m_pRs->MoveNext();
		}
	}
	catch (_com_error &e)
	{
		TRACE("UpdateResultList异常");
	}
	CloseDataBase(m_pDB, m_pRs);

}

void CResultListView::OnCloseupResultTimepicker()
{
	// TODO:  在此添加控件通知处理程序代码
	m_Date = m_ResultDate.GetDate();
	int day = m_Date.GetDay();
	int month = m_Date.GetMonth();
	int year = m_Date.GetYear();
	TRACE("DAY:%d\n", day);
	TRACE("month:%d\n", month);
	TRACE("YEAR:%d\n", year);
	UpdateResultList(m_Date);
}


void CResultListView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CBCGPChartExampleView::OnPaint()
	//UpdateResultList();
}




void CResultListView::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//MessageBox(L"Assert Here!");
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	POSITION pos = m_ResultList.GetFirstSelectedItemPosition();


	if (pos == NULL)
		TRACE("No items were selected!\n");
	else
	{
		int nItem = m_ResultList.GetNextSelectedItem(pos);
		TRACE1("Item %d was selected!\n", nItem);
		CString selectnum = m_ResultList.GetItemText(nItem, 1);
		ThisResult.nownum = nItem;

	}
	if (m_ResultList.GetNextSelectedItem(pos)<m_ResultList.GetItemCount())
	{
		CMainFrame* pMf = (CMainFrame*)AfxGetMainWnd();
		CRect rect;
		CRect rect1;
		pMf->GetClentRectEx(rect);

		CRuntimeClass* pClass = RUNTIME_CLASS(CResultDetails);
		CView* pView = DYNAMIC_DOWNCAST(CView, pClass->CreateObject());

		this->m_pResultDetails = (CResultDetails*)pView;
		m_pResultDetails->pThisResult = &ThisResult;


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
		UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
		::SetWindowLong(pActiveView->m_hWnd, GWL_ID,
			::GetWindowLong(pView->m_hWnd, GWL_ID));
		::SetWindowLong(pView->m_hWnd, GWL_ID, temp);
		pActiveView->ShowWindow(SW_HIDE);
		pView->ShowWindow(SW_SHOW);
		((CMainFrame*)::AfxGetMainWnd())->SetActiveView(pView);
		//::PostMessage(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), WM_WINDOWCHANGE, 17, 0);

	}
}

void CResultListView::OnPaitientResult()
{
	// TODO:  在此添加控件通知处理程序代码
	CMainFrame* pMf = (CMainFrame*)AfxGetMainWnd();
	CRect rect;
	CRect rect1;
	pMf->GetClentRectEx(rect);

	CRuntimeClass* pClass = RUNTIME_CLASS(CPatientResultView);
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
		rect, pMf, AFX_IDW_PANE_FIRST + 11, &newContext))
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
