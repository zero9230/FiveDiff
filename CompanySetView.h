#pragma once
#include "Includes_app.h"

// CCompanySetView 对话框

class CCompanySetView : public CDialogEx
{
	DECLARE_DYNAMIC(CCompanySetView)

public:
	CCompanySetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCompanySetView();

// 对话框数据
	enum { IDD = IDD_COMPANYSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
