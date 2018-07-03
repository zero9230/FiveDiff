#pragma once


// CMultiLangTest 对话框

class CMultiLangTest : public CDialogEx
{
	DECLARE_DYNAMIC(CMultiLangTest)

public:
	CMultiLangTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMultiLangTest();

// 对话框数据
	enum { IDD = IDD_MULTILANG_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
