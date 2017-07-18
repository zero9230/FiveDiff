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
// BCGPChartExampleDoc.h : interface of the CBCGPChartExampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPCHARTEXAMPLEDOC_H__30DB379C_C966_4852_A28A_11D54B8C3F4D__INCLUDED_)
#define AFX_BCGPCHARTEXAMPLEDOC_H__30DB379C_C966_4852_A28A_11D54B8C3F4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBCGPChartExampleDoc : public CDocument
{
protected: // create from serialization only
	CBCGPChartExampleDoc();
	DECLARE_DYNCREATE(CBCGPChartExampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPChartExampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGPChartExampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGPChartExampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPCHARTEXAMPLEDOC_H__30DB379C_C966_4852_A28A_11D54B8C3F4D__INCLUDED_)
