#pragma once
#include "Includes_app.h"

// CLocationquantitativeView 对话框

class CLocationquantitativeView : public CDialogEx
{
	DECLARE_DYNAMIC(CLocationquantitativeView)

public:
	CLocationquantitativeView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLocationquantitativeView();

// 对话框数据
	enum { IDD = IDD_LOCATION_QUANTITATIVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSpi			         m_spidev;
	afx_msg void OnBnClickedDebugXyration();
	void SetWindowEnable(void);
	void SetWindowDisable(void);
	afx_msg void OnBnClickedDebugSampleration();
	afx_msg void OnBnClickedDebugHgblyseration();
	afx_msg void OnBnClickedDebugRinseration();
	afx_msg void OnBnClickedDebugFixration();
	afx_msg void OnBnClickedDebugDiluentration();
	afx_msg void OnBnClickedDebugWbclyseration();
	afx_msg void OnBnClickedDebugEscape();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnPaint();
};
