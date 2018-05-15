#pragma once
//#include "afxwin.h"
//#include "BCGPChartExample.h"
//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
#include "Includes_app.h"
// CChangeAllReagentView 对话框

class CChangeAllReagentView : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeAllReagentView)

public:
	CChangeAllReagentView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeAllReagentView();

// 对话框数据
	enum { IDD = IDD_CHANGE_ALL_REAGENTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	CBCGPDateTimeCtrl m_Dstartdate;
	CBCGPDateTimeCtrl m_Rstartdate;
	CBCGPDateTimeCtrl m_HGBstartdate;
	CBCGPDateTimeCtrl m_EOSstartdate;
	CBCGPDateTimeCtrl m_BASstartdate;

	CBCGPDateTimeCtrl m_Denddate;
	CBCGPDateTimeCtrl m_Renddate;
	CBCGPDateTimeCtrl m_HGBenddate;
	CBCGPDateTimeCtrl m_EOSenddate;
	CBCGPDateTimeCtrl m_BASenddate;

	COleDateTime    DiluentStartDate, RinseStartDate, HGBStartDate, EOSStartDate, BASStartDate;
	COleDateTime	DiluentEndDate, RinseEndDate, HGBEndDate, EOSEndDate, BASEndDate;

	int m_nFirstDayOfWeek ;

	virtual void OnOK();
	void SaveDate();
	void SaveReagentAmount();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
