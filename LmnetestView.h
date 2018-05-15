#pragma once
#include "Includes_app.h"
#include "afxcmn.h"
#include "cmybcgplistctrl.h"

// CLmnetestView 对话框

class CLmnetestView : public CDialogEx
{
	DECLARE_DYNAMIC(CLmnetestView)

public:
	CLmnetestView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLmnetestView();
	CSpi m_spidev;
	
// 对话框数据
	enum { IDD = IDD_LMNE_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedSfpipecheckOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnBnClickedSfpipecheckQuery();
	afx_msg void OnBnClickedCancel();
	BOOL InitForm(void);
//	void OnInitialUpdat(void);
//	void OnInitialUpdate(void);
	virtual BOOL OnInitDialog();
//	CListCtrl my_List;
//	CMyBCGListCtrl m_List;
	CMyBCGPListCtrl m_List;
};
