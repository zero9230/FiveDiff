#pragma once

// CTestmainView 窗体视图
//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "CMyBCGPListCtrl.h"
//#include "ListCtrl.h"
#include "Includes_app.h"
#include "BCGPComboBox.h"

static sample_info	 sampledata;			//与界面交互和数据库交互的变量
static patient_info	 patientdata;
static task_info	 taskdata;

class CTestmainView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CTestmainView)

protected:
	CTestmainView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTestmainView();

public:
	enum { IDD = IDD_TESTMAIN};
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	virtual void UpdateTestMode(int nTheme);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CMyBCGPListCtrl m_WBCresultList;
	CMyBCGPListCtrl m_RBCresultList;
	CMyBCGPListCtrl m_PLTresultList;
	CMyBCGPListCtrl m_RETresultList;
	CMyBCGPListCtrl m_CRPresultList;

	CBCGPChartCtrl  m_LMNEChart;
	CBCGPChartCtrl  m_BASOChart;
	CBCGPChartCtrl  m_RBCChart;
	CBCGPChartCtrl  m_PLTChart;
	CBCGPChartCtrl  m_PieChart;
	CBCGPListBox    m_WBCFlagListBox;
	CBCGPListBox    m_RBCFlagListBox;
	CBCGPListBox    m_PLTFlagListBox;
	CBCGPListBox    m_RETFlagListBox;

	virtual void OnChangeBackgroundDarkness()
	{
		SetObjectColors();
	}

	void SetObjectColors();

public:
	CSpi			 m_spidev;


	DataTransmission m_datatrans;
	DataProcess		 m_dataprocess;

	static unsigned char	ErrFlag;
	static bool		ErrorTimer_Flag;
	bool		BlockErr_Flag;
	static bool		TempReq_EN ;
	static int		addtime;
	static int		reagenttemp;
	static int		cuptemp;
	static int		oritemp_rea;
	static int		oritemp_cup;
	static int		TimesofTest ;
	unsigned int	i ;
	unsigned char 	temperature[9];
	unsigned int 	tempcup_base;
	unsigned int 	tempreagent_base;
	unsigned char	BlockErrStore;
	static	unsigned char		IsBlocking;
	static unsigned char		EN_Repeat;


	char 			SampNum[16] ;
	bool 			NumChanged;
	
public:
	virtual void	OnInitialUpdate();
	void			InitControl();
	void			patientPaint(patient_info *ppatientdata);

	BOOL			InitForm(sample_info* psampledata);
	BOOL			InitWBCForm(sample_info* psampledata);
	BOOL			InitRBCForm(sample_info* psampledata);
	BOOL			InitPLTForm(sample_info* psampledata);
	BOOL			InitRETForm();
	BOOL			InitCRPForm();

	BOOL			UpdateForm(sample_info* psampledata);
	BOOL			UpdateWBCForm(sample_info* psampledata);
	BOOL			UpdateRBCForm(sample_info* psampledata);
	BOOL			UpdatePLTForm(sample_info* psampledata);
	BOOL			UpdateRETForm();
	BOOL			UpdateCRPForm();

	void			Init_B_LMNE(float	coefficient, B_LMNE* p_blmne);
	void			PrintChart(sample_info *psampledata);
	void			PrintLMNEChart(sample_info *psampledata);
	void			PrintBASOChart(sample_info *psampledata);
	void			PrintRBCChart(sample_info *psampledata);
	void			PrintPLTChart(sample_info *psampledata);
	void			PrintPieChart();
	void			UpdatePrintChart(sample_info *psampledata);
	void			UpdatePrintBASOChart(sample_info *psampledata, const unsigned char rangetype);
	void			UpdatePrintRBCChart(sample_info *psampledata, const unsigned char rangetype);
	void			UpdatePrintPLTChart(sample_info *psampledata, const unsigned char rangetype);
	void			UpdatePrintPieChart();
	void			LmneGraphPaint(sample_info *psampledata, const unsigned char rangetype,CDC &MemDC);

	void			InitWBCFlagBox();
	void			InitRBCFlagBox();
	void			InitPLTFlagBox();
	void			UpdateWBClmneFlagBox(sample_info *psampledata);
	void			UpdateWBCBasoFlagBox(sample_info *psampledata);
	void			UpdateRBCFlagBox(sample_info *psampledata);
	void			UpdatePLTFlagBox(sample_info *psampledata);

	void			SetItemHeight(UINT nHeight);
	void			GetPatientInfo(patient_info *ppatientdata);

	void			Generatetask(task_info* ptaskdata);
    static  void	GetASBarcode(char buffRe[]);

private:
	void			InitData(void);
	void			DisplayErrMess();
	void			GetErrInfo();
	void            DealwithBlockErr(uchar CMD_Name, uchar ErrNum);
	void			SendCmdToDSP(uchar CMD_Name);
	void			AutoClean_MainWnd(RECT* STATUS);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

public:
	afx_msg LRESULT OnMainblanktest(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDisableview(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEnableview(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBlocker(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAutoclean(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConcenclean(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMaintest(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:

	void	CommonExecution(const char* Mess, uchar CMD, unsigned int m_ntime);
	void	AutoClean(const char* Mess);
	void	ConcentratedCleaning_1(const char* Mess);
	void	ConcentratedCleaning_2(const char* Mess);
	void	YealyMaintenance( const char* Mess);
	void	EM_RINSEBATHS( const char* Mess);


	static DWORD WINAPI	CreateAutoSampleThread(LPVOID lpParam);
	static DWORD WINAPI BarcodeCheck(LPVOID lpParam);
	static DWORD WINAPI ThreadPC(LPVOID lpParam);
	static DWORD WINAPI SwitchStateCheck(LPVOID lpParam);
	CBCGPComboBox m_sexcombo;
	CBCGPComboBox m_doctorcombo;
	CString		  m_barcode;
	//CDC			  MemDC;

protected:
	afx_msg LRESULT OnGetbarcode(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTestmainBarcode();
	// 开关状态检测
	
};


