#pragma once
#include "afxcmn.h"
#include "Includes_app.h"


// CQcXrTestView 对话框

class CQcXrTestView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXrTestView)

public:
	CQcXrTestView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQcXrTestView();

// 对话框数据
	enum { IDD = IDD_QC_XR_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int					testNum;			//测试次数
	unsigned int			QcXrFileExistEdit ;	//0:文件没有编辑信息，1:文件有编辑信
	CString				tempXrNumber ;
	CString				tempXrDeadline ;

	CMyBCGPListCtrl		m_QcXrTestList;
	QcDataProcess	 m_qcDataProcess;
	CSpi		   m_spidev;
	qcresult_info qcresultdata;			//测试结果
	qcresult_info qcresultdata1;		//测试结果
	qcresult_info qcresultdataAve;		//平均测试结果，只有参数，图形没有意义
	qcresult_info qcresultdataRan;		//极差，只有参数，图形没有意义


	void					InitQcXrTestList();
	void					UpdateQcXrTestList1();
	void					UpdateQcXrTestList2();
	void					UpdateQcXrTestHeadInfo();

	void					initQcXrData();
	void					initQcXrData1();
	void					initQcXrAveData();
	void					initQcXrRanData();
	void					copyqcresultToResult1();

	void					getAveRan();
	bool					getQcXrEditFile();//读取数据库中质控编辑数据
	int					getqcresultRow();
	afx_msg LRESULT		OnQualitytest(WPARAM wParam, LPARAM lParam);//发送质控测试命令
	afx_msg LRESULT		OnAckspi(WPARAM wParam, LPARAM lParam);//onackspi，向下位机索取数据
	void					OnTimer(UINT_PTR nIDEvent);//定时器，ontimer
	//更新表格

	//

	

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	CFont			textfont;

	
};
