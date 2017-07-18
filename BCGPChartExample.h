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
// BCGPChartExample.h : main header file for the BCGPCHARTEXAMPLE application
//

#if !defined(AFX_BCGPCHARTEXAMPLE_H__FA3CFA1A_02B1_4E23_BDD2_8E2CBB177398__INCLUDED_)
#define AFX_BCGPCHARTEXAMPLE_H__FA3CFA1A_02B1_4E23_BDD2_8E2CBB177398__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#include "resource.h"       // main symbols
#include "Includes_app.h"
#include "ConfigSetView.h"

#define BCGGRID_VIEWS_NUM		16

#define BCGGRID_BASIC			0
#define BCGGRID_REPORT			1
#define BCGGRID_CELLTYPES		2
#define BCGGRID_COLOR			3
#define BCGGRID_VIRTUAL			4
#define BCGGRID_MERGE			5
#define BCGGRID_FILTER			6
#define BCGGRID_FILTERBAR		7
#define BCGGRID_FREEZECOL		8
#define BCGGRID_DRAGNDROP		9
#define BCGGRID_EASYINPUT		10
#define BCGGRID_MULTILINEHEADER	11
#define BCGGRID_MULTILINEITEMS	12
#define BCGGRID_CONDITIONALFORM	13
#define BCGGRID_SPARKLINE		14
#define BCGGRID_AUTOCOMPLETE	15

//自定义消息

#define WM_USB_STATUS		(WM_USER + 1)
#define UM_REDRAW			(WM_USER + 2)
#define MSG_ACKSPI			(WM_USER + 3)

//TestmainView
#define WM_DISABLEVIEW		(WM_USER+4)
#define WM_ENABLEVIEW		(WM_USER+5)
#define WM_MAINBLANKTEST	(WM_USER+6)
#define WM_BLOCKER			(WM_USER+7)
#define WM_ACKSPI			(WM_USER+8)
#define WM_AUTOCLEAN		(WM_USER+9)
#define WM_CONCENCLEAN		(WM_USER+10)
#define	WM_MAINTEST			(WM_USER+11)


#define WM_CHANGEWINDOW		(WM_USER+12)

#define WM_ACKSPI2			(WM_USER+13)
#define WM_QUALITYTEST		(WM_USER+14)

#define WM_THREAD			(WM_USER+15)
#define WM_TESTSWITCHON		(WM_USER+16)

#define WM_GETBARCODE		(WM_USER+17)

#define WM_WORKSHEET_TEST		(WM_USER+18)
#define WM_WORKSHEET_ACKSPI		(WM_USER+19)
#define WM_STARTNEXTTASK		(WM_USER+20)

#define WM_GETALLTASKINFO		(WM_USER+21)
#define WM_GETRESULT			(WM_USER+22)

#define WM_RESTART				(WM_USER+23)
#define WM_WORKSHEET_CLEAN		(WM_USER+24)
#define WM_SWITCHSTATE			(WM_USER+25)

extern CConfigSetView* SetPTR;


/////////////////////////////////////////////////////////////////////////////
// CBCGPChartExampleApp:
// See BCGPChartExample.cpp for the implementation of this class
//

class CBCGPChartExampleApp : public CBCGPWinApp
{
public:
	CBCGPChartExampleApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();

	int GetDefaultLineWidth()
	{
		return globalData.bIsWindows7 ? 2 : 1;
	}

	const CBCGPChartTheme& GetCustomTheme(int nTheme)
	{
		return nTheme == -2 ? m_CustomColorTheme : m_CustomTexturedTheme;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPChartExampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPChartExampleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBCGPChartTheme m_CustomColorTheme;
	CBCGPChartTheme m_CustomTexturedTheme;
public:
	int ExitInstanc(void);
};

extern CBCGPChartExampleApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPCHARTEXAMPLE_H__FA3CFA1A_02B1_4E23_BDD2_8E2CBB177398__INCLUDED_)
