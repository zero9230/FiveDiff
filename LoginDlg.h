#pragma once

#include "Includes_app.h"
//#include "afxwin.h"
// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

	// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CComboBox m_userComb;
	CString m_user;
	CString  m_pw;

	int m_right;
	_ConnectionPtr  m_pDB;
	_RecordsetPtr   m_pRs;

	CBitmap bitmap;
	HBITMAP  pbitmap;
	CBitmap logobitmap;
	int width, height, px;
	CPoint m_startpos;
	CRect m_ctlrect;
	CPicture* m_pPic;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLogin();
	virtual void OnOK();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

