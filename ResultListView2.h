#pragma once
#include "CMyBCGPListCtrl.h"
#include "ResultDetails.h"
#include "Includes_app.h"

// CResultListView2 对话框

class CResultListView2 : public CDialogEx
{
	DECLARE_DYNAMIC(CResultListView2)

public:
	CResultListView2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResultListView2();

	// 对话框数据
	enum { IDD = IDD_RESULTLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CMyBCGPListCtrl		m_ResultList;
	ResultToDisplay 	ThisResult;
	CResultDetails*		m_pResultDetails;
	CBCGPButton			m_paitient_result;
	int					m_nFirstDayOfWeek;
	COleDateTime		m_Date;

	CBCGPDateTimeCtrl	m_ResultDate;



	BOOL				InitResultForm();

	void				UpdateResultList(COleDateTime);
	afx_msg void		OnCloseupResultTimepicker();
	afx_msg void		OnPaint();

	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);


	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
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
