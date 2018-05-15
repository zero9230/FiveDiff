#pragma once
#include "Includes_app.h"
#include "afxwin.h"

// CCorrectParaSetView 对话框

class CCorrectParaSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CCorrectParaSetView)

public:
	CCorrectParaSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCorrectParaSetView();

// 对话框数据
	enum { IDD = IDD_CORRECTEPARASET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int m_modeRadio;
	int m_testmodeRadio;
	uchar		TestMode;
	afx_msg void OnBnClickedModifysetWholeblood();
	afx_msg void OnBnClickedModifysetDiluent();
	afx_msg void OnBnClickedModifysetCbc5diff();
	afx_msg void OnBnClickedModifysetCbc();
	virtual BOOL OnInitDialog();
	void ShowModifyPara();
	afx_msg void OnParaSetSave();
};
