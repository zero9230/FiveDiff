#pragma once

//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "CMyBCGPListCtrl.h"
#include "Includes_app.h"
// CDoctorInfoView 窗体视图

typedef struct{
	vector<CString>	numofrs;    //存储id
	int				totalnums;  //当前显示id个数
	int				nownum;     //当前选中的id序号

	int				page_count;  //数据库总页数
	int				page_index;  //当前页数
	long			data_count;	//数据库id总数
	int				page_num; //一页显示的id个数
}DoctorInfoToDisplay;

class CDoctorInfoView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CDoctorInfoView)

protected:
	CDoctorInfoView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDoctorInfoView();

public:
	enum { IDD = IDD_DOCTORINFO };
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
	CMyBCGPListCtrl m_DoctorInfoList;

	BOOL InitDoctorInfoForm();
	BOOL UpdataDoctorInfoForm();
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnManualAdd();
	afx_msg void OnDelete();
	afx_msg void OnDblclkDoctorList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSave();
	DoctorInfoToDisplay ThisResult;
	afx_msg void OnBnClickedDoctPageHome();
	afx_msg void OnBnClickedDoctPageFront();
	afx_msg void OnBnClickedDoctPageNext();
	afx_msg void OnBnClickedDoctPageTrailer();
	afx_msg void OnBnClickedDoctPageJump();
};


