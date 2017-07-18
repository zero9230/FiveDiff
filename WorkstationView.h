#pragma once
#include "BCGPButton.h"
#include "WorkstationTasksheet.h"
#include "WorkstationAnalysis.h"
#include "WorkstationResult.h"
#include "Includes_app.h"
// CWorkstationView 对话框


//static sample_info	 sampledata2;			//与界面交互和数据库交互的变量
//static patient_info	 patientdata2;
//static task_info	 taskdata2;

class CWorkstationView : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkstationView)

public:
	CWorkstationView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkstationView();

// 对话框数据
	enum { IDD = IDD_WORKSTATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	CBCGPTabWnd  m_workstationtab;
	void		 updatetabview();

	CBCGPButton m_ok;
	CBCGPButton m_cancel;

	CWorkstationTasksheet m_Tasksheetpage;
	CWorkstationAnalysis  m_Analysispage;
	CWorkstationResult	  m_Resultpage;
	CSpi				m_spidev;
	afx_msg void		OnClose();
	afx_msg void		OnTimer(UINT_PTR nIDEvent);
	virtual void		OnOK();
	virtual void		OnCancel();
	void				InitData(task_info* taskdata);
	void				DisplayErrMess();
	void				GetErrInfo();
	void				DealwithBlockErr(uchar CMD_Name, uchar ErrNum);
	void				SendCmdToDSP(uchar CMD_Name);
	void				InformWindowTheTask(int num);
protected:
	afx_msg LRESULT OnWorkstationtest(WPARAM wParam, LPARAM lParam);
public:
	static bool			ErrorTimer_Flag;
	static int			addtime;
	static bool			TempReq_EN;
	static int			reagenttemp;
	static int			cuptemp;
	static int			oritemp_rea;
	static int			oritemp_cup;
	unsigned int 		tempcup_base;
	unsigned int 		tempreagent_base;
	unsigned char 		temperature[9];
	static unsigned char ErrFlag;
	bool				BlockErr_Flag;
	unsigned char		BlockErrStore;
	static unsigned char	IsBlocking;
	static unsigned char	EN_Repeat;
	bool 				NumChanged;
	static int			TimesofTest;

	vector<task_info>*  m_alltask;
	DataTransmission	m_datatrans;
	DataProcess			m_dataprocess;

	 sample_info	 sampledata2;			//与界面交互和数据库交互的变量
	 patient_info	 patientdata2;
	 task_info		 taskdata2;

protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetallTaskInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWorksheetClean(WPARAM wParam, LPARAM lParam);
};
