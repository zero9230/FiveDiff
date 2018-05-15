#pragma once
#include "Includes_app.h"

// CReabentalarmView 对话框

class CReabentalarmView : public CDialogEx
{
	DECLARE_DYNAMIC(CReabentalarmView)

public:
	CReabentalarmView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReabentalarmView();
	CFont m_Font;
// 对话框数据
	enum { IDD = IDD_REAGENT_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegentsetOk();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
