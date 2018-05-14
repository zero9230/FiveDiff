#pragma once


// CBackupRestoreView 对话框

class CBackupRestoreView : public CDialogEx
{
	DECLARE_DYNAMIC(CBackupRestoreView)

public:
	CBackupRestoreView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBackupRestoreView();

// 对话框数据
	enum { IDD = IDD_BACKUP_RESTORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
};
