#pragma once
#include "Includes_app.h"
#include "afxcmn.h"

// CRangeSetView 对话框
class CRangeSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CRangeSetView)

public:
	CRangeSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRangeSetView();

// 对话框数据
	enum { IDD = IDD_RANGESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CMyBCGPListCtrl m_typeList;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void InitTypeList();
	void ShowRange(int types);
	void SaveRange(int types);
	afx_msg void OnNMClickTypeList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSetDefault();
	afx_msg void OnSave();
	afx_msg void OnSampleCopy();
};
