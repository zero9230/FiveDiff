#pragma once
#include "afxwin.h"


// CTypeRangeCopy 对话框

class CTypeRangeCopy : public CDialogEx
{
	DECLARE_DYNAMIC(CTypeRangeCopy)

public:
	CTypeRangeCopy(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTypeRangeCopy();

// 对话框数据
	enum { IDD = IDD_TYPERANGE_COPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual void OnCancel();

	CString pasteName[10];
	CComboBox m_copyCombo;
};
