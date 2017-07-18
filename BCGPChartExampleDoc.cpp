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
// BCGPChartExampleDoc.cpp : implementation of the CBCGPChartExampleDoc class
//

#include "stdafx.h"
#include "BCGPChartExample.h"
//
#include "BCGPChartExampleDoc.h"
#include "Includes_app.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleDoc

IMPLEMENT_DYNCREATE(CBCGPChartExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPChartExampleDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPChartExampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleDoc construction/destruction

CBCGPChartExampleDoc::CBCGPChartExampleDoc()
{
	// TODO: add one-time construction code here

}

CBCGPChartExampleDoc::~CBCGPChartExampleDoc()
{
}

BOOL CBCGPChartExampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleDoc serialization

void CBCGPChartExampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleDoc diagnostics

#ifdef _DEBUG
void CBCGPChartExampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPChartExampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleDoc commands
