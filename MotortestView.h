#pragma once
#include "Includes_app.h"


// CMotortestView 对话框

class CMotortestView : public CDialogEx
{
	DECLARE_DYNAMIC(CMotortestView)

public:
	CMotortestView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMotortestView();

// 对话框数据
	enum { IDD = IDD_MOTORTEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void  CheckMoters(const char* Mess, uchar CMD);
	CSpi m_spidev;
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnChmotorsSamndle();
	afx_msg void OnChmotorsCar();
	afx_msg void OnChmotorsSamsyr();
	afx_msg void OnChmotorsDrainsyr();
	afx_msg void OnChmotorsCountsyr();
	afx_msg void OnChmotorsCytosyr();
	afx_msg void OnChmotorsDilusyr();
	afx_msg void OnChmotorsPuncture();
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
