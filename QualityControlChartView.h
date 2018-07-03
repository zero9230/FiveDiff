#pragma once
#include "BCGPChartCtrl.h"
#include "BCGPListCtrl.h"
//#include <CString>


// CQualityControlChartView 对话框


class CQualityControlChartView : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityControlChartView)

public:
	CQualityControlChartView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQualityControlChartView();

	// 对话框数据
	enum { IDD = IDD_QUALITY_CONTROL_CHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void	OnPaint();
	virtual BOOL	OnInitDialog();
	afx_msg HBRUSH  OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBCGPChartVisualObject* pChart;
	CBCGPChartVisualObject* pChart2;
	CBCGPChartVisualObject* pChart3;
	CBCGPChartVisualObject* pChart4;

	void			InitLineChart();
	void			InitLineChart2();
	void			InitLineChart3();
	void			InitLineChart4();

	void			UpdateLineChart();
	void			UpdateLineChart2();
	void			UpdateLineChart3();
	void			UpdateLineChart4();

	void			OnUpdateChart(int num);
	CBCGPChartCtrl  m_QualityLineChart;
	CBCGPChartCtrl  m_QualityLineChart2;
	CBCGPChartCtrl  m_QualityLineChart3;
	CBCGPChartCtrl  m_QualityLineChart4;
	CMyBCGPListCtrl   m_materialInfolist;
	bool			InitmaterialInfoList();
	bool			UpdateMaterialInfoList();
	CString			quality_table[28];

	int				curpage;
	afx_msg void	OnGraphUp();
	afx_msg void	OnGraphDown();
	afx_msg LRESULT OnRedraw(WPARAM, LPARAM);

	void UpdateView();


	CFont			textfont;
	int				QcLjFileExistEdit;//0:文件没有编辑信息，1:文件有编辑信息
	int 			qcLjGraphNum;		//对应质控方式及文件的记录总数
	int				GetNumDea(int controltype, int controlfile);
	int				GetDetail(int controltype, int controlfile);
	void			UpdateMSC();
	void			UpdateLUlimit();
	double			upperlimit[26];//上限
	double			lowerlimit[26];//下限
	double			data[26][31];//质控结果
	float Mean[26];
	float SD[26];
	float CV[26];
	CString number;
	CString deadline;

	//void Draw_LJ(int Orgx, int Orgy, HDC hdc);
	afx_msg void OnBnClickedGraphPrint();
	//void Draw_LJ(int Orgx, int Orgy, int y_max, int num, HDC hdc);
	void Draw_LJ(CString type, CDC &pDC, int Xorg, int Yorg, float y_max, int num);
	void Compute_MSC();//计算每个项目的Mean,SD,CV的值
};
