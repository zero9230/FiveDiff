#pragma once


// CManualCalibrationView 对话框

class CManualCalibrationView : public CDialogEx
{
	DECLARE_DYNAMIC(CManualCalibrationView)

public:
	CManualCalibrationView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManualCalibrationView();

// 对话框数据
	enum { IDD = IDC_MANUAL_CALIBRATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int			m_moderadio;
	int			m_testmoderadio;
	uchar		TestMode;
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnModeRadio();
	afx_msg void OnModeRadio2();
	afx_msg void OnTestmodeRadio();
	afx_msg void OnTestmodeRadio2();

	void ShowCalibration();
};
