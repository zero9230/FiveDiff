#pragma once


// CSetMarkModeLMNEView 对话框

class CSetMarkModeLMNEView : public CDialogEx
{
	DECLARE_DYNAMIC(CSetMarkModeLMNEView)

public:
	CSetMarkModeLMNEView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetMarkModeLMNEView();
	CFont m_Font;
// 对话框数据
	enum { IDD = IDD_SetMarkModeLMNE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedSetlmnemodelOk();
	
	BOOL RAD_LMNE_Manual;
};
