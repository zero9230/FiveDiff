#pragma once


// CQcXrChartView 对话框

class CQcXrChartView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXrChartView)

public:
	CQcXrChartView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQcXrChartView();

// 对话框数据
	enum { IDD = IDD_QC_XR_CHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CBCGPChartVisualObject* pChart1;
	CBCGPChartVisualObject* pChart2;

	CBCGPChartCtrl  m_QcXrChartLineChart1;
	CBCGPChartCtrl  m_QcXrChartLineChart2;

	CMyBCGPListCtrl   m_QcXrChartMaterialInfolist;

	int				curpage;
	int				qcXrChartFileExistEdit;//0:文件没有编辑信息，1:文件有编辑信息
	int 				qcXrChartGraphNum;		//对应质控方式及文件的记录总数


	double			qcAve[26];//平均值
	double			qcRan[26];//极差

	double			data[26][62];//质控结果
	CString			quality_table[28];

	CFont			textfont;
	CString			number;
	CString			deadline;

	void			InitLineChart1();
	void			InitLineChart2();
	void			OnUpdateChart(int num);
	void			setQcAveRan();
	

	bool			InitmaterialInfoList();
	bool			UpdateMaterialInfoList();
	int			GetQcXrResult(int controltype, int controlfile);
	int			GetQcXrEdit(int controltype, int controlfile);


	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnRedraw(WPARAM, LPARAM);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedQcXrChartGraphUp();
	afx_msg void OnBnClickedQcXrChartGraphDown();
};
