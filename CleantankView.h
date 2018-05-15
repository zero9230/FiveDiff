#pragma once
#include "Includes_app.h"

// CCleantankView 对话框

class CCleantankView : public CDialogEx
{
	DECLARE_DYNAMIC(CCleantankView)

public:
	CCleantankView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCleantankView();

// 对话框数据
	enum { IDD = IDD_CLEAN_TANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
