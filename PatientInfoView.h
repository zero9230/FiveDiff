#pragma once

//#include "BCGPChartExampleDoc.h"
//#include "BCGPChartExampleView.h"
//#include "afxcmn.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPChartCtrl.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListBox.h"
//#include "C:\Program Files (x86)\BCGSoft\BCGControlBarPro\BCGCBPro\BCGPListCtrl.h"
//#include "CMyBCGPListCtrl.h"
#include "Includes_app.h"
#include "ResultDetails.h"
#include "CMyBCGPListCtrl.h"
#include "afxcmn.h"
// CPatientInfoView 窗体视图

class CPatientInfoView : public CBCGPChartExampleView
{
	DECLARE_DYNCREATE(CPatientInfoView)

protected:
	CPatientInfoView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPatientInfoView();

public:
	enum { IDD = IDD_PAITIENTINFO };
	ResultToDisplay 	ThisResult2;
	//CString m_patientId;
	//CString m_patientname;
	//CString m_patientNickname;
	//CString m_patientSex;
	//CString m_patientBirthday;
	//CString m_patientDistrict;
	//CString m_patientDoctor;
	//CString m_patientComment;

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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	BOOL InitPaitientInfoForm();
	//CListCtrl m_patientInfoList;
	CMyBCGPListCtrl m_patientInfoList;
	virtual void OnInitialUpdate();
	afx_msg void OnNMDblclkPatientinfoList(NMHDR *pNMHDR, LRESULT *pResult);
	//CListCtrl m_patientInfoList;
	afx_msg void OnClickedSave();
	afx_msg void OnManualAdd();
	afx_msg void OnDelete();
};


