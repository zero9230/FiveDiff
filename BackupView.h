#pragma once
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPTabWnd.h"
#include "BackupRestoreView.h"
#include "BackupSetView.h"
#include "BCGPButton.h"

// CBackupView 对话框

class CBackupView : public CDialogEx
{
	DECLARE_DYNAMIC(CBackupView)

public:
	CBackupView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBackupView();

// 对话框数据
	enum { IDD = IDD_BACKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	void	updatetabview();
	CBCGPTabWnd m_backuptab;

	CBackupRestoreView  CRestorePage;
	CBackupSetView		CSetPage;

	CBCGPButton m_backupinstall;
	CBCGPButton m_shutup;
	CBCGPButton m_resourceManage;
	CBCGPButton m_manualbackup;
	CBCGPButton m_saveset;
	CBCGPButton m_OK;
	CBCGPButton m_Cancel;
};
