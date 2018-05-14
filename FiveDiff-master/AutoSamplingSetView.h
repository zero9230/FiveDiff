#pragma once
#include "Includes_app.h"

// CAutoSamplingSetView 对话框

extern bool 		Allow_ASOnLine;
const uchar 		ASCMD_RESET[] = { 0x01, 0x02, 0x03, 0x03, 0x03, 0x04, 0x04, 0x05, 0x06, 0x07 };
const uchar 		ASCMD_RUN[] = { 0x08, 0x09, 0x0A, 0x11, 0x12, 0x0B, 0x13, 0x0C, 0x0D, 0x0E };
const uchar 		ASCMD_OPPARA[] = { 0x0F, 0x10, 0x14, 0x15 };
static int			OriPara[] = { 689, 136, 350, 238, 68, 2360, 50, 192, 238, 164 };
static uchar        OriVersionNum[] = { 0, 0, 0 };

class CAutoSamplingSetView : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoSamplingSetView)

public:
	CAutoSamplingSetView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoSamplingSetView();

// 对话框数据
	enum { IDD = IDD_AUTOSAMPLINGSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();

	void InitPara(int para[]);
	void OutputPara(int para[]);
	void OutputVersionNum(int para[]);
	bool  send_asmotpara(uchar sdata[], uchar len, uchar cmd);
	int  recv_asmotpara(unsigned int * rdata, uchar len);
	int  recv_versionnum(unsigned int * rdata, uchar len);
	CRS232			m_newCom;
	static bool 	AllowAS;
	bool				rs;
	unsigned char 	sdata2[21];
	unsigned char 	sdata[21];
	static uchar    IsMotorReseted[10];    // 1:have reseted
	static unsigned int   VersionNum[3];
	static unsigned int  polltimes;
	static unsigned int ASMotorPara[10];
	CString			paratemp[10];
	char 			buff[5] ;
	char 			buff2[3] ;
	char			version[20] ;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnAs1Reset();
	afx_msg void OnAs2Reset();
	afx_msg void OnAs3Reset();
	afx_msg void OnAs4Reset();
	afx_msg void OnAs5Reset();
	afx_msg void OnAs6Reset();
	afx_msg void OnAs7Reset();
	afx_msg void OnAs8Reset();
	afx_msg void OnAs9Reset();
	afx_msg void OnAs10Reset();
	afx_msg void OnAs1Run();
	afx_msg void OnAs2Run();
	afx_msg void OnAs3Run();
	afx_msg void OnAs4Run();
	afx_msg void OnAs5Run();
	afx_msg void OnAs6Run();
	afx_msg void OnAs7Run();
	afx_msg void OnAs8Run();
	afx_msg void OnAs9Run();
	afx_msg void OnAs10Run();
	afx_msg void OnAsParaRead();
	afx_msg void OnAsParaWrite();
	afx_msg void OnParaInit();
	afx_msg void OnAsAllReset();
};
