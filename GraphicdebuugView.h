#pragma once
#include "Includes_app.h"

// CGraphicdebuugView 对话框

class CGraphicdebuugView : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphicdebuugView)

public:
	CGraphicdebuugView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGraphicdebuugView();

// 对话框数据
	enum { IDD = IDD_GRAPHIC_DEBUG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
