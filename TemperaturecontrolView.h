#pragma once
#include "Includes_app.h"

// CTemperaturecontrolView 对话框

class CTemperaturecontrolView : public CDialogEx
{
	DECLARE_DYNAMIC(CTemperaturecontrolView)

public:
	CTemperaturecontrolView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTemperaturecontrolView();
	CFont m_Font;
	CSpi m_spidev;
	CEdit * Tem_Env;
	CEdit * Tem_Inc;
	int Tem_Set_Env;
	int Tem_Set_Inc;
// 对话框数据
	enum { IDD = IDD_TEMPERATURE_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	
	afx_msg void OnBnClickedTmctrlTmsetOk();
	void SendSysPara(void);
};
