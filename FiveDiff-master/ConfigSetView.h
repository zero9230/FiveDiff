#pragma once
#include "Includes_app.h"
//#include "Mainfrm.h"
#include "WorkspaceBar.h"
#include "TimeSetView.h"
#include "UnitSetView.h"
#include "RangeSetView.h"
#include "ThresholdSetView.h"
#include "UploadSetView.h"
#include "PrintSetView.h"
#include "ReportSetView.h"
#include "ResetView.h"
#include "PLTSetView.h"
#include "MotorSetView.h"
#include "CorrectParaSetView.h"
#include "DevelopmentSetView.h"
#include "AutoMaintenanceSetView.h"
#include "LMNESetView.h"
#include "CompanySetView.h"
#include "DevelopmentSetView.h"
#include "AutoSamplingSetView.h"

// CConfigSetView 对话框

class CConfigSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigSetView)

public:
	CConfigSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfigSetView();

// 对话框数据
	enum { IDD = IDD_CONFIGSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CWorkspaceBar			m_wndWorkSpace;
	int						m_nCurrType;
	CArray<CView*, CView*>	m_arViews;
	CDialogEx*				m_treePage[17];
	static BOOL				Activeflg[17];
	int						SetView[17];
	static int				ActiveView;
	CView*					GetView(int nID);
	void					SelectView(int nID);
	afx_msg	 int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
};
