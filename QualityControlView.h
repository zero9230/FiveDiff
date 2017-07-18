#pragma once
#include "afxcmn.h"
#include "QualityRadarView.h"
#include "QualityControlChartView.h"
#include "QualityTargetValueView.h"
#include "QualityTestView.h"
// CQualityControlView 窗体视图
extern 	CQualityTestView m_QualityTestPage;

class CQualityControlView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CQualityControlView)

protected:
	CQualityControlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CQualityControlView();

public:
	enum { IDD = IDD_QUALITY_CONTROL };
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
	afx_msg void OnPaint();
	virtual void OnInitialUpdate();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CBCGPTabWnd					m_QualityTab;

	CQualityRadarView			m_RadarPage;
	CQualityControlChartView	m_QualityChartPage;
	CQualityTargetValueView		m_QualityTargetPage;

	CDialog*					pDialog[4];  //用来保存对话框对象指针
	afx_msg void				OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


