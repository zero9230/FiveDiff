#pragma once
#include "Includes_app.h"

// CUploadSetView 对话框

class CUploadSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CUploadSetView)

public:
	CUploadSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUploadSetView();

// 对话框数据
	enum { IDD = IDD_UPLOADSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
