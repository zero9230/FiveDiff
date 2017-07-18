#pragma once
#include "BCGPButton.h"


// CControlChooese 对话框

class CControlChooese : public CDialogEx
{
	DECLARE_DYNAMIC(CControlChooese)

public:
	CControlChooese(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CControlChooese();

// 对话框数据
	enum { IDD = IDD_SELECTQUALITYFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CBCGPButton m_File1;
	CBCGPButton m_file2;
	CBCGPButton m_file3;
	CBCGPButton m_file4;
	CBCGPButton m_file5;
	CBCGPButton m_file6;
	CBCGPButton m_file7;
	CBCGPButton m_file8;
	CBCGPButton m_file9;
	CFont		textfont;
	int			m_ControltypeRadio;

	void		Initbutton();
	afx_msg void OnLjcontrolradio();
	afx_msg void OnFilebutton1();
	afx_msg void OnFilebutton2();
	afx_msg void OnFilebutton3();
	afx_msg void OnFilebutton4();
	afx_msg void OnFilebutton5();
	afx_msg void OnFilebutton6();
	afx_msg void OnFilebutton7();
	afx_msg void OnFilebutton8();
	afx_msg void OnFilebutton9();
};
