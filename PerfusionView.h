#pragma once
#include "Includes_app.h"

// CPerfusionView 对话框

class CPerfusionView : public CDialogEx
{
	DECLARE_DYNAMIC(CPerfusionView)

public:
	CPerfusionView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPerfusionView();

// 对话框数据
	enum { IDD = IDD_PERFUSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPrimeDiluent();
	afx_msg void OnPrimeRinse();
	afx_msg void OnPrimeLmnefix();
	afx_msg void OnPrimeWbclyse();
	afx_msg void OnPrimeHgblyse();
	afx_msg void OnPrimeAll();
	afx_msg void OnPrimeReversedprime();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void PrimeReagent(char* Mess, uchar CMD);
	void SetWindowEnable();
	void SetWindowDisable();
	CSpi m_spidev;
	
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
	int RinseMode;
};
