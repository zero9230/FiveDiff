#pragma once
#include "Includes_app.h"

// CMaintainView 对话框

class CMaintainView : public CDialogEx
{
	DECLARE_DYNAMIC(CMaintainView)

public:
	CMaintainView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMaintainView();

// 对话框数据
	enum { IDD = IDD_MAINTAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
