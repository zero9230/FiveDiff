#pragma once

//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "CMyBCGPListCtrl.h"
#include "Includes_app.h"

// CWorkSheetView 窗体视图

class CWorkSheetView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CWorkSheetView)

protected:
	CWorkSheetView();           // 动态创建所使用的受保护的构造函数
	virtual ~CWorkSheetView();

public:
	enum { IDD = IDD_WORKSHEET };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyBCGPListCtrl m_worksheetList;

	BOOL		 InitWorksheetForm();
	virtual void OnInitialUpdate();
	void		 UpdateWorksheetForm();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};


