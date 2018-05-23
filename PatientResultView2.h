#pragma once
//#include "CMyBCGPListCtrl.h"

#include "Includes_app.h"
#include "afxwin.h"
#include "ResultDetails.h"

// CPatientResultView2 对话框

class CPatientResultView2 : public CDialogEx
{
	DECLARE_DYNAMIC(CPatientResultView2)

public:
	CPatientResultView2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPatientResultView2();

// 对话框数据
	enum { IDD = IDD_PAITIENTRESULT };
//#ifdef _DEBUG
//	virtual void AssertValid() const;
//#ifndef _WIN32_WCE
//	virtual void Dump(CDumpContext& dc) const;
//#endif
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyBCGPListCtrl		m_PatientResultList;
	CBCGPButton			m_daily_result;
	CResultDetails*		m_pResultDetails2;
	ResultToDisplay 	ThisResult2;
	Relation            ThisRelation;
	CBCGPButton			m_SearchButton;


	BOOL  InitPatientResultForm();
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	bool is_search;
	afx_msg void OnBnClickedButton1();

	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_patientname;
	//	afx_msg void OnBnClickedPatientResult2();
	//	afx_msg void OnBnClickedButton3();
	//CString m_patientGender;
	afx_msg void OnBnClickedButtonSearch();
	CComboBox patient_gender;
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
