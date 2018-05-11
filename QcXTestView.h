#pragma once
#include "Includes_app.h"
#include "CMyBCGPListCtrl.h"
#include "BCGPChartCtrl.h"

// CQcXTestView 对话框

class CQcXTestView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXTestView)

public:
	CQcXTestView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQcXTestView();

// 对话框数据
	enum { IDD = IDD_QC_X_TESTVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();

	CMyBCGPListCtrl m_WBCList;
	CMyBCGPListCtrl m_RBCList;
	CMyBCGPListCtrl m_PLTList;
	CMyBCGPListCtrl m_RETList;
	CMyBCGPListCtrl m_CRPList;
	CBCGPChartCtrl m_LmneChart;
	CBCGPChartCtrl m_BASOChart;
	CBCGPChartCtrl m_RBCChart;
	CBCGPChartCtrl m_PLTChart;
	CBCGPChartCtrl m_PieChart;

	qcresult_info	 qcresultdata;			//测试结果
	qcresult_info	 qcresultdataAve;			//平均测试结果，只有参数，图形没有意义
	QcDataProcess	 m_qcDataProcess;
	CSpi		   m_spidev;
	static unsigned int QcXFileExistEdit;	//0:文件没有编辑信息，1:文件有编辑信?
	unsigned char 	testNum;			//测试次数

	BOOL InitForm(qcresult_info *qcresultdata);
	BOOL UpdateForm(qcresult_info *qcresultdata);
	BOOL InitWBCForm(qcresult_info *qcresultdata);
	BOOL UpdateWBCForm(qcresult_info *qcresultdata);
	BOOL InitRBCForm(qcresult_info *qcresultdata);
	BOOL UpdateRBCForm(qcresult_info *qcresultdata);
	BOOL InitPLTForm(qcresult_info *qcresultdata);
	BOOL UpdatePLTForm(qcresult_info *qcresultdata);
	BOOL InitRETForm();
	BOOL UpdateRETForm();
	BOOL InitCRPForm();
	BOOL UpdateCRPForm();


	void PrintChart(qcresult_info *qcresultdata);
	void Init_B_LMNE(float	coefficient, B_LMNE* p_blmne);

	void LmneGraphPaint(qcresult_info *qcresultdata, const unsigned char rangetype, CDC &MemDC);
	void LmneGraphPaint(qcresult_info *qcresultdata, const unsigned char rangetype);

	void PrintLMNEChart(qcresult_info *qcresultdata);
	void UpdatePrintChart(qcresult_info *qcresultdata);
	void PrintBASOChart(qcresult_info *qcresultdata);
	void UpdatePrintBASOChart(qcresult_info *qcresultdata);
	void PrintRBCChart(qcresult_info *qcresultdata);
	void UpdatePrintRBCChart(qcresult_info *qcresultdata);
	void PrintPLTChart(qcresult_info *qcresultdata);
	void UpdatePrintPLTChart(qcresult_info *qcresultdata);
	void PrintPieChart();
	void UpdatePrintPieChart();
	void UpdateView();

	//void initQcLjData();//质控测试参数就是26个，没有必要28个，和主测试流程不一样
	int getqcresultRow();

	CFont	textfont;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void initQcXData();
	void initQcXAveData();
	void Addqcresult1ToAve();
	void Addqcresult2ToAve();



protected:
	afx_msg LRESULT OnQualitytest(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnAckspi(WPARAM wParam, LPARAM lParam);
};
