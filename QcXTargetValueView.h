#pragma once

#include "ReportGenerator\ReportGenerator.h"
// CQcXTargetValueView 对话框

class CQcXTargetValueView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXTargetValueView)

public:
	CQcXTargetValueView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQcXTargetValueView();

	// 对话框数据
	enum { IDD = IDD_QC_X_TARGETVALUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyBCGPListCtrl m_QcXTargetValueList;
	void			InitTargetValueList();
	afx_msg void	OnPaint();
	virtual BOOL	OnInitDialog();
	afx_msg HBRUSH  OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void	createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);
	void	distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);

	afx_msg void	OnNMClickQcXTargetvalueList(NMHDR *pNMHDR, LRESULT *pResult);
	int				e_QcXItem;    //刚编辑的行  
	int				e_QcXSubItem; //刚编辑的列  
	CEdit			m_QcXTargetEdit;
	bool			isQcXEditcreated;//标志编辑框已经被创建
	static	int		item_focused;
	int nRow;

	CString			tempXNumber;
	CString			tempXDeadline;
	CString			Qctarget[26];
	CString			TargetLimit[26];	//偏差限
	unsigned char	QcXFileExist;		//0:文件未使用，1:文件已使用


	//char			Qctype;
	void			GetQcLimitData();
	afx_msg void	OnQcXTargetConfirm();
	afx_msg void	OnQcXRangeConfirm();
	bool			JudgmentValid(CString Content);
	bool			GetQcFile();
	void			UpdateView();//更新界面中的数据
	//	int			GetEditFileCount(int controlType,int fileNum);

	CFont			textfont;
	CReportGenerator m_XreportGenerator;
	afx_msg void OnBnClickedPrintTarget();
};
