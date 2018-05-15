#pragma once
#include "Includes_app.h"

// CRecoilView 对话框

class CRecoilView : public CDialogEx
{
	DECLARE_DYNAMIC(CRecoilView)

public:
	CRecoilView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecoilView();
	CFont m_Font;
	CSpi m_spidev;
// 对话框数据
	enum { IDD = IDD_RECOIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedMainHydrBackflush();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
};
