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
// WorkspaceBar.h : interface of the CWorkspaceBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKSPACEBAR_H__435B2ABB_C4AB_4400_B80C_7EE3520CBFEA__INCLUDED_)
#define AFX_WORKSPACEBAR_H__435B2ABB_C4AB_4400_B80C_7EE3520CBFEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct CDemoFeature2
{
	enum Feature
	{
		BCGP_Unknown = -1,
		TIME_SET,


	};

	CDemoFeature2()
	{
		m_nGroup = -1;
		m_id = 0;
		m_Feature = BCGP_Unknown;
		m_RTI = NULL;
		m_hItem = NULL;
	}

	CDemoFeature2(int nGroup, Feature feature, LPCTSTR lpszName, CRuntimeClass* pRTI)
	{
		m_nGroup = nGroup;
		m_id = 0;
		m_Feature = feature;
		m_strName = lpszName;
		m_RTI = pRTI;
		m_hItem = NULL;
	}

	int				m_nGroup;
	int				m_id;
	Feature			m_Feature;
	CString			m_strName;
	CRuntimeClass*	m_RTI;
	HTREEITEM		m_hItem;
};

class CWorkspaceToolBar : public CBCGPToolBar
{
public: 
	// All commands should be routed via owner window, not via frame:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler) 
	{ 
		CBCGPToolBar::OnUpdateCmdUI ((CFrameWnd*) GetOwner (), bDisableIfNoHndler);
	}

	// Toolbar should't appear on the customization list
	virtual BOOL AllowShowOnList () const		{	return FALSE;	}
	virtual void AdjustLayout ();
};

class CWorkspaceBar : public CBCGPDockingControlBar
{
public:
	CWorkspaceBar();

// Attributes
protected:
	CWorkspaceToolBar	m_wndToolBar;
	CTreeCtrl			m_wndTree;

// Operations
public:
	void SelectItem(int id);
	int	GetFeatureCount() const
	{
		return (int)m_mapItems.GetCount();
	}

	CRuntimeClass* GetFeatureViewRTI(int id) const;
	void GetFeatureName(int id, CString& strTitle) const;
	CDemoFeature2::Feature GetFeature(int id) const;

	void AdjustLayout ();


// Implementation
public:
	virtual ~CWorkspaceBar();


// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTreeCollapseAll();
	afx_msg void OnTreeExpandAll();
	//}}AFX_MSG
	afx_msg void OnSelectTree(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

	void AddFeatureGroup(LPCTSTR lpszName, int nGroupID);

	CMap<int, int, CDemoFeature2*, CDemoFeature2*>	m_mapItems;
	CImageList										m_Images;
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACEBAR_H__435B2ABB_C4AB_4400_B80C_7EE3520CBFEA__INCLUDED_)
