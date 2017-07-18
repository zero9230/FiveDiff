// ConfigSetView.cpp : 实现文件
//

#include "stdafx.h"
//#include "BCGPChartExample.h"
#include "ConfigSetView.h"
//#include "afxdialogex.h"
//#include "Includes_app.h"

// CConfigSetView 对话框

IMPLEMENT_DYNAMIC(CConfigSetView, CDialogEx)

CConfigSetView::CConfigSetView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigSetView::IDD, pParent)
{
	m_treePage[0] = NULL;
	m_treePage[1] = new CTimeSetView;
	m_treePage[2] = new	CUnitSetView;
	m_treePage[3] = new	CRangeSetView;
	m_treePage[4] = new	CThresholdSetView;
	m_treePage[5] = new	CUploadSetView;
	m_treePage[6] = new	CPrintSetView;
	m_treePage[7] = new	CReportSetView;
	m_treePage[8] = new	CResetView;
	m_treePage[9] = new	CPLTSetView;
	m_treePage[10] = new	CMotorSetView;
	m_treePage[11] = new	CCorrectParaSetView;
	m_treePage[12] = new	CAutoMaintenanceSetView;
	m_treePage[13] = new	CLMNESetView;
	m_treePage[14] = new	CCompanySetView;
	m_treePage[15] = new	CDevelopmentSetView;
	m_treePage[16] = new	CAutoSamplingSetView;

	SetView[0] = 0;
	SetView[1] = IDD_TIMESET;
	SetView[2] = IDD_UNITSET;
	SetView[3] = IDD_RANGESET;
	SetView[4] = IDD_THRESHOLDSET;
	SetView[5] = IDD_UPLOADSET;
	SetView[6] = IDD_PRINTSET;
	SetView[7] = IDD_REPORTSET;
	SetView[8] = IDD_RESET;
	SetView[9] = IDD_PLTSET;
	SetView[10] = IDD_MOTORSET;
	SetView[11] = IDD_CORRECTEPARASET;
	SetView[12] = IDD_AUTOMAINTENANCESET;
	SetView[13] = IDD_LMNESET;
	SetView[14] = IDD_COMPANYSET;
	SetView[15] = IDD_DEVELOPMENTSET;
	SetView[16] = IDD_AUTOSAMPLINGSET;

}

CConfigSetView::~CConfigSetView()
{
}

void CConfigSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigSetView, CDialogEx)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CConfigSetView 消息处理程序


BOOL CConfigSetView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(_T("设置"));


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


int CConfigSetView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize(CSize(16, 16));
	imagesWorkspace.SetTransparentColor(RGB(255, 0, 255));
	imagesWorkspace.Load(IDB_WORKSPACE);
	imagesWorkspace.SmoothResize(globalData.GetRibbonImageScale());

	CRect rc;
	GetClientRect(rc);

	if (!m_wndWorkSpace.Create(_T("设置选项"), this, CRect(0, 0, 200, rc.Height()-50),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI,
		CBRS_BCGP_REGULAR_TABS,
		CBRS_BCGP_RESIZE | CBRS_BCGP_AUTOHIDE))
	{
		TRACE0("Failed to create Workspace bar\n");
		return -1;      // fail to create
	}

	m_wndWorkSpace.SetIcon(imagesWorkspace.ExtractIcon(0), FALSE);

	m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);

	//EnableDocking(CBRS_ALIGN_ANY);
	//EnableAutoHideBars(CBRS_ALIGN_ANY);



	//DockControlBar(&m_wndWorkSpace);

	m_wndWorkSpace.SelectItem(m_nCurrType);


	return 0;
}



CView* CConfigSetView::GetView(int nID)
{
	
	if (m_arViews.GetSize() == 0)
	{
		const int nCount = m_wndWorkSpace.GetFeatureCount();
		for (int i = 0; i < nCount; i++)
		{
			m_arViews.Add(NULL);
		}
	}

	int nIndex = nID - 1;

	if (nIndex < 0 || nIndex >= m_arViews.GetSize())
	{
		ASSERT(FALSE);
		return NULL;
	}

	CView* pView = m_arViews[nIndex];
	if (pView != NULL)
	{
		return pView;
	}

	CRuntimeClass* pClass = m_wndWorkSpace.GetFeatureViewRTI(nID);
	if (pClass == NULL)
	{
		ASSERT(FALSE);
		return NULL;
	}

	ASSERT(pClass->IsDerivedFrom(RUNTIME_CLASS(CView)));

	pView = DYNAMIC_DOWNCAST(CView, pClass->CreateObject());
	ASSERT_VALID(pView);

	CDocument* pCurrentDoc = ((CMainFrame*)::AfxGetMainWnd())->GetActiveDocument();

	CCreateContext newContext;
	newContext.m_pNewViewClass = NULL;
	newContext.m_pNewDocTemplate = NULL;
	newContext.m_pLastView = NULL;
	newContext.m_pCurrentFrame = NULL;
	newContext.m_pCurrentDoc = pCurrentDoc;


	if (!pView->Create(NULL, _T(""), (AFX_WS_DEFAULT_VIEW & ~WS_VISIBLE),
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST + 15+nIndex, &newContext))
	{
		TRACE1("Failed to create view '%s'\n", pClass->m_lpszClassName);
		delete pView;
		return NULL;
	}

	pView->OnInitialUpdate();

	m_arViews.SetAt(nIndex, pView);
	return pView;
}

BOOL CConfigSetView::Activeflg[17] = {false};
int	 CConfigSetView::ActiveView = 1;
void CConfigSetView::SelectView(int nID)
{

	if (Activeflg[nID] == false)
	{
		for (int i=0; i <16; i++)
		{
			Activeflg[i] = false;
		}
		m_treePage[nID]->Create(SetView[nID], this);

		m_treePage[nID]->ShowWindow(SW_SHOW);
		if (ActiveView != nID)
		{
			//m_treePage[ActiveView]->ShowWindow(SW_HIDE);
			m_treePage[ActiveView]->DestroyWindow();
		}
		ActiveView = nID;
		Activeflg[nID] = true;
	}
	CRect m_rect;
	GetClientRect(m_rect);
	m_rect.left = 200;
	m_rect.bottom = m_rect.bottom - 50;
	m_treePage[nID]->MoveWindow(m_rect);

}

void CConfigSetView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//CRect rect;
	//GetClientRect(rect);
	//dc.FillSolidRect(rect, RGB(255, 255, 255));
	//dc.FillPath();

	//CDialogEx::OnPaint();
}
