#pragma once
#include "Includes_app.h"

// CReportSetView 对话框

class CReportSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CReportSetView)

public:
	CReportSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReportSetView();

// 对话框数据
	enum { IDD = IDD_REPORTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
