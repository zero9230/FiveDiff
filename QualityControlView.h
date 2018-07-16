#pragma once
#include "afxcmn.h"
#include "QualityRadarView.h"
#include "QualityControlChartView.h"
#include "QualityTargetValueView.h"
#include "QualityTestView.h"
#include "QualityListView.h"
#include "QcXTargetValueView.h"
#include "QcXChartView.h"
#include "QcXListView.h"
#include "QcXTestView.h"
#include "QcXrEditView.h"
#include "QcXrTestView.h"
#include "QcXrListView.h"
#include "QcXrChartView.h"
// CQualityControlView 窗体视图
//extern 	CQualityTestView m_QualityTestPage;

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
	void CQualityControlView::DatabaseSave(vector<qc_edit_data> &qc_edit, vector<qc_result_data> &qc_result);
	CBCGPTabWnd					m_QualityTab;
	CString ChartsToCStringdata2(unsigned char * chart, int len);
	CString ChartsToCString(char * chart, int len);
	CQualityRadarView			m_RadarPage;

	CQualityTargetValueView	m_QualityTargetPage;

	
	CQcXTargetValueView		m_QcXTargetPage;
	//CQcXChartView				m_QcXChartPage;

	CQcXrEditView				m_QcXrEditPage;	

	void DatabaseLoad(CString filename);
	CDialog*					pDialog[4];  //用来保存对话框对象指针
	afx_msg void				OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnBnClickedQualityFileinfo();
	afx_msg void OnBnClickedQualityLoad();
};
extern CQualityTestView			m_QualityTestPage;
extern CQcXTestView				m_QcXTestPage;
extern CQcXrTestView			m_QcXrTestPage;

