#pragma once

#include "Includes_app.h"
// CHgbtestView 对话框

class CHgbtestView : public CDialogEx
{
	DECLARE_DYNAMIC(CHgbtestView)

public:
	CHgbtestView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHgbtestView();
	CFont m_Font;
	CSpi m_spidev;
// 对话框数据
	enum { IDD = IDD_HGB_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedHgbtestOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedHgbtestBack();
};
