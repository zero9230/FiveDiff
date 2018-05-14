#pragma once
#include "Includes_app.h"

// CPLTSetView 对话框

class CPLTSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CPLTSetView)

public:
	CPLTSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPLTSetView();

// 对话框数据
	enum { IDD = IDD_PLTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnApplicate();

public:
	int m_pltmodeRadio;
	CFont font, font1;
};
