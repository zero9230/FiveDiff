#pragma once
#include "CMyBCGPListCtrl.h"


// CWorkstationResult 对话框

class CWorkstationResult : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkstationResult)

public:
	CWorkstationResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkstationResult();

// 对话框数据
	enum { IDD = IDD_WORKSTATION_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CMyBCGPListCtrl m_resultlist;

	void  ChangeSize(CWnd *pWnd, int cx, int cy);
	CRect m_rect;
};
