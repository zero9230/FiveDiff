#pragma once
#include "Includes_app.h"

// CMotorSetView 对话框

class CMotorSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorSetView)

public:
	CMotorSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMotorSetView();

// 对话框数据
	enum { IDD = IDD_MOTOR_PARASET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	CSpi m_spidev;
	afx_msg void OnBnClickedXm1();
	afx_msg void OnBnClickedXm2();
	afx_msg void OnBnClickedXm3();
	afx_msg void OnBnClickedXm4();
	afx_msg void OnBnClickedXm5();
	afx_msg void OnBnClickedXm6();
	afx_msg void OnBnClickedDim();
	afx_msg void OnBnClickedYm1();
	afx_msg void OnBnClickedYm2();
	afx_msg void OnBnClickedYm3();
	afx_msg void OnBnClickedYm4();
	afx_msg void OnBnClickedYm5();
	afx_msg void OnBnClickedYm6();
	afx_msg void OnBnClickedYm7();
	afx_msg void OnBnClickedYm8();
	afx_msg void OnBnClickedYm9();
	afx_msg void OnBnClickedYm10();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnResetXYmotor();
	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
