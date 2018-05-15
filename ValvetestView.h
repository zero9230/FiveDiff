#pragma once

#include "Includes_app.h"
// CValvetestView 对话框

class CValvetestView : public CDialogEx
{
	DECLARE_DYNAMIC(CValvetestView)

public:
	CValvetestView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CValvetestView();

// 对话框数据
	enum { IDD = IDD_VALVETEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChvalvesV1();
	afx_msg void OnChvalvesV2();
	afx_msg void OnChvalvesV3();
	afx_msg void OnChvalvesV4();
	afx_msg void OnChvalvesV5();
	afx_msg void OnChvalvesV6();
	afx_msg void OnChvalvesV7();
	afx_msg void OnChvalvesV8();
	afx_msg void OnChvalvesV9();
	afx_msg void OnChvalvesV10();
	afx_msg void OnChvalvesV11();
	afx_msg void OnChvalvesV12();
	afx_msg void OnChvalvesV13();
	afx_msg void OnChvalvesV14();
	afx_msg void OnChvalvesV15();
	afx_msg void OnChvalvesV16();
	afx_msg void OnChvalvesV17();
	afx_msg void OnChvalvesV18();
	afx_msg void OnChvalvesV19();
	afx_msg void OnChvalvesV20();
	afx_msg void OnChvalvesV21();
	afx_msg void OnChvalvesV22();
	afx_msg void OnChvalvesV23();
	afx_msg void OnChvalvesV24();
	afx_msg void OnChvalvesV25();
	afx_msg void OnChvalvesV26();
	afx_msg void OnChvalvesV27();
	afx_msg void OnChvalvesV28();
	afx_msg void OnChvalvesV29();
	afx_msg void OnChvalvesV30();
	afx_msg void OnChvalvesV31();
	afx_msg void OnChvalvesV32();
	afx_msg void OnChvalvesV33();
	afx_msg void OnChvalvesV34();
	afx_msg void OnChvalvesV35();
	afx_msg void OnChvalvesV36();
	afx_msg void OnChvalvesV37();
	afx_msg void OnChvalvesV38();
	afx_msg void OnChvalvesV39();
	afx_msg void OnChvalvesV40();

	CSpi m_spidev;
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
