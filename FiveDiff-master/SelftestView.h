#pragma once
#include "Includes_app.h"
#include "afxwin.h"

// CSelftestView 对话框

class CSelftestView : public CDialogEx
{
	DECLARE_DYNAMIC(CSelftestView)

public:
	CSelftestView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSelftestView();

// 对话框数据
	enum { IDD = IDD_SELFTEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
private:
	CFont m_Font;
public:
	
	
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CSpi m_spidev;
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	void DisplayErrMess();
protected:
	afx_msg LRESULT OnBlocker(WPARAM wParam, LPARAM lParam);

public:
	void DealwithBlockErr(uchar CMD_Name, uchar ErrNum);
	afx_msg void OnBnClickedMechinitOk();
	afx_msg void OnBnClickedMechinitCancel();
};
