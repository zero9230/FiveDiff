#pragma once
#include "Includes_app.h"

// CLMNESetView 对话框

#define PEAK1_L		30
#define PEAK1_H		80
#define PEAK2_L		80
#define PEAK2_H		120

class CLMNESetView : public CDialogEx
{
	DECLARE_DYNAMIC(CLMNESetView)

public:
	CLMNESetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLMNESetView();

// 对话框数据
	enum { IDD = IDD_LMNESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnApplicate();
	CFont font, font1;
};
