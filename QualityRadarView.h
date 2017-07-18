#pragma once
#include "BCGPChartCtrl.h"
#include "CMyBCGPListCtrl.h"


// CQualityRadarView 对话框

class CQualityRadarView : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityRadarView)

public:
	CQualityRadarView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQualityRadarView();

// 对话框数据
	enum { IDD = IDD_RADARCHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void			OnPaint();
	virtual BOOL			OnInitDialog();
	void					OnUpdateChart(int num);
	void					OnInitRadarChart1();
	void					OnInitRadarChart2();
	void					OnInitRadarChart3();
	void					OnInitRadarChart4();
	void					OnInitRadarChart5();
	CBCGPChartCtrl			m_RadarChart1;
	CBCGPChartCtrl			m_RadarChart2;
	CBCGPChartCtrl			m_RadarChart3;
	CBCGPChartCtrl			m_RadarChart4;
	CBCGPChartCtrl			m_RadarChart5;
	CBCGPChartCtrl			m_RadarChart6;
	CBCGPChartCtrl			m_RadarChart7;
	CBCGPChartCtrl			m_RadarChart8;
	CMyBCGPListCtrl			m_QualityMaterialList;
	BOOL					OnInitQualityMaterialList();
	CFont					textfont;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
};
