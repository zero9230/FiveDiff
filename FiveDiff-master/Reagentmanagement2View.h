#pragma once
//#include "BCGPChartExample.h"
//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPButton.h"
#include "Includes_app.h"

// CReagentmanagement2View 窗体视图

class CReagentmanagement2View : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CReagentmanagement2View)

protected:
	CReagentmanagement2View();           // 动态创建所使用的受保护的构造函数
	virtual ~CReagentmanagement2View();

public:
	enum { IDD = IDD_REAGENT_MANAGEMENT2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual void OnInitialUpdate();


	int				  m_nFirstDayOfWeek;
	CBCGPDateTimeCtrl m_DiluentStartDate;
	CBCGPDateTimeCtrl m_RinseStartDate;
	CBCGPDateTimeCtrl m_HGBStartDate;
	CBCGPDateTimeCtrl m_EOSStartDate;
	CBCGPDateTimeCtrl m_BASStartDate;
	CBCGPDateTimeCtrl m_DiluentEndDate;
	CBCGPDateTimeCtrl m_RinseEndDate;
	CBCGPDateTimeCtrl m_HGBEndDate;
	CBCGPDateTimeCtrl m_EOSEndDate;
	CBCGPDateTimeCtrl m_BASEndDate;

	COleDateTime    DiluentStartDate, RinseStartDate, HGBStartDate, EOSStartDate, BASStartDate;
	COleDateTime	DiluentEndDate, RinseEndDate, HGBEndDate, EOSEndDate, BASEndDate;

	void			Paint_Diluent();
	void			Paint_Rinse();
	void			Paint_HB5D_HGB();
	void			Paint_HB5D_EOS();
	void			Paint_HB5D_BAS();
	void			UpdateReagentDate();
	CBCGPButton		m_Diluent_Status;
	afx_msg void	OnChangeAllReagent();
	afx_msg void	OnChangeReagent();
	virtual BOOL	PreCreateWindow(CREATESTRUCT& cs);
	void PaintLevel();
};


