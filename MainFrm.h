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
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__CA7FBBF0_F2F8_4379_9D8F_BB2137D22B03__INCLUDED_)
#define AFX_MAINFRM_H__CA7FBBF0_F2F8_4379_9D8F_BB2137D22B03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Includes_app.h"

#include <vector>
using std::vector;
#define CFrameWnd CBCGPFrameWnd

extern CRect m_progressrect;
//extern CQualityTestView m_QualityTestPage;
struct CDemoFeature
{
	enum Feature
	{
		BCGP_Unknown = -1,
		TestmainView,
		ReagentmanagementView,
		//QcFileSelectView,
		QualityControlView,
		DoctorInfoView,
		LogView,
		//ResultListView,
		//PaitientResultView,
		ResultManageView,
		CalibtationView,
		WorkSheetView,
		PatientInfoView,

	};

	CDemoFeature()
	{
		m_nGroup = -1;
		m_id = 0;
		m_Feature = BCGP_Unknown;
		m_RTI = NULL;
		m_hItem = NULL;
	}

	CDemoFeature(int nGroup, Feature feature, LPCTSTR lpszName, CRuntimeClass* pRTI)
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

class TransferWindow{
public:
	vector<int> window_num;
	int current_num;
public:
	TransferWindow(){
		current_num = 1;
		window_num.push_back(2);
	}
	int forward(){
		if (current_num < window_num.size())
			current_num++;
		return window_num[current_num - 1];
	}
	int back(){
		if (current_num > 1)
			current_num--;
		return window_num[current_num - 1];
	}
	void add_new_window(int num){
		if (current_num != window_num.size()){
			auto it = window_num.begin() + current_num - 1;
			for (int i = window_num.size() - current_num; i > 0; i--)
				window_num.erase(it + i);
		}
		window_num.push_back(num);
		current_num++;
	}
};

class CMainFrame : public CFrameWnd
{
public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	void SelectView(int nID);

	int GetCurrentViewType () const
	{
		return m_nCurrType;
	}
	CBCGPOutlookBar& GetShortCut()
	{
		return m_wndShortcutsBar;
	}
	CBCGPOutlookBarPane& GetShortCutPane(){
		return m_wndShortcutsPane1;
	}

	int	GetFeatureCount() const
	{
		return (int)m_mapItems.GetCount();
	}
	int	GetTestMode() const
	{
		return m_nTestMode;
	}
	void UpdateCurrentView (int nViewType);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPStatusBar			m_wndStatusBar;
	CBCGPExplorerToolBar		m_wndToolBar;
	CBCGPOutlookBar			m_wndShortcutsBar;
	CBCGPOutlookBarPane		m_wndShortcutsPane1;
	CBCGPCaptionBar			m_wndCaptionBar;
	//CWorkspaceBar			m_wndWorkSpace;
	

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void			OnViewBack();
	afx_msg void			OnUpdateViewBack(CCmdUI* pCmdUI);
	afx_msg void			OnViewForward();
	afx_msg void			OnUpdateViewForward(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void			OnTestModeCombo();
	afx_msg void			OnOutlookBarShortcut(UINT id);
	afx_msg void OnUpdateOutlookBarShortcut(CCmdUI* pCmdUI);
	afx_msg LRESULT			OnRedraw(WPARAM, LPARAM);
	afx_msg LRESULT			USB_StatusChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT			OnMSG_ACKSPI(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	void										    AddFeatureGroup(LPCTSTR lpszName, int nGroupID);

	BOOL											CreateShortcutsBar();
	int												m_nCurrType;
	CArray<CView*, CView*>							m_arViews;
	int												m_nTestMode;
	CMap<int, int, CDemoFeature*, CDemoFeature*>	m_mapItems;
	
public:
	
	CSpi			         m_spidev;
	CProgressCtrl			 m_progress;
	static int			     TimeClick;
	static int				 progresstimes;
	CRuntimeClass*			 GetFeatureViewRTI(int id) const;
	void					 GetFeatureName(int id, CString& strTitle) const;
	CDemoFeature::Feature	 GetFeature(int id) const;
	
	CView*				 GetView(int nID);
	afx_msg void			OnStartup();
	afx_msg void			OnTimer(UINT_PTR nIDEvent);

public:
	void					SendSysPara_MainTop();
	void					SendSysPara();

	void					InitNormalUserParas();
	void					InitMaintain(void);
	void					InitSuperUserParas(void);
	void					InitPrerogativeUserParas(void);
	void					InitLogFiles(void);
	void					Syscfginit(void);
	void					Init(void);

	HWND					hwnd;
	CWnd*					pWnd;
	void					GetClentRectEx(CRect& lpRect);

	afx_msg void			OnBlanktest();
	afx_msg void			OnMainTest();
	afx_msg void			OnConfigSet();
	afx_msg void			OnSelftest();
	afx_msg void			OnMotorcheck();
	afx_msg void			OnValvecheck();
	afx_msg void			OnPerfusion();
	afx_msg void			OnClean();
	afx_msg void			OnEmpty();
	afx_msg void			OnConcentratedclean();
	afx_msg void			OnRecoil();
	afx_msg void			OnMicroPerfusion();
	afx_msg void			OnAutoclean();
	afx_msg void			OnReagentManagement();
	afx_msg void			OnMaintenance();
	afx_msg void			OnSourceManagement();
	afx_msg void			OnHgbTest();
	afx_msg void			OnLmneTest();
	afx_msg void			OnCleanTank();
	afx_msg void			OnLocationQuantitative();
	afx_msg void			OnGraphicDebug();
	afx_msg void			OnFaultStatistics();
	afx_msg void			OnReagentAlarmSet();
	afx_msg void			OnTemperatureControl();
	afx_msg void			OnBasoLandmarkSet();
	afx_msg void			OnLmneLandmarkPattern();
	afx_msg void			OnConnectDSP();

	
	void					StartProgress(int ntime);
	HACCEL hAccel;

	afx_msg void OnQualityTest();
	afx_msg void OnClose();
	afx_msg LRESULT OnTestSwitchOn(WPARAM wParam, LPARAM lParam);

	static DWORD WINAPI	CreateSwitchDetechThread(LPVOID lpParam);
	static DWORD WINAPI	CreateHeartbeatThread(LPVOID lpParam);

	afx_msg void OnDatabaseImport();
	afx_msg void OnDatabaseBackup();
	afx_msg void OnDatabaseClearup();
	afx_msg void OnWorksheet();
	afx_msg void OnLockKeyboard();
	afx_msg void OnUnlockKeyboard();
	afx_msg void OnBackupsystem();

protected:
	afx_msg LRESULT OnUpdateErrStatus(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnReagentAlarm(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLanguageChoose();
	afx_msg void OnMultilangTest();
//	afx_msg void OnMainDiluentsample();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CA7FBBF0_F2F8_4379_9D8F_BB2137D22B03__INCLUDED_)
