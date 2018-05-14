#pragma once
#include <vector>
#include "CMyBCGPListCtrl.h"
#include "BCGPEdit.h"
using namespace std;

// CWorkstationAnalysis 对话框

class CWorkstationAnalysis : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkstationAnalysis)

public:
	CWorkstationAnalysis(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkstationAnalysis();

// 对话框数据
	enum { IDD = IDD_WORKSHEET_ANALYSIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	int			GetthetaskSerialNum(sample_info* sampledata);
	CRect	m_rect;
	void	ChangeSize(CWnd *pWnd, int cx, int cy);
	vector<task_info>* m_alltask;
	sample_info* sampledata;
protected:
	afx_msg LRESULT OnGetallTaskInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetresult(WPARAM wParam, LPARAM lParam);
public:
	CMyBCGPListCtrl m_analysisList;
	void			InitAnaliysisList();
	void			FillResultInfo(sample_info* sampledata, task_info* taskdata);
	void			UpdateAnaliysisList(int num);
};
