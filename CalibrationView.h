#pragma once


#include "BCGPChartExample.h"
#include "BCGPChartExampleDoc.h"
#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
#include "BCGPChartCtrl.h"
#include "BCGPListBox.h"
#include "BCGPListCtrl.h"
#include "CMyBCGPListCtrl.h"
#include "Includes_app.h"


// CCalibrationView 窗体视图


static uchar ref_ac[5][6];				//5项参考值输入
static CString wbc_buff[5], rbc_buff[5], hgb_buff[5], mcv_buff[5], plt_buff[5];	//五次测试结果
static uchar wbc_cvbuff[6], rbc_cvbuff[6], hgb_cvbuff[6], mcv_cvbuff[6], plt_cvbuff[6];			//变异系数CV
static uchar wbc_coebuff[5], rbc_coebuff[5], hgb_coebuff[5], mcv_coebuff[5], plt_coebuff[5];	//最后的校正系数


class CCalibrationView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CCalibrationView)

protected:
	CCalibrationView();           // 动态创建所使用的受保护的构造函数
	virtual ~CCalibrationView();

public:
	enum { IDD = IDD_CALIBRATION };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAutoCalibrateStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CMyBCGPListCtrl m_CalibrationList;
	CMyBCGPListCtrl m_CoefficientList;

	CString Mean[5];//平均值
	//CString TestTime[5];//测试时间
	int e_Item;    //刚编辑的行  
	int e_SubItem; //刚编辑的列  
	CEdit m_WBCEdit;
	bool haveeditcreate;//标志编辑框已经被创建


	void	createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);
	void	distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);
	BOOL	InitCalibrationForm();
	BOOL	InitCoeffcientForm();
	virtual void OnInitialUpdate();
	void	AutoCalibrationRun();
	void	DealWithWBC(uchar CurCalMode);
	void	DealWithRBC(uchar CurCalMode);
	void	DealWithHGB(uchar CurCalMode);
	void	DealWithMCV(uchar CurCalMode);
	void	DealWithPLT(uchar CurCalMode);
	void	DealWithData(uchar CurCalMode, CString ResultBuff[5],CString MeanBuff[5], uchar CVBuff[5], uchar CoeBuff[5], int ItemType,int meanIndex);
	//void	DealWithData(uchar CurCalMode, CString ResultBuff[5], uchar CVBuff[5], uchar CoeBuff[5], int ItemType);
	void	ShowCalibrationInfo();
	void	UpdateCalibrate();
	void	Showtarget();
	BOOL	GetRefValue();

public :

	static unsigned char oldSysmode;			//记录进入界面前的系统测试模式，退出界面的时候要恢复原来的测试模式
	static unsigned char ac_index;              //需要五次测试，记录第几次测试
	static unsigned char ref_flag;				//表示参考值的输入状态，1表示已输入，0表示未输入
	static status CurStatusMess;



private:
	sample_info		 sampledata;
	CSpi			 m_spidev;
	DataTransmission m_datatrans;
	DataProcess		 m_dataprocess;
	uchar			 TestMode;

protected:
	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
public:
	//afx_msg void OnTargetvalue();
	afx_msg void OnNMClickCoefficientList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedTestmodeRadio();
	int m_modeRadio;
	int m_testmodeRadio;
	afx_msg void OnBnClickedAutoModeRadio();

	afx_msg void OnBnClickedAutoModeRadio2();
	afx_msg void OnBnClickedAutoTestmodeRadio();
	afx_msg void OnBnClickedAutoTestmodeRadio2();
	afx_msg void OnCalibrationTest();
	void		 UpdateTargetvalue();

	void		initData();


	afx_msg void OnBnClickedManualCalibrationSave();
};


