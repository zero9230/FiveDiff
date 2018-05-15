#pragma once
#include "Includes_app.h"

// CReagentmanagementView 对话框

class CReagentmanagementView : public CDialogEx
{
	DECLARE_DYNAMIC(CReagentmanagementView)

public:
	CReagentmanagementView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReagentmanagementView();

// 对话框数据
	enum { IDD = IDD_REAGENT_MANAGEMENT };
	CFont m_Font;
	CSpi m_spidev;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedMaintenanceWeeklyOk1();
	afx_msg void OnBnClickedMaintenanceWeeklyOk2();
	afx_msg void OnBnClickedMaintenanceYearly();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
};
