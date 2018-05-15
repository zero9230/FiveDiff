#pragma once


// CQualityFileExit 对话框
extern int rc;
class CQualityFileExit : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityFileExit)

public:
	CQualityFileExit(CWnd* pParent = NULL );   // 标准构造函数
	virtual ~CQualityFileExit();

// 对话框数据
	enum { IDD = IDD_QUALITY_FILEEXIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	qc_edit_data_info qcLjXXrEditData;

	afx_msg void OnClose();
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	CFont		 textfont;

	afx_msg void OnBnClickedCancel();
	void setLjXXrEditData(qc_edit_data_info qcEditData);
};
