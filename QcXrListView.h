#pragma once


// CQcXrListView 对话框

class CQcXrListView : public CDialogEx
{
	DECLARE_DYNAMIC(CQcXrListView)

public:
	CQcXrListView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQcXrListView();

// 对话框数据
	enum { IDD = IDD_QC_XR_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont			textfont;
	CMyBCGPListCtrl	m_ListList;				//列表控件的绑定对象

	int				curpage;					//当前页码，用于翻页
	int				maxPage;					//最大页数
	int				startIndex;				//当前页起始下标
	int				endIndex;					//当前页终末下标
	CString			pageNum;					//用于显示页面中当前页码
	int				itemCount;				//记录条数

	unsigned char	QcXrFileExist;				//0:文件未使用，1:文件已使用
	int 				qcXrListDataNum;			//对应质控方式及文件的记录总数
	CString			number;					//批号
	CString			deadline;					//有效期
	double			qcAve[26];				//总平均值
	double			qcRan[26];				//总平均极差

	double			data[26][62];				//质控结果,包含平均值和极差
	CString			qcResDate[31];			//质控日期
	CString			qcResTime[31];			//质控时间

	void			setQcAveRan();
	void			InitListList();
	void			UpdateListResultList();
	void			UpdateView();
	bool			GetQcXrEditData();
	int			GetQcXrResultData(int controltype, int controlfile);



	afx_msg void OnBnClickedQcXrListUpButton();
	afx_msg void OnBnClickedQcXrListDownButton();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnRedraw(WPARAM, LPARAM);

};
