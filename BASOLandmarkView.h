#pragma once
#include "afxwin.h"


// CBASOLandmarkView 对话框

class CBASOLandmarkView : public CDialogEx
{
	DECLARE_DYNAMIC(CBASOLandmarkView)

public:
	CBASOLandmarkView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBASOLandmarkView();
	CFont m_Font;
// 对话框数据
	enum { IDD = IDD_BASO_LANDMARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CEdit* Edit_BASO1;
	CEdit* Edit_BASO2;
	CEdit* Edit_BASO3;
	afx_msg void OnBnClickedOk();
};
