#pragma once
#include "CMyBCGPListCtrl.h"


// CQualityTargetValueView 对话框
extern qc_edit_data_info qcLjEditData;
class CQualityTargetValueView : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityTargetValueView)

public:
	CQualityTargetValueView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQualityTargetValueView();

// 对话框数据
	enum { IDD = IDD_QUALITY_TARGETVALUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyBCGPListCtrl m_TargetValueList;
	void			InitTargetValueList();
	afx_msg void	OnPaint();
	virtual BOOL	OnInitDialog();
	afx_msg HBRUSH  OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void	createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);
	void	distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);

	afx_msg void	OnNMClickQualityTargetvalueList(NMHDR *pNMHDR, LRESULT *pResult);
	int				e_Item;    //刚编辑的行  
	int				e_SubItem; //刚编辑的列  
	CEdit			m_QualityTargetEdit;
	bool			haveeditcreate;//标志编辑框已经被创建
	static	int		item_focused;
	int nRow;

	CString			tempLjNumber;
	CString			tempLjDeadline;
	CString			Qctarget[26];
	CString			TargetLimit[26];	//偏差限
	unsigned char	QcLjFileExist;		//0:文件未使用，1:文件已使用
	

	//char			Qctype;
	void			GetQcLimitData();
	afx_msg void	OnQualitytargetConfirm();
	afx_msg void	OnRangeConfirm();
	bool			JudgmentValid(CString Content);
	bool			GetQcFile();
	void			UpdateView();//更新界面中的数据
//	int			GetEditFileCount(int controlType,int fileNum);

	CFont			textfont;

};
