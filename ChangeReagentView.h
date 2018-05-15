#pragma once
//#include "afxwin.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPDateTimeCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPComboBox.h"
#include "Includes_app.h"

// CChangeReagentView 对话框

class CChangeReagentView : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeReagentView)

public:
	CChangeReagentView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeReagentView();

// 对话框数据
	enum { IDD = IDD_CHANGE_REAGENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	CBCGPDateTimeCtrl m_startdate;
	CBCGPDateTimeCtrl m_enddate;
	COleDateTime  startdate,enddate;

	int			m_nFirstDayOfWeek;
	CBCGPComboBox m_reagentbox;
	virtual void OnOK();

	void  SaveDate();
	void  SaveReagentAmount();
	afx_msg void OnChangeReagentCombo();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
