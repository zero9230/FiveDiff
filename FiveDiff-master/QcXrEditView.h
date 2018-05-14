#pragma once


// CQcXrEditView 对话框

class CQcXrEditView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXrEditView)

public:
	CQcXrEditView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQcXrEditView();



// 对话框数据
	enum { IDD = IDD_QC_XR_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	unsigned int QcXrFileExist;
	CString tempXrNumber;
	CString tempXrDeadline;
	

	afx_msg void OnBnClickedQcXrEditEnter();
	bool getQcXrFile(bool loadData);
	//bool GetQcXEditData();
	void setQcXrEditData();
	CFont			textfont;
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
