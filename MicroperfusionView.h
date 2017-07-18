#pragma once
#include"Includes_app.h"

// CMicroperfusionView 对话框

class CMicroperfusionView : public CDialogEx
{
	DECLARE_DYNAMIC(CMicroperfusionView)

public:
	CMicroperfusionView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMicroperfusionView();
	CFont m_Font;
	CSpi m_spidev;
// 对话框数据
	enum { IDD = IDD_MICROPERFUSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedMainHydrMiniprime();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
};
