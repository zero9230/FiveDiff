#pragma once
#include "BCGPChartCtrl.h"
#include "BCGPListCtrl.h"

// CQualityListView 对话框

class CQualityListView : public CDialogEx
{
	DECLARE_DYNAMIC(CQualityListView)

public:
	CQualityListView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQualityListView();

// 对话框数据
	enum { IDD = IDD_QUALITY_LIST };

	CFont			textfont;
	CMyBCGPListCtrl	m_ListList;				//列表控件的绑定对象

	int				curpage;					//当前页码，用于翻页
	int				maxPage;					//最大页数
	int				startIndex;				//当前页起始下标
	int				endIndex;					//当前页终末下标
	CString			pageNum;					//用于显示页面中当前页码
	int				itemCount;				//记录条数

	unsigned char	QcLjFileExist;				//0:文件未使用，1:文件已使用
	CString			number;					//批号
	CString			deadline;					//有效期
	CString			Qctarget[26];				//靶值
	CString			TargetLimit[26];			//偏差限

	double			data[26][31];				//质控结果
	CString			qcResDate[31];			//质控日期
	CString			qcResTime[31];			//质控时间

	void			InitListList();
	void			UpdateListResultList();
	void			UpdateView();
	bool			GetQcLjEditData();
	int			GetQcLjResultData(int controltype, int controlfile);
	
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQualityListUpButton();
	afx_msg void OnBnClickedQualityListDownButton();
	afx_msg LRESULT OnRedraw(WPARAM, LPARAM);
	virtual BOOL OnInitDialog();
	
};
