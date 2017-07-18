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
// BCGPChartExampleView.h : interface of the CBCGPChartExampleView class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_BCGPCHARTEXAMPLEVIEW_H__CB2F5435_9A0A_418C_8145_C809FAB94156__INCLUDED_)
#define AFX_BCGPCHARTEXAMPLEVIEW_H__CB2F5435_9A0A_418C_8145_C809FAB94156__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define YEARS_NUM 5

inline double Rand(double dblStart, double dblFinish)
{
	double minVal = min(dblStart, dblFinish);
	double maxVal = max(dblStart, dblFinish);

	return (maxVal - minVal) * (double)rand() / (RAND_MAX + 1) + minVal;
}

class CBCGPChartExampleView : public CBCGPFormView
{
protected: // create from serialization only
	CBCGPChartExampleView(UINT id = 0);
	DECLARE_DYNCREATE(CBCGPChartExampleView)

	// Form Data
public:
	//{{AFX_DATA(CBCGPChartExampleView)
	enum { IDD = IDD_FORM };
	//}}AFX_DATA

	// Attributes
public:
	CBCGPChartExampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPChartExampleView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPChartExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual CBCGPChartVisualObject* GetChart()
	{
		return NULL;
	}

	virtual CBCGPBaseVisualCtrl* GetCtrl()
	{
		return NULL;
	}

	virtual void SetupLayout();
	virtual void UpdateChartColorTheme(int nTheme);
	virtual void OnChangeBackgroundDarkness() {}

	void RotateChart(CBCGPRotationObject::RotationElement hit, double xDelta = 10., double yDelta = 10., double persperctiveDelta = 0.1);
	void SetDefaultLineWidth();

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPChartExampleView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg void OnFilePrintPreview();
	afx_msg LRESULT HandleInitDialog(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

	CString					m_strTitle;
	//CDemoFeature::Feature	m_Feature;
	BOOL					m_bIsReady;
	BOOL					m_bIsDarkBackground;
	BOOL					m_bIsTexturedTheme;
	BOOL					m_bIsFlatTheme;

	CBCGPGridCtrl*							m_pCurrGrid;
	CArray<CBCGPGridCtrl*, CBCGPGridCtrl*>	m_arGrids;
	int										m_nCurrType;

public:
	//sMaintain				m_sMaintain;
	//void					InitMaintain();
	//void					InitNormalUserParas();
	//void					InitSuperUserParas();
	//void					InitPrerogativeUserParas();
	//void					InitLogFiles();
	//void					syscfginit();
	//void					init();
	//lgfi					logfile;
};
 

#ifndef _DEBUG  // debug version in BCGPChartExampleView.cpp
inline CBCGPChartExampleDoc* CBCGPChartExampleView::GetDocument()
   { return (CBCGPChartExampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPCHARTEXAMPLEVIEW_H__CB2F5435_9A0A_418C_8145_C809FAB94156__INCLUDED_)
