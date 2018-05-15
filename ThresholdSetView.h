#pragma once
#include "Includes_app.h"

// CThresholdSetView 对话框

class CThresholdSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CThresholdSetView)

public:
	CThresholdSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThresholdSetView();

// 对话框数据
	enum { IDD = IDD_THRESHOLDSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnThresholdApplicate();
};
