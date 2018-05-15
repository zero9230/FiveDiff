#pragma once
#include "Includes_app.h"
#include "afxwin.h"

// CResetView 对话框

class CResetView : public CDialogEx
{
	DECLARE_DYNAMIC(CResetView)

public:
	CResetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResetView();

// 对话框数据
	enum { IDD = IDD_RESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CFont textfont;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSetDefault();
	CStatic m_statictext;
};
