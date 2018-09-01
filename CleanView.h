#pragma once
#include "Includes_app.h"

// CCleanView 对话框

class CCleanView : public CDialogEx
{
	DECLARE_DYNAMIC(CCleanView)

public:
	CCleanView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCleanView();

// 对话框数据
	enum { IDD = IDD_WASH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void CleanChannel(char* Mess, uchar CMD);
	void SetWindowEnabled();
	void SetWindowDisabled();

	CSpi m_spidev;
	afx_msg void OnCleanCyto();
	afx_msg void OnCleanChambers();
	afx_msg void OnCleanDiluentintine();
	afx_msg void OnCleanDiluentextine();
	afx_msg void OnCleanGem();
	afx_msg void OnCleanSheatflowpipe();
	afx_msg void OnCleanRinsebaso();
	afx_msg void OnCleanRinseintine();
	afx_msg void OnCleanRinseextine();
	afx_msg void OnCleanExternneedle();

	static unsigned char ExterCleanFlag;	//外部针清洗标志，1-外部针清洗
	static unsigned char ExterCleanStep;	//外部清洗步骤，0-初始状态，1-第一步完成，2-第二步完成，3-第三步完成，4-第四步完成
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
};
