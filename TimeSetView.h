#pragma once
#include "Includes_app.h"

// CTimeSetView 对话框

class CTimeSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeSetView)

public:
	CTimeSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTimeSetView();

// 对话框数据
	enum { IDD = IDD_TIMESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
