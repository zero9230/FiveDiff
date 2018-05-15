#pragma once
#include "Includes_app.h"

// CDevelopmentSetView 对话框

class CDevelopmentSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CDevelopmentSetView)

public:
	CDevelopmentSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevelopmentSetView();

// 对话框数据
	enum { IDD = IDD_DEVELOPMENTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
