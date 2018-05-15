#pragma once
#include "Includes_app.h"

// CPrintSetView 对话框

class CPrintSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CPrintSetView)

public:
	CPrintSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrintSetView();

// 对话框数据
	enum { IDD = IDD_PRINTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	CBCGPSwitchCtrl	m_AutoprintSwitch;
	CBCGPSwitchCtrl	m_PictureSwitch;

	CFont textfont;
	CFont textfont1;


	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPrintApplicate();
	int m_PrintsizeRadio;
};
