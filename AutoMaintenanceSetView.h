#pragma once
#include "Includes_app.h"

// CAutoMaintenanceSetView 对话框

class CAutoMaintenanceSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoMaintenanceSetView)

public:
	CAutoMaintenanceSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoMaintenanceSetView();

// 对话框数据
	enum { IDD = IDD_AUTOMAINTENANCESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	int m_microperfusiontimeRadio;
	CFont font,font1;
	virtual BOOL OnInitDialog();
	afx_msg void OnApplicateMantainset();

	BOOL SaveIntervalFrequency();
	afx_msg void OnRecoil();
};
