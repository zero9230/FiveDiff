#pragma once
#include "PatientResultView2.h"
#include "ResultListView2.h"
#include "afxcmn.h"

// CResultManageView 对话框

class CResultManageView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CResultManageView)

protected:
	CResultManageView();   // 标准构造函数
	virtual ~CResultManageView();

// 对话框数据
	enum { IDD = IDD_RESULT_MANAGE };
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
	CBCGPTabWnd m_ResultManageTab;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	CPatientResultView2 m_PatientResultPage;
	CResultListView2	m_ResultListPage;
	
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};
