#pragma once
#include "Includes_app.h"

// CFaultstatisticsView 对话框

class CFaultstatisticsView : public CDialogEx
{
	DECLARE_DYNAMIC(CFaultstatisticsView)

public:
	CFaultstatisticsView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFaultstatisticsView();

// 对话框数据
	enum { IDD = IDD_FAULTS_STATISTICS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedAlertXmempty();
	afx_msg void OnBnClickedAlertYmempty();
	afx_msg void OnBnClickedAlertSmempty();
	afx_msg void OnBnClickedAlertDimempty();
	afx_msg void OnBnClickedAlertDrmempty();
	afx_msg void OnBnClickedAlertCtmempty();
	afx_msg void OnBnClickedAlertCymempty();
	afx_msg void OnBnClickedAlertWbcempty();
	afx_msg void OnBnClickedAlertRbcempty();
	afx_msg void OnBnClickedAlertWlempty();
	afx_msg void OnBnClickedAlertDiltmempty();
	afx_msg void OnBnClickedAlertWlfempty();
	afx_msg void OnBnClickedAlertTnempty();
	afx_msg void OnBnClickedAlertAllmempty();
};
