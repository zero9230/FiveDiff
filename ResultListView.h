#pragma once

//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPDateTimeCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPButton.h"
#include "CMyBCGPListCtrl.h"
#include "ResultDetails.h"
#include "PatientResultView.h"
#include "Includes_app.h"
#include "afxwin.h"
// CResultListView 窗体视图

class CResultListView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CResultListView)

public:
	CResultListView();           // 动态创建所使用的受保护的构造函数
	virtual ~CResultListView();

public:
	enum { IDD = IDD_RESULTLIST };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL		OnEraseBkgnd(CDC* pDC);
	virtual void		OnInitialUpdate();
	BOOL				InitResultForm();
	CMyBCGPListCtrl		m_ResultList;

	int					m_nFirstDayOfWeek;
	COleDateTime		m_Date;

	CBCGPDateTimeCtrl	m_ResultDate;
	void				UpdateResultList(COleDateTime);
	afx_msg void		OnCloseupResultTimepicker();
	afx_msg void		OnPaint();

	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

public:
	ResultToDisplay 	ThisResult;
	CResultDetails*		m_pResultDetails;
	CBCGPButton			m_paitient_result;
	afx_msg void		OnPaitientResult();
	afx_msg void OnBnClickedResultPageUp();
	afx_msg void OnBnClickedResultPageDown();
	afx_msg void OnBnClickedResultPageTrailer();
	afx_msg void OnBnClickedResultPageJump();
	afx_msg void OnBnClickedResultPageHome();

	CButton ResultList_Page_Home;
	CButton ResultList_Page_Front;
	CButton ResultList_Page_Next;
	CButton ResultList_Page_Trailer;
};


