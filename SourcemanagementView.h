#pragma once
#include "Includes_app.h"

// CSourcemanagementView 对话框

class CSourcemanagementView : public CDialogEx
{
	DECLARE_DYNAMIC(CSourcemanagementView)

public:
	CSourcemanagementView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSourcemanagementView();

// 对话框数据
	enum { IDD = IDD_SOURCE_MANAGEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
