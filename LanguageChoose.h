#pragma once


// CLanguageChoose 对话框

class CLanguageChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CLanguageChoose)

public:
	CLanguageChoose(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLanguageChoose();

	// 对话框数据
	enum { IDD = IDD_LANGUAGE_CHOOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int m_languageChoose;
	afx_msg void OnBnClickedRadioChinese();
	afx_msg void OnBnClickedRadioEnglish();
	afx_msg void OnBnClickedRadioFrench();
	afx_msg void OnBnClickedRadioRussian();
	afx_msg void OnBnClickedRadioSpanish();
	virtual BOOL OnInitDialog();
};
