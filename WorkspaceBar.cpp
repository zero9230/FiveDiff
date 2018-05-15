//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2014 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// WorkspaceBar.cpp : implementation of the CWorkspaceBar class
//

#include "stdafx.h"
#include "BCGPChartExample.h"
#include "WorkspaceBar.h"
////#include "MainFrm.h"
//
//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
#include "ConfigSetView.h"
#include "TimeSetView.h"
#include "Includes_app.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int idTree = 1;
/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar

BEGIN_MESSAGE_MAP(CWorkspaceBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CWorkspaceBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_TREE_COLLAPSE_ALL, OnTreeCollapseAll)
	ON_COMMAND(ID_TREE_EXPAND_ALL, OnTreeExpandAll)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED, idTree, OnSelectTree)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar construction/destruction

CWorkspaceBar::CWorkspaceBar()
{
}

CWorkspaceBar::~CWorkspaceBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

static CDemoFeature2 features[] =
{
	CDemoFeature2(0, CDemoFeature2::TIME_SET, _T("日期/时间"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(1, CDemoFeature2::TIME_SET, _T("单位设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(2, CDemoFeature2::TIME_SET, _T("范围设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(3, CDemoFeature2::TIME_SET, _T("阈值设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(4, CDemoFeature2::TIME_SET, _T("上传设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(5, CDemoFeature2::TIME_SET, _T("打印设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(6, CDemoFeature2::TIME_SET, _T("报告设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(7, CDemoFeature2::TIME_SET, _T("恢复系统默认设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(7, CDemoFeature2::TIME_SET, _T("PLT右阈值设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(7, CDemoFeature2::TIME_SET, _T("电机参数设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(7, CDemoFeature2::TIME_SET, _T("修改因子设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(7, CDemoFeature2::TIME_SET, _T("自动维护设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(7, CDemoFeature2::TIME_SET, _T("LMNE电阻抗设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(7, CDemoFeature2::TIME_SET, _T("公司/型号设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(7, CDemoFeature2::TIME_SET, _T("开发者设置"), RUNTIME_CLASS(CTimeSetView)),
	CDemoFeature2(7, CDemoFeature2::TIME_SET, _T("自动进样设置"), RUNTIME_CLASS(CTimeSetView)),

	CDemoFeature2()
};

int CWorkspaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create toolbar:
#ifdef _BCGSUITE_INC_
	if (!m_wndToolBar.Create (this, AFX_DEFAULT_TOOLBAR_STYLE, AFX_IDW_TOOLBAR + 1) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR_TREE, 0, 0, TRUE /* Is locked */))
	{
		TRACE0("Failed to create toolbar\n");
		return -1; // fail to create
	}

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
		
	m_wndToolBar.SetPaneStyle (
		m_wndToolBar.GetPaneStyle () & 
			~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
#else
	if (!m_wndToolBar.Create (this, dwDefaultToolbarStyle, AFX_IDW_TOOLBAR + 1) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR_TREE, 0, 0, TRUE /* Is locked */))
	{
		TRACE0("Failed to create toolbar\n");
		return -1; // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
		
	m_wndToolBar.SetBarStyle (
		m_wndToolBar.GetBarStyle () & 
			~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
#endif

	m_wndToolBar.SetOwner (this);

	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_TREE_EXPAND_ALL), NULL, TRUE, FALSE);
	m_wndToolBar.SetToolBarBtnText (m_wndToolBar.CommandToIndex (ID_TREE_COLLAPSE_ALL), NULL, TRUE, FALSE);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame (FALSE);

	// Create tree windows.
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_TRACKSELECT |
								TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_FULLROWSELECT;
	
	if (!m_wndTree.Create (dwViewStyle, rectDummy, this, idTree))
	{
		TRACE0("Failed to create workspace view\n");
		return -1;      // fail to create
	}

#ifndef _BCGSUITE_INC_
	globalData.SetWindowTheme(&m_wndTree, L"explorer", NULL);
#endif

	m_wndTree.SetBkColor(RGB(255,255,255));

	AddFeatureGroup(_T("日期/时间"), 0);
	AddFeatureGroup(_T("单位设置"), 1);
	AddFeatureGroup(_T("范围设置"), 2);
	AddFeatureGroup(_T("阈值设置"), 3);
	AddFeatureGroup(_T("上传设置"), 4);
	AddFeatureGroup(_T("打印设置"), 5);
	AddFeatureGroup(_T("报告设置"), 6);
	AddFeatureGroup(_T("工程师服务"), 7);


	SelectItem(1);
	return 0;
}

void CWorkspaceBar::AddFeatureGroup(LPCTSTR lpszName, int nGroupID)
{
	HTREEITEM hFolder = m_wndTree.InsertItem (lpszName, 0);

	for (int i = 0;; i++)
	{
		CDemoFeature2& feature = features[i];
		if (feature.m_nGroup == -1)
		{
			break;
		}

		if (feature.m_nGroup == nGroupID)
		{
			HTREEITEM hTreeItem = m_wndTree.InsertItem (feature.m_strName, 1, 1, hFolder);

			int id = GetFeatureCount() + 1;

			feature.m_id = id;
			feature.m_hItem = hTreeItem;

			m_mapItems.SetAt(id, &feature);

			m_wndTree.SetItemData(hTreeItem, id);
		}
	}
}

void CWorkspaceBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout ();

	/*CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	if (pFrame != NULL)
	{	
		pFrame->AdjustDockingLayout ();
	}*/
}

void CWorkspaceBar::OnSelectTree(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	HTREEITEM hTreeItem = m_wndTree.GetSelectedItem ();
	if (hTreeItem != NULL)
	{
		int nView = (int)m_wndTree.GetItemData(hTreeItem);
		if (nView == 0)	// Group
		{
			m_wndTree.Expand(hTreeItem, TVE_EXPAND);

			HTREEITEM hTreeChild = m_wndTree.GetNextItem(hTreeItem, TVGN_CHILD);
			if (hTreeChild != NULL)
			{
				m_wndTree.SelectItem(hTreeChild);
				nView = (int)m_wndTree.GetItemData(hTreeChild);
			}
		}
		/*CConfigSetView* tempview=new(CConfigSetView);
		tempview->SelectView(nView);
		delete tempview;*/
		//SetDlg->SelectView(nView);

		//CConfigSetView::SelectView(nView);
		SetPTR->SelectView(nView);
	/*	if (nView > 0 && AfxGetMainWnd() != NULL)
		{
			((CMainFrame*)AfxGetMainWnd())->SelectView(nView);
		}*/
	}
	*pResult = 0;
}

void CWorkspaceBar::SelectItem(int id)
{
	CDemoFeature2* pItem = NULL;
	
	if (m_mapItems.Lookup(id, pItem))
	{
		m_wndTree.SelectItem(pItem->m_hItem);
		m_wndTree.Expand(m_wndTree.GetParentItem(pItem->m_hItem), TVE_EXPAND);
		m_wndTree.EnsureVisible(pItem->m_hItem);
	}

}

CRuntimeClass* CWorkspaceBar::GetFeatureViewRTI(int id) const
{
	CDemoFeature2* pItem = NULL;
	
	if (m_mapItems.Lookup(id, pItem))
	{
		return pItem->m_RTI;
	}

	return NULL;
}

void CWorkspaceBar::GetFeatureName(int id, CString& strTitle) const
{
	CDemoFeature2* pItem = NULL;
	
	if (m_mapItems.Lookup(id, pItem))
	{
		strTitle = pItem->m_strName;
	}
	else
	{
		strTitle.Empty();
	}
}

CDemoFeature2::Feature CWorkspaceBar::GetFeature(int id) const
{
	CDemoFeature2* pItem = NULL;
	
	if (m_mapItems.Lookup(id, pItem))
	{
		return pItem->m_Feature;
	}
	else
	{
		return CDemoFeature2::BCGP_Unknown;
	}
}

void CWorkspaceBar::AdjustLayout ()
{
	CRect rectClient;
	GetClientRect (rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout (FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos (NULL, 0, 0, 
								rectClient.Width (), cyTlb,
								SWP_NOACTIVATE | SWP_NOZORDER);

	m_wndTree.SetWindowPos (NULL, 0, cyTlb, 
							rectClient.Width (), rectClient.Height () - cyTlb, 
							SWP_NOACTIVATE | SWP_NOZORDER);
}

void CWorkspaceToolBar::AdjustLayout ()
{
	CBCGPToolBar::AdjustLayout ();

	((CWorkspaceBar*) GetParent ())->AdjustLayout ();
}

void CWorkspaceBar::OnTreeCollapseAll() 
{
	HTREEITEM hSelectedItem = m_wndTree.GetSelectedItem();
	HTREEITEM hChildItem = m_wndTree.GetRootItem();

	while (hChildItem != NULL)
	{
		m_wndTree.Expand(hChildItem, TVE_COLLAPSE);
		hChildItem = m_wndTree.GetNextItem(hChildItem, TVGN_NEXT);
	}

	m_wndTree.Expand(m_wndTree.GetParentItem(hSelectedItem), TVE_EXPAND);
	m_wndTree.SelectItem(hSelectedItem);
	m_wndTree.EnsureVisible(hSelectedItem);
}

void CWorkspaceBar::OnTreeExpandAll() 
{
	HTREEITEM hSelectedItem = m_wndTree.GetSelectedItem();
	HTREEITEM hChildItem = m_wndTree.GetRootItem();

	while (hChildItem != NULL)
	{
		m_wndTree.Expand(hChildItem, TVE_EXPAND);
		hChildItem = m_wndTree.GetNextItem(hChildItem, TVGN_NEXT);
	}

	m_wndTree.EnsureVisible(hSelectedItem);
}
