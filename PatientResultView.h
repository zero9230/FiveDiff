#pragma once
//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPButton.h"
//
//#include "CMyBCGPListCtrl.h"
#include "ResultListView.h"
#include "Includes_app.h"
#include "afxwin.h"

// CPatientResultView 窗体视图

class CPatientResultView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CPatientResultView)

public:
	CPatientResultView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPatientResultView();

public:
	enum { IDD = IDD_PAITIENTRESULT };
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
	CMyBCGPListCtrl		m_PatientResultList;
	CBCGPButton			m_daily_result;
	CResultDetails*		m_pResultDetails2;
	ResultToDisplay 	ThisResult2;
	Relation            ThisRelation;

	BOOL  InitPatientResultForm();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();

	afx_msg void OnDailyResult2();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_patientname;
//	afx_msg void OnBnClickedPatientResult2();
//	afx_msg void OnBnClickedButton3();
	//CString m_patientGender;
	afx_msg void OnBnClickedButtonSearch();
	CComboBox patient_gender;
	afx_msg void OnPaint();
};


